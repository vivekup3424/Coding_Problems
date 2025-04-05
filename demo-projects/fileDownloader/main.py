import os
import time
import argparse
import re
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException, NoSuchElementException, StaleElementReferenceException

def clean_url(url):
    """Clean URL strings from various formats"""
    # Remove quotes, commas and trim whitespace
    url = url.strip().strip('"').strip("'").strip(',')
    # Extract the actual URL if there might be multiple formats
    url_match = re.search(r'(https?://[^\s"\']+)', url)
    if url_match:
        return url_match.group(1)
    return url

def check_file_downloaded(download_dir, file_partial_name, timeout=300):
    """
    Check if a file with a specific partial name has been downloaded
    and is no longer a temporary file (*.crdownload, *.part).
    
    Args:
        download_dir: Directory to monitor for downloads
        file_partial_name: Part of the filename to look for
        timeout: Maximum time to wait in seconds
    
    Returns:
        True if file is found and complete, False otherwise
    """
    start_time = time.time()
    while time.time() - start_time < timeout:
        # List all files in the download directory
        try:
            files = os.listdir(download_dir)
            
            # Check if any file matches our partial name
            matching_files = [f for f in files if file_partial_name in f]
            
            # Check if any matching file is not a temporary download file
            complete_files = [f for f in matching_files if not (f.endswith('.crdownload') or f.endswith('.part'))]
            
            if complete_files:
                print(f"✅ Downloaded: {complete_files[0]}")
                return True
        except Exception as e:
            print(f"Error checking downloads: {str(e)}")
            
        # Wait a bit before checking again
        time.sleep(2)
    
    print(f"❌ Download failed or timed out for: {file_partial_name}")
    return False

def setup_driver(download_dir):
    """Configure and return a Chrome WebDriver with custom options"""
    chrome_options = Options()
    
    # Convert WSL path to Windows path for Chrome if needed
    if download_dir.startswith('/mnt/'):
        # Assuming standard WSL path structure
        drive_letter = download_dir.split('/')[2].upper()
        win_path = download_dir.replace(f'/mnt/{download_dir.split("/")[2]}', f'{drive_letter}:')
        win_path = win_path.replace('/', '\\')
        download_dir = win_path
        print(f"🔄 Converted download path to Windows format: {download_dir}")
    
    # Configure download settings
    prefs = {
        "download.default_directory": download_dir,
        "download.prompt_for_download": False,
        "download.directory_upgrade": True,
        "safebrowsing.enabled": False
    }
    chrome_options.add_experimental_option("prefs", prefs)
    
    # Additional options to help avoid detection
    chrome_options.add_argument("--disable-blink-features=AutomationControlled")
    chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
    chrome_options.add_experimental_option('useAutomationExtension', False)
    
    # Add these options to fix the session creation issue
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")
    chrome_options.add_argument("--remote-debugging-port=9222")
    
    # Create a unique user data directory to avoid conflicts
    temp_dir = f"/tmp/chrome_user_data_{int(time.time())}"
    chrome_options.add_argument(f"--user-data-dir={temp_dir}")
    
    try:
        # Try using webdriver_manager to get the correct ChromeDriver
        service = Service(ChromeDriverManager().install())
        driver = webdriver.Chrome(service=service, options=chrome_options)
    except Exception as e:
        print(f"Warning: ChromeDriverManager failed: {e}")
        # Fallback to default Chrome setup
        driver = webdriver.Chrome(options=chrome_options)
    
    # Change the properties of the navigator object at runtime
    driver.execute_script(
        "Object.defineProperty(navigator, 'webdriver', {get: () => undefined})"
    )
    
    return driver

