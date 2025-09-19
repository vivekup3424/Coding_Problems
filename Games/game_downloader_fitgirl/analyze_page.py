import time
import os
import logging
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from bs4 import BeautifulSoup
import requests

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

class FitGirlDownloader:
    def __init__(self, download_folder="downloads"):
        """Initialize the downloader with a specified download folder"""
        self.download_folder = os.path.abspath(download_folder)
        if not os.path.exists(self.download_folder):
            os.makedirs(self.download_folder)
        
        self.driver = None
        self.setup_driver()
        
    def setup_driver(self):
        """Set up Chrome driver with appropriate options"""
        chrome_options = Options()
        # Set download directory
        prefs = {
            "download.default_directory": self.download_folder,
            "download.prompt_for_download": False,
            "download.directory_upgrade": True,
            "safebrowsing.enabled": True
        }
        chrome_options.add_experimental_option("prefs", prefs)
        chrome_options.add_argument("--no-sandbox")
        chrome_options.add_argument("--disable-dev-shm-usage")
        
        try:
            self.driver = webdriver.Chrome(options=chrome_options)
            logger.info("Chrome driver initialized successfully")
        except Exception as e:
            logger.error(f"Failed to initialize Chrome driver: {e}")
            raise
    
    def analyze_page_structure(self, url):
        """Analyze the structure of the target page to understand how to extract links"""
        try:
            logger.info(f"Analyzing page structure for: {url}")
            self.driver.get(url)
            
            # Wait for page to load
            time.sleep(5)
            
            # Get page source and parse with BeautifulSoup
            page_source = self.driver.page_source
            soup = BeautifulSoup(page_source, 'html.parser')
            
            # Save page source for inspection
            with open("page_source.html", "w", encoding="utf-8") as f:
                f.write(page_source)
            
            # Look for common link patterns
            links = soup.find_all("a", href=True)
            logger.info(f"Found {len(links)} links on the page")
            
            # Print all links for analysis
            for i, link in enumerate(links[:20]):  # Show first 20 links
                logger.info(f"Link {i+1}: {link.get('href')} - Text: {link.get_text().strip()}")
            
            # Look for buttons
            buttons = soup.find_all("button")
            logger.info(f"Found {len(buttons)} buttons on the page")
            
            for i, button in enumerate(buttons):
                logger.info(f"Button {i+1}: {button.get_text().strip()} - Class: {button.get('class')}")
            
            return links, buttons
            
        except Exception as e:
            logger.error(f"Error analyzing page structure: {e}")
            return [], []
    
    def extract_download_links(self, url):
        """Extract all download links from the main page"""
        try:
            logger.info(f"Extracting download links from: {url}")
            self.driver.get(url)
            
            # Wait for the page to load completely
            WebDriverWait(self.driver, 10).until(
                EC.presence_of_element_located((By.TAG_NAME, "body"))
            )
            
            # Try different selectors for download links
            possible_selectors = [
                "a[href*='download']",
                "a[href*='.rar']",
                "a[href*='part']",
                "a[href*='mega.nz']",
                "a[href*='1fichier']",
                "a[href*='uploaded']",
                "a[class*='link']",
                "a[class*='download']"
            ]
            
            download_links = []
            
            for selector in possible_selectors:
                try:
                    elements = self.driver.find_elements(By.CSS_SELECTOR, selector)
                    for element in elements:
                        href = element.get_attribute("href")
                        text = element.text.strip()
                        if href and href not in [link[0] for link in download_links]:
                            download_links.append((href, text))
                            logger.info(f"Found download link: {href} - {text}")
                except Exception as e:
                    logger.debug(f"Selector {selector} failed: {e}")
            
            # Also try to find links in the decrypted content (if it's a pastebin)
            try:
                # Wait a bit more for decryption
                time.sleep(3)
                
                # Look for text content that might contain links
                content_elements = self.driver.find_elements(By.CSS_SELECTOR, "div, p, pre, textarea")
                for element in content_elements:
                    text = element.text
                    if "http" in text:
                        # Extract URLs from text using regex
                        import re
                        urls = re.findall(r'https?://[^\s<>"{}|\\^`]+', text)
                        for url in urls:
                            if url not in [link[0] for link in download_links]:
                                download_links.append((url, "Found in text"))
                                logger.info(f"Found URL in text: {url}")
                        
            except Exception as e:
                logger.debug(f"Error extracting from text content: {e}")
            
            logger.info(f"Total download links found: {len(download_links)}")
            return download_links
            
        except Exception as e:
            logger.error(f"Error extracting download links: {e}")
            return []
    
    def close(self):
        """Close the driver"""
        if self.driver:
            self.driver.quit()
            logger.info("Driver closed")

def main():
    """Main function to test the analyzer"""
    url = "https://paste.fitgirl-repacks.site/?94eb73b7278bcadc#DRdroRidyDmXRkS4vKbPSxFgC4Z4sdWiHhtbyoyqDgD1"
    
    downloader = FitGirlDownloader()
    
    try:
        # Analyze page structure first
        links, buttons = downloader.analyze_page_structure(url)
        
        # Try to extract download links
        download_links = downloader.extract_download_links(url)
        
        print(f"\n=== ANALYSIS COMPLETE ===")
        print(f"Found {len(download_links)} potential download links")
        for i, (link, text) in enumerate(download_links, 1):
            print(f"{i}. {link} - {text}")
            
    except Exception as e:
        logger.error(f"Error in main: {e}")
    finally:
        downloader.close()

if __name__ == "__main__":
    main()