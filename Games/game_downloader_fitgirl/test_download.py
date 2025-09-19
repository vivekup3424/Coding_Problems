import time
import os
import logging
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import TimeoutException

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

def test_single_download():
    """Test downloading a single file to verify the process works"""
    
    # Test URL (first part)
    test_url = "https://fuckingfast.co/qqo4zo00xjby#Clair_Obscur_Expedition_33_--_fitgirl-repacks.site_--_.part01.rar"
    
    # Setup download folder
    download_folder = os.path.join(os.getcwd(), "test_downloads")
    if not os.path.exists(download_folder):
        os.makedirs(download_folder)
    
    # Setup Chrome driver
    chrome_options = Options()
    prefs = {
        "download.default_directory": download_folder,
        "download.prompt_for_download": False,
        "download.directory_upgrade": True,
        "safebrowsing.enabled": False,
        "safebrowsing.disable_download_protection": True,
        "profile.default_content_setting_values.automatic_downloads": 1
    }
    chrome_options.add_experimental_option("prefs", prefs)
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")
    
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        logger.info(f"Testing download from: {test_url}")
        driver.get(test_url)
        
        # Wait for page to load
        WebDriverWait(driver, 20).until(
            EC.presence_of_element_located((By.TAG_NAME, "body"))
        )
        
        # Save page source for debugging
        with open("test_page_source.html", "w", encoding="utf-8") as f:
            f.write(driver.page_source)
        
        # Look for download button variations
        button_selectors = [
            "button.link-button.text-5xl.gay-button",  # Original selector
            "button[contains(@class, 'link-button')]",
            "button[contains(@class, 'gay-button')]",
            "button[contains(text(), 'DOWNLOAD')]",
            "button[contains(text(), 'Download')]",
            ".link-button",
            "button.link-button",
            "a.link-button"
        ]
        
        download_button = None
        
        for selector in button_selectors:
            try:
                if selector.startswith("button[contains"):
                    # XPath selector
                    download_button = WebDriverWait(driver, 10).until(
                        EC.element_to_be_clickable((By.XPATH, f"//{selector}"))
                    )
                else:
                    # CSS selector
                    download_button = WebDriverWait(driver, 10).until(
                        EC.element_to_be_clickable((By.CSS_SELECTOR, selector))
                    )
                logger.info(f"Found download button with selector: {selector}")
                break
            except TimeoutException:
                logger.debug(f"Selector failed: {selector}")
                continue
        
        if not download_button:
            logger.error("No download button found. Check page source in test_page_source.html")
            return False
        
        # Get initial file count
        initial_files = set(os.listdir(download_folder))
        
        # Click download button
        driver.execute_script("arguments[0].scrollIntoView();", download_button)
        time.sleep(2)
        download_button.click()
        
        logger.info("Clicked download button, waiting for download to start...")
        
        # Wait for download to start (new file or .crdownload file)
        download_started = False
        start_time = time.time()
        
        while not download_started and (time.time() - start_time) < 60:
            current_files = set(os.listdir(download_folder))
            new_files = current_files - initial_files
            
            if new_files or any(f.endswith('.crdownload') for f in current_files):
                download_started = True
                logger.info("Download started!")
                if new_files:
                    logger.info(f"New file(s): {new_files}")
            else:
                time.sleep(3)
        
        if not download_started:
            logger.error("Download did not start within 60 seconds")
            return False
        
        # Wait for download to complete
        logger.info("Waiting for download to complete...")
        while True:
            current_files = os.listdir(download_folder)
            crdownload_files = [f for f in current_files if f.endswith('.crdownload')]
            
            if not crdownload_files:
                logger.info("Download completed!")
                final_files = set(os.listdir(download_folder))
                new_files = final_files - initial_files
                logger.info(f"Downloaded file(s): {new_files}")
                return True
            
            if crdownload_files:
                logger.info(f"Still downloading: {crdownload_files[0]}")
            
            time.sleep(5)
            
    except Exception as e:
        logger.error(f"Error during test: {e}")
        return False
    finally:
        driver.quit()

if __name__ == "__main__":
    logger.info("Testing single download...")
    success = test_single_download()
    if success:
        logger.info("Test successful! The downloader should work.")
    else:
        logger.error("Test failed. Check the logs and page source.")