def download_file(driver, url, max_retries=3):
    """
    Navigate to the URL and click the download button, handling any ads
    
    Args:
        driver: Selenium WebDriver instance
        url: URL of the file to download
        max_retries: Maximum number of retry attempts
    
    Returns:
        Partial name of the file being downloaded
    """
    # Clean the URL
    url = clean_url(url)
    
    # Extract the file name from the URL for tracking download progress
    file_name = url.split('#')[1] if '#' in url else url.split('/')[-1]
    
    for attempt in range(max_retries):
        try:
            driver.get(url)
            print(f"📄 Navigated to page for: {file_name}")
            
            # Wait for the page to load
            time.sleep(5)
            
            # Try multiple XPath patterns for the download button
            button_xpaths = [
                "//button[contains(@class, 'link-button') and contains(text(), 'DOWNLOAD')]",
                "//button[contains(text(), 'DOWNLOAD')]",
                "//a[contains(@class, 'download-button')]",
                "//a[contains(text(), 'DOWNLOAD')]"
            ]
            
            download_button = None
            for xpath in button_xpaths:
                try:
                    download_button = WebDriverWait(driver, 10).until(
                        EC.element_to_be_clickable((By.XPATH, xpath))
                    )
                    if download_button:
                        break
                except:
                    continue
            
            if not download_button:
                print(f"⚠️ Download button not found, trying JavaScript click...")
                # Try to find and click the button using JavaScript
                driver.execute_script("""
                    var buttons = document.querySelectorAll('button, a');
                    for(var i=0; i<buttons.length; i++) {
                        if(buttons[i].textContent.includes('DOWNLOAD')) {
                            buttons[i].click();
                            return true;
                        }
                    }
                    return false;
                """)
            else:
                # First click might open an ad
                download_button.click()
                print(f"👆 Clicked download button for: {file_name}")
            
            # Wait a moment for any possible ads to open
            time.sleep(5)
            
            # Switch back to the main window
            main_window = driver.window_handles[0]
            if len(driver.window_handles) > 1:
                print("🪟 Ad window detected, closing it...")
                # Close all other tabs/windows
                for handle in driver.window_handles[1:]:
                    driver.switch_to.window(handle)
                    driver.close()
                # Switch back to main window
                driver.switch_to.window(main_window)
                
                # Find and click the download button again
                for xpath in button_xpaths:
                    try:
                        download_button = WebDriverWait(driver, 10).until(
                            EC.element_to_be_clickable((By.XPATH, xpath))
                        )
                        if download_button:
                            download_button.click()
                            print(f"👆 Clicked download button again (after ad) for: {file_name}")
                            break
                    except:
                        continue
            
            # Sometimes we need to handle another popup or confirmation
            time.sleep(3)
            try:
                # Check for any additional download buttons or confirmations
                confirm_buttons = driver.find_elements(By.XPATH, "//button[contains(text(), 'Download') or contains(text(), 'Confirm') or contains(text(), 'Yes')]")
                if confirm_buttons:
                    confirm_buttons[0].click()
                    print("👆 Clicked confirmation button")
            except Exception as e:
                print(f"Note: No confirmation button needed: {str(e)}")
            
            return file_name
            
        except (TimeoutException, NoSuchElementException, StaleElementReferenceException) as e:
            print(f"⚠️ Attempt {attempt+1}/{max_retries} failed: {str(e)}")
            if attempt == max_retries - 1:
                print(f"❌ All attempts failed for {file_name}")
            else:
                print(f"🔄 Retrying...")
                time.sleep(2)
    
    return file_name

def main():
    # Parse command line arguments
    parser = argparse.ArgumentParser(description='Automated file downloader for FuckingFast.co')
    parser.add_argument('--input', '-i', type=str, required=True, help='Input text file containing links (one per line)')
    parser.add_argument('--output', '-o', type=str, default=os.path.expanduser('/mnt/c/Users/keusu/Downloads'), 
                      help='Directory to save downloaded files (default: /mnt/c/Users/keusu/Downloads')
    parser.add_argument('--start', '-s', type=int, default=0, help='Starting index (0-based) to resume downloads')
    parser.add_argument('--timeout', '-t', type=int, default=300, help='Download timeout in seconds per file')
    args = parser.parse_args()
    
    # Create download directory if it doesn't exist
    download_dir = os.path.abspath(args.output)
    os.makedirs(download_dir, exist_ok=True)
    print(f"📁 Files will be downloaded to: {download_dir}")
    
    # Read links from input file
    with open(args.input, 'r') as f:
        # Read all lines and clean them
        lines = [line.strip() for line in f.readlines() if line.strip()]
        # Filter out empty lines after cleaning
        links = [clean_url(line) for line in lines if clean_url(line)]
    
    print(f"🔗 Found {len(links)} links to process")
    
    if args.start > 0:
        if args.start >= len(links):
            print(f"⚠️ Start index {args.start} is out of range (total links: {len(links)})")
            return
        links = links[args.start:]
        print(f"▶️ Starting from index {args.start}, {len(links)} links remaining")
    
    # Track successful and failed downloads
    successful = 0
    failed = 0
    
    try:
        # Setup WebDriver
        driver = setup_driver(download_dir)
        print("🌐 Browser initialized successfully")
        
        # Process each link
        for i, link in enumerate(links, args.start + 1):
            print(f"\n[{i}/{len(links) + args.start}] Processing: {link}")
            
            # Download the file
            file_partial_name = download_file(driver, link)
            
            # Wait for the download to complete
            if check_file_downloaded(download_dir, file_partial_name, timeout=args.timeout):
                successful += 1
            else:
                failed += 1
                print(f"⚠️ Moving to next link without confirming download completion")
            
            # Short delay between downloads to avoid overwhelming the server
            print(f"⏳ Waiting before next download...")
            time.sleep(5)
        
        print(f"\n✅ Downloads completed! Success: {successful}, Failed: {failed}")
    
    except Exception as e:
        print(f"❌ An error occurred: {str(e)}")
    
    finally:
        # Clean up
        try:
            driver.quit()
            print("🧹 Browser closed successfully")
        except:
            print("⚠️ Failed to close browser properly")

if __name__ == "__main__":
    main()