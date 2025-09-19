import time
import os
import logging
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.action_chains import ActionChains
from selenium.common.exceptions import TimeoutException

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

def debug_download_page():
    """Debug the download page to understand the overlay issue"""
    
    # Test URL (first part)
    test_url = "https://fuckingfast.co/qqo4zo00xjby#Clair_Obscur_Expedition_33_--_fitgirl-repacks.site_--_.part01.rar"
    
    # Setup Chrome driver with better options
    chrome_options = Options()
    prefs = {
        "download.default_directory": os.getcwd(),
        "download.prompt_for_download": False,
        "download.directory_upgrade": True,
        "safebrowsing.enabled": False,
        "profile.default_content_settings.popups": 0
    }
    chrome_options.add_experimental_option("prefs", prefs)
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")
    chrome_options.add_argument("--disable-blink-features=AutomationControlled")
    chrome_options.add_argument("--disable-extensions")
    chrome_options.add_argument("--disable-popup-blocking")
    chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
    chrome_options.add_experimental_option('useAutomationExtension', False)
    
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        # Execute anti-detection scripts
        driver.execute_script("Object.defineProperty(navigator, 'webdriver', {get: () => undefined})")
        
        logger.info(f"Navigating to: {test_url}")
        driver.get(test_url)
        
        # Wait for page to load
        WebDriverWait(driver, 20).until(
            EC.presence_of_element_located((By.TAG_NAME, "body"))
        )
        
        # Wait a bit more
        time.sleep(5)
        
        # Save page source for inspection
        with open("debug_page_source.html", "w", encoding="utf-8") as f:
            f.write(driver.page_source)
        logger.info("Saved page source to debug_page_source.html")
        
        # Look for overlays
        overlays = driver.execute_script("""
            var overlays = [];
            var allElements = document.querySelectorAll('*');
            
            allElements.forEach(function(el) {
                var style = window.getComputedStyle(el);
                if ((style.position === 'fixed' || style.position === 'absolute') && 
                    parseInt(style.zIndex) > 1000) {
                    overlays.push({
                        tagName: el.tagName,
                        className: el.className,
                        zIndex: style.zIndex,
                        position: style.position,
                        display: style.display,
                        innerHTML: el.innerHTML.substring(0, 100)
                    });
                }
            });
            
            return overlays;
        """)
        
        logger.info(f"Found {len(overlays)} potential blocking overlays:")
        for i, overlay in enumerate(overlays):
            logger.info(f"  Overlay {i+1}: {overlay}")
        
        # Try to find the download button
        try:
            download_button = driver.find_element(By.CSS_SELECTOR, "button.link-button.text-5xl.gay-button")
            logger.info("Found download button!")
            
            # Get button info
            button_info = driver.execute_script("""
                var btn = arguments[0];
                var rect = btn.getBoundingClientRect();
                return {
                    text: btn.innerText,
                    visible: btn.offsetParent !== null,
                    enabled: !btn.disabled,
                    rect: {
                        x: rect.x,
                        y: rect.y,
                        width: rect.width,
                        height: rect.height
                    }
                };
            """, download_button)
            
            logger.info(f"Button info: {button_info}")
            
        except Exception as e:
            logger.error(f"Download button not found: {e}")
            
            # Look for any buttons
            all_buttons = driver.find_elements(By.TAG_NAME, "button")
            logger.info(f"Found {len(all_buttons)} buttons on page:")
            for i, btn in enumerate(all_buttons):
                try:
                    text = btn.text.strip()
                    classes = btn.get_attribute("class")
                    logger.info(f"  Button {i+1}: '{text}' - classes: '{classes}'")
                except:
                    pass
        
        # Now try to remove overlays and click
        logger.info("Attempting to remove overlays...")
        
        removed_count = driver.execute_script("""
            var removed = 0;
            
            // Method 1: Remove high z-index divs
            var highZDivs = document.querySelectorAll('div');
            highZDivs.forEach(function(div) {
                var style = window.getComputedStyle(div);
                if ((style.position === 'fixed' || style.position === 'absolute') && 
                    parseInt(style.zIndex) > 1000 && 
                    !div.querySelector('button')) {
                    div.remove();
                    removed++;
                }
            });
            
            // Method 2: Hide elements with very high z-index
            var allElements = document.querySelectorAll('*');
            allElements.forEach(function(el) {
                var style = window.getComputedStyle(el);
                if (parseInt(style.zIndex) > 2000000) {
                    el.style.display = 'none';
                    removed++;
                }
            });
            
            return removed;
        """)
        
        logger.info(f"Removed/hidden {removed_count} overlay elements")
        
        # Now try clicking
        try:
            download_button = driver.find_element(By.CSS_SELECTOR, "button.link-button.text-5xl.gay-button")
            
            # Try different click methods
            methods = [
                ("Regular click", lambda btn: btn.click()),
                ("JavaScript click", lambda btn: driver.execute_script("arguments[0].click();", btn)),
                ("ActionChains click", lambda btn: ActionChains(driver).move_to_element(btn).click().perform()),
            ]
            
            for method_name, method_func in methods:
                try:
                    logger.info(f"Trying {method_name}...")
                    method_func(download_button)
                    logger.info(f"✓ {method_name} succeeded!")
                    
                    # Wait a bit to see if download starts
                    time.sleep(3)
                    break
                    
                except Exception as e:
                    logger.info(f"✗ {method_name} failed: {e}")
                    
        except Exception as e:
            logger.error(f"Could not find download button after cleanup: {e}")
        
        logger.info("Debug complete. Check the logs and debug_page_source.html")
        input("Press Enter to close browser...")
        
    except Exception as e:
        logger.error(f"Error during debug: {e}")
    finally:
        driver.quit()

if __name__ == "__main__":
    logger.info("Starting debug session...")
    debug_download_page()