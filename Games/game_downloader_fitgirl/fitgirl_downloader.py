import time
import os
import logging
import json
import glob
from datetime import datetime
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.action_chains import ActionChains
from selenium.common.exceptions import TimeoutException, WebDriverException
from bs4 import BeautifulSoup
import re

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

class FitGirlGameDownloader:
    def __init__(self, download_folder="downloads", timeout=60):
        """Initialize the downloader with specified download folder and timeout"""
        self.download_folder = os.path.abspath(download_folder)
        if not os.path.exists(self.download_folder):
            os.makedirs(self.download_folder)
        
        self.timeout = timeout
        self.driver = None
        self.download_links = []
        self.current_link_index = 0
        self.progress_file = "download_progress.json"
        
        self.setup_driver()
        self.load_progress()
        
    def setup_driver(self):
        """Set up Chrome driver with appropriate options for downloading"""
        chrome_options = Options()
        
        # Set download preferences
        prefs = {
            "download.default_directory": self.download_folder,
            "download.prompt_for_download": False,
            "download.directory_upgrade": True,
            "safebrowsing.enabled": False,
            "safebrowsing.disable_download_protection": True,
            "profile.default_content_setting_values.automatic_downloads": 1,
            "profile.default_content_settings.popups": 0,
            "profile.managed_default_content_settings.images": 2  # Don't load images to speed up
        }
        chrome_options.add_experimental_option("prefs", prefs)
        
        # Additional options for stability and bypassing detection
        chrome_options.add_argument("--no-sandbox")
        chrome_options.add_argument("--disable-dev-shm-usage")
        chrome_options.add_argument("--disable-blink-features=AutomationControlled")
        chrome_options.add_argument("--disable-extensions")
        chrome_options.add_argument("--disable-plugins")
        chrome_options.add_argument("--disable-images")
        chrome_options.add_argument("--disable-javascript-harmony-shipping")
        chrome_options.add_argument("--disable-background-timer-throttling")
        chrome_options.add_argument("--disable-backgrounding-occluded-windows")
        chrome_options.add_argument("--disable-renderer-backgrounding")
        chrome_options.add_argument("--disable-features=TranslateUI")
        chrome_options.add_argument("--disable-popup-blocking")
        chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
        chrome_options.add_experimental_option('useAutomationExtension', False)
        
        # User agent to appear more human
        chrome_options.add_argument("--user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36")
        
        try:
            self.driver = webdriver.Chrome(options=chrome_options)
            
            # Execute scripts to hide automation indicators
            self.driver.execute_script("Object.defineProperty(navigator, 'webdriver', {get: () => undefined})")
            self.driver.execute_script("Object.defineProperty(navigator, 'plugins', {get: () => [1, 2, 3, 4, 5]})")
            self.driver.execute_script("Object.defineProperty(navigator, 'languages', {get: () => ['en-US', 'en']})")
            
            logger.info("Chrome driver initialized successfully")
        except Exception as e:
            logger.error(f"Failed to initialize Chrome driver: {e}")
            raise
    
    def load_progress(self):
        """Load download progress from file"""
        if os.path.exists(self.progress_file):
            try:
                with open(self.progress_file, 'r') as f:
                    progress = json.load(f)
                    self.current_link_index = progress.get('current_index', 0)
                    self.download_links = progress.get('download_links', [])
                    logger.info(f"Loaded progress: starting from link {self.current_link_index + 1}")
            except Exception as e:
                logger.warning(f"Failed to load progress: {e}")
    
    def save_progress(self):
        """Save current download progress to file"""
        try:
            progress = {
                'current_index': self.current_link_index,
                'download_links': self.download_links,
                'last_updated': datetime.now().isoformat()
            }
            with open(self.progress_file, 'w') as f:
                json.dump(progress, f, indent=2)
        except Exception as e:
            logger.warning(f"Failed to save progress: {e}")
    
    def extract_download_links(self, paste_url):
        """Extract all download links from the FitGirl paste URL"""
        try:
            logger.info(f"Extracting download links from: {paste_url}")
            self.driver.get(paste_url)
            
            # Wait for page to load and decrypt
            WebDriverWait(self.driver, 15).until(
                EC.presence_of_element_located((By.TAG_NAME, "body"))
            )
            
            # Wait a bit more for decryption to complete
            time.sleep(5)
            
            # Extract URLs from page text
            content_elements = self.driver.find_elements(By.CSS_SELECTOR, "div, p, pre, textarea")
            all_urls = []
            
            for element in content_elements:
                text = element.text
                if "http" in text:
                    # Extract URLs using regex
                    urls = re.findall(r'https?://[^\s<>"{}|\\^`\[\]]+', text)
                    all_urls.extend(urls)
            
            # Filter for actual download links (excluding the pastebin itself)
            download_links = []
            for url in all_urls:
                if url != paste_url and "paste.fitgirl-repacks.site" not in url:
                    # Extract filename from URL fragment
                    filename = ""
                    if "#" in url:
                        fragment = url.split("#")[1]
                        if ".rar" in fragment or ".bin" in fragment:
                            filename = fragment
                    
                    download_links.append({
                        'url': url,
                        'filename': filename,
                        'downloaded': False
                    })
            
            # Sort links to ensure proper order (part01, part02, etc.)
            download_links.sort(key=lambda x: x['filename'])
            
            self.download_links = download_links
            logger.info(f"Found {len(download_links)} download links")
            
            # Save the links
            self.save_progress()
            return download_links
            
        except Exception as e:
            logger.error(f"Error extracting download links: {e}")
            return []
    
    def wait_for_download_to_complete(self, expected_filename=None):
        """Wait for the current download to complete"""
        logger.info(f"Waiting for download to complete: {expected_filename}")
        
        # Get initial file count and file list
        initial_files = set(os.listdir(self.download_folder))
        initial_count = len(initial_files)
        
        # Wait for download to start (new file appears or .crdownload file)
        download_started = False
        start_time = time.time()
        max_wait_for_start = 60  # 60 seconds to start
        
        logger.info("Waiting for download to start...")
        while not download_started and (time.time() - start_time) < max_wait_for_start:
            current_files = set(os.listdir(self.download_folder))
            new_files = current_files - initial_files
            crdownload_files = [f for f in current_files if f.endswith('.crdownload')]
            
            if new_files or crdownload_files:
                download_started = True
                logger.info("Download started!")
                if new_files:
                    logger.info(f"New file(s) detected: {list(new_files)}")
                if crdownload_files:
                    logger.info(f"Chrome download file(s): {crdownload_files}")
            else:
                time.sleep(2)
        
        if not download_started:
            logger.warning(f"Download may not have started within {max_wait_for_start} seconds")
            return False
        
        # Wait for download to complete (no more .crdownload files)
        logger.info("Download started, waiting for completion...")
        max_download_time = 600  # 10 minutes max per file
        completion_start_time = time.time()
        last_progress_time = time.time()
        
        while (time.time() - completion_start_time) < max_download_time:
            current_files = set(os.listdir(self.download_folder))
            crdownload_files = [f for f in current_files if f.endswith('.crdownload')]
            
            if not crdownload_files:
                # No more .crdownload files - download completed
                final_files = current_files - initial_files
                if final_files:
                    logger.info(f"Download completed! New file(s): {list(final_files)}")
                    return True
                else:
                    logger.warning("No new files found after download completion")
                    return False
            
            # Show progress every 30 seconds
            current_time = time.time()
            if current_time - last_progress_time >= 30:
                if crdownload_files:
                    logger.info(f"Still downloading: {crdownload_files[0]} ({int(current_time - completion_start_time)}s elapsed)")
                last_progress_time = current_time
            
            time.sleep(5)  # Check every 5 seconds
        
        # Timeout
        logger.error(f"Download timeout after {max_download_time} seconds")
        return False
    
    def download_from_fuckingfast(self, url, filename):
        """Download a file from fuckingfast.co"""
        try:
            logger.info(f"Downloading: {filename} from {url}")
            
            # Navigate to the download page
            self.driver.get(url)
            
            # Wait for page to load
            WebDriverWait(self.driver, 20).until(
                EC.presence_of_element_located((By.TAG_NAME, "body"))
            )
            
            # Wait a bit more for any overlays to load
            time.sleep(3)
            
            # Remove any potential overlays that might block clicks
            try:
                self.driver.execute_script("""
                    // Remove any high z-index overlays
                    var overlays = document.querySelectorAll('div[style*="z-index"]');
                    overlays.forEach(function(overlay) {
                        var zIndex = window.getComputedStyle(overlay).zIndex;
                        if (zIndex > 1000) {
                            overlay.style.display = 'none';
                            console.log('Removed overlay with z-index:', zIndex);
                        }
                    });
                    
                    // Remove common ad blocker detection overlays
                    var annoying = document.querySelectorAll('[style*="position: fixed"], [style*="position:fixed"]');
                    annoying.forEach(function(el) {
                        if (el.style.zIndex > 1000) {
                            el.remove();
                        }
                    });
                """)
                logger.info("Removed potential click-blocking overlays")
            except Exception as e:
                logger.debug(f"Failed to remove overlays: {e}")
            
            # Wait for the download button to be present
            try:
                download_button = WebDriverWait(self.driver, 20).until(
                    EC.presence_of_element_located((By.CSS_SELECTOR, "button.link-button.text-5xl.gay-button"))
                )
                
                # Scroll to button
                self.driver.execute_script("arguments[0].scrollIntoView({block: 'center'});", download_button)
                time.sleep(2)
                
                # Use JavaScript click directly (most reliable method based on testing)
                click_successful = False
                
                try:
                    # JavaScript click bypasses overlay issues
                    self.driver.execute_script("arguments[0].click();", download_button)
                    click_successful = True
                    logger.info(f"Successfully clicked download button for {filename}")
                except Exception as e:
                    logger.error(f"JavaScript click failed for {filename}: {e}")
                
                if not click_successful:
                    logger.error(f"Failed to click download button for {filename}")
                    return False
                
                # Wait for download to complete
                success = self.wait_for_download_to_complete(filename)
                
                if success:
                    logger.info(f"Successfully downloaded: {filename}")
                    return True
                else:
                    logger.error(f"Download failed or timed out: {filename}")
                    return False
                    
            except TimeoutException:
                logger.error(f"Download button not found for {filename}")
                return False
                
        except Exception as e:
            logger.error(f"Error downloading {filename}: {e}")
            return False
    
    def download_all_files(self):
        """Download all files in sequence"""
        if not self.download_links:
            logger.error("No download links found. Run extract_download_links first.")
            return
        
        total_files = len(self.download_links)
        logger.info(f"Starting automated download of {total_files} files from index {self.current_link_index}")
        
        while self.current_link_index < total_files:
            link_info = self.download_links[self.current_link_index]
            
            if link_info['downloaded']:
                logger.info(f"Skipping already downloaded file: {link_info['filename']}")
                self.current_link_index += 1
                continue
            
            url = link_info['url']
            filename = link_info['filename']
            
            logger.info(f"="*80)
            logger.info(f"PROGRESS: {self.current_link_index + 1}/{total_files} - {filename}")
            logger.info(f"="*80)
            
            # Download the file
            success = self.download_from_fuckingfast(url, filename)
            
            if success:
                # Mark as downloaded
                self.download_links[self.current_link_index]['downloaded'] = True
                logger.info(f"✓ Successfully downloaded: {filename}")
            else:
                logger.error(f"✗ Failed to download: {filename}")
            
            # Move to next file regardless of success (to avoid infinite loops)
            self.current_link_index += 1
            
            # Save progress after each attempt
            self.save_progress()
            
            # Wait between downloads to be respectful to the server
            if self.current_link_index < total_files:
                logger.info("Waiting 15 seconds before next download...")
                time.sleep(15)
        
        # Final summary
        completed_count = sum(1 for link in self.download_links if link['downloaded'])
        logger.info(f"="*80)
        logger.info(f"DOWNLOAD SUMMARY:")
        logger.info(f"  Total files: {total_files}")
        logger.info(f"  Successfully downloaded: {completed_count}")
        logger.info(f"  Failed downloads: {total_files - completed_count}")
        logger.info(f"="*80)
        
        if completed_count == total_files:
            logger.info("🎉 ALL DOWNLOADS COMPLETED SUCCESSFULLY!")
        else:
            logger.info("⚠️  Some downloads failed. You can run the script again to retry failed downloads.")
        
        logger.info("All downloads processed!")
    
    def resume_downloads(self):
        """Resume downloads from where we left off"""
        if self.download_links:
            self.download_all_files()
        else:
            logger.error("No download links loaded. Extract links first.")
    
    def close(self):
        """Clean up resources"""
        if self.driver:
            self.driver.quit()
            logger.info("Driver closed")

