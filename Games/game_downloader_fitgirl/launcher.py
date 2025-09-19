#!/usr/bin/env python3
"""
Simple launcher for FitGirl Game Downloader
"""

import sys
import os
from fitgirl_downloader import FitGirlGameDownloader

def main():
    print("=" * 60)
    print("         FitGirl Repacks Game Downloader")
    print("=" * 60)
    print()
    
    # Get paste URL from user
    default_url = "https://paste.fitgirl-repacks.site/?94eb73b7278bcadc#DRdroRidyDmXRkS4vKbPSxFgC4Z4sdWiHhtbyoyqDgD1"
    
    print("Enter the FitGirl paste URL (or press Enter for default):")
    paste_url = input().strip()
    
    if not paste_url:
        paste_url = default_url
        print(f"Using default URL: {paste_url}")
    
    # Validate URL
    if not paste_url.startswith("https://paste.fitgirl-repacks.site/"):
        print("ERROR: Please provide a valid FitGirl paste URL")
        sys.exit(1)
    
    # Get download folder
    print("\nEnter download folder (or press Enter for 'downloads'):")
    download_folder = input().strip()
    
    if not download_folder:
        download_folder = "downloads"
    
    download_folder = os.path.abspath(download_folder)
    print(f"Download folder: {download_folder}")
    
    # Create downloader
    print("\nInitializing downloader...")
    downloader = FitGirlGameDownloader(download_folder)
    
    try:
        # Check for existing progress
        if downloader.download_links:
            total_files = len(downloader.download_links)
            completed_files = sum(1 for link in downloader.download_links if link['downloaded'])
            print(f"\nFound existing progress:")
            print(f"  Total files: {total_files}")
            print(f"  Completed: {completed_files}")
            print(f"  Remaining: {total_files - completed_files}")
            
            if completed_files < total_files:
                choice = input("\nResume downloads? (y/n): ").lower()
                if choice == 'y':
                    downloader.download_all_files()
                    return
        
        # Extract links
        print("\nExtracting download links...")
        links = downloader.extract_download_links(paste_url)
        
        if not links:
            print("ERROR: No download links found!")
            return
        
        print(f"\nFound {len(links)} files to download:")
        for i, link in enumerate(links[:5], 1):  # Show first 5
            print(f"  {i}. {link['filename']}")
        
        if len(links) > 5:
            print(f"  ... and {len(links) - 5} more files")
        
        # Confirm download
        total_size_est = len(links) * 500  # Rough estimate: 500MB per file
        print(f"\nEstimated download size: ~{total_size_est:.1f} MB")
        print(f"Files will be saved to: {download_folder}")
        
        choice = input("\nStart downloading? (y/n): ").lower()
        if choice == 'y':
            print("\nStarting downloads...")
            print("You can interrupt with Ctrl+C and resume later")
            print("-" * 50)
            downloader.download_all_files()
        else:
            print("Download cancelled.")
    
    except KeyboardInterrupt:
        print("\n\nDownload interrupted by user.")
        print("Progress has been saved. Run the script again to resume.")
    
    except Exception as e:
        print(f"\nERROR: {e}")
        print("Check the logs for more details.")
    
    finally:
        downloader.close()
        print("\nDownloader closed.")

if __name__ == "__main__":
    main()