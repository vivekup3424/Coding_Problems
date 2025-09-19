# FitGirl Repacks Game Downloader

This Python script automates the process of downloading FitGirl repack games from paste sites that contain multiple RAR file links.

## Features

- **Automatic Link Extraction**: Extracts all download links from FitGirl paste URLs
- **Sequential Downloads**: Downloads files one by one in the correct order (part01, part02, etc.)
- **Progress Tracking**: Saves progress and can resume interrupted downloads
- **Download Monitoring**: Waits for each download to complete before moving to the next
- **Error Handling**: Robust error handling and logging
- **Browser Automation**: Uses Selenium to handle dynamic content and click download buttons

## Setup

### 1. Install Requirements

Make sure you have Python 3.7+ installed, then:

```bash
# Create and activate virtual environment
python -m venv venv
.\venv\Scripts\Activate.ps1   # Windows PowerShell
# or
source venv/bin/activate      # Linux/Mac

# Install dependencies
pip install -r requirements.txt
```

### 2. Chrome Driver

This script uses Chrome WebDriver. Make sure you have Google Chrome installed. The script will automatically download the appropriate ChromeDriver.

## Usage

### Quick Start

1. **Edit the script** to set your paste URL:
   ```python
   paste_url = "https://paste.fitgirl-repacks.site/?YOUR_PASTE_ID_HERE"
   ```

2. **Run the main script**:
   ```bash
   python fitgirl_downloader.py
   ```

### Test Single Download

Before running the full batch, test with a single file:

```bash
python test_download.py
```

### Resume Interrupted Downloads

The script automatically saves progress. If interrupted, simply run it again and it will resume from where it left off.

## Files Description

- **`fitgirl_downloader.py`** - Main downloader script
- **`test_download.py`** - Test script for single file download
- **`analyze_page.py`** - Page analysis script (for debugging)
- **`requirements.txt`** - Python dependencies
- **`download_progress.json`** - Progress tracking file (auto-generated)

## How It Works

1. **Link Extraction**: The script visits the FitGirl paste URL and extracts all download links from the decrypted content
2. **Sequential Processing**: Downloads are processed in order (part01, part02, etc.)
3. **Browser Automation**: For each link, the script:
   - Opens the download page (e.g., fuckingfast.co)
   - Finds and clicks the download button
   - Waits for the download to complete
   - Moves to the next file
4. **Progress Saving**: After each file, progress is saved so downloads can be resumed

## Configuration

You can customize the downloader behavior by modifying the `FitGirlGameDownloader` class parameters:

```python
downloader = FitGirlGameDownloader(
    download_folder="downloads",  # Where to save files
    timeout=60                    # Timeout for page loads
)
```

## Troubleshooting

### Common Issues

1. **Chrome driver not found**: Make sure Chrome browser is installed
2. **Download button not found**: The site might have changed its layout. Check `test_page_source.html` for debugging
3. **Downloads not starting**: Check your Chrome download settings and antivirus software
4. **Slow downloads**: The script waits between downloads to be respectful to the server

### Debug Mode

For debugging, check the log output and the generated HTML files:
- `page_source.html` - Source of the main paste page
- `test_page_source.html` - Source of a download page

### Manual Intervention

If a download fails, you can:
1. Download the file manually
2. Place it in the downloads folder
3. Edit `download_progress.json` to mark it as downloaded
4. Resume the script

## Important Notes

- **Be Respectful**: The script includes delays between downloads to avoid overloading servers
- **Legal Use**: Only use this for content you legally own or have permission to download
- **Antivirus**: Some antivirus software may flag downloaded files - this is normal for game files
- **Storage Space**: Make sure you have enough disk space (games can be 50GB+ when unpacked)

## Download Progress Structure

The script saves progress in `download_progress.json`:

```json
{
  "current_index": 5,
  "download_links": [
    {
      "url": "https://fuckingfast.co/...",
      "filename": "game.part01.rar",
      "downloaded": true
    }
  ],
  "last_updated": "2024-01-01T12:00:00"
}
```

## Supported Sites

Currently supports:
- fuckingfast.co
- Can be extended to support other file hosting services

## License

This project is for educational purposes only. Use responsibly and in accordance with applicable laws and terms of service.