def main():
    """Main function - fully automated"""
    # The paste URL from the user
    paste_url = "https://paste.fitgirl-repacks.site/?94eb73b7278bcadc#DRdroRidyDmXRkS4vKbPSxFgC4Z4sdWiHhtbyoyqDgD1"
    
    # Create downloads folder in current directory
    download_folder = os.path.join(os.getcwd(), "downloads")
    
    logger.info("="*80)
    logger.info("🎮 FITGIRL GAME DOWNLOADER - AUTOMATED MODE")
    logger.info("="*80)
    logger.info(f"Download folder: {download_folder}")
    logger.info(f"Paste URL: {paste_url}")
    
    downloader = FitGirlGameDownloader(download_folder)
    
    try:
        # Check if we have existing progress
        if not downloader.download_links:
            logger.info("No existing progress found. Extracting download links...")
            links = downloader.extract_download_links(paste_url)
            if not links:
                logger.error("❌ Failed to extract download links")
                return
        
        # Show download summary
        total_files = len(downloader.download_links)
        completed_files = sum(1 for link in downloader.download_links if link['downloaded'])
        remaining_files = total_files - completed_files
        
        logger.info("="*80)
        logger.info("📋 DOWNLOAD SUMMARY:")
        logger.info(f"  📁 Total files: {total_files}")
        logger.info(f"  ✅ Completed: {completed_files}")
        logger.info(f"  ⏳ Remaining: {remaining_files}")
        logger.info(f"  💾 Download folder: {download_folder}")
        logger.info("="*80)
        
        if remaining_files > 0:
            logger.info(f"🚀 Starting automated download of {remaining_files} files...")
            logger.info("⏱️  This process is fully automated - no user input required")
            logger.info("🛑 Press Ctrl+C to stop (progress will be saved)")
            logger.info("="*80)
            
            # Start automated downloads
            downloader.download_all_files()
        else:
            logger.info("🎉 All files already downloaded!")
            
    except KeyboardInterrupt:
        logger.info("\n" + "="*80)
        logger.info("🛑 Download interrupted by user")
        logger.info("💾 Progress has been saved")
        logger.info("🔄 Run the script again to resume from where you left off")
        logger.info("="*80)
    except Exception as e:
        logger.error(f"❌ Error in main: {e}")
    finally:
        downloader.close()
        logger.info("🔐 Browser closed")

if __name__ == "__main__":
    main()