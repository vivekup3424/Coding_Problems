#!/usr/bin/env python3
"""
Auto-start script for FitGirl Game Downloader - No user input required
"""

import sys
import os
import time

# Add current directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from fitgirl_downloader import main

if __name__ == "__main__":
    print("🎮 FitGirl Game Downloader - Auto Start")
    print("="*50)
    print("Starting in 3 seconds... (Ctrl+C to cancel)")
    
    try:
        for i in range(3, 0, -1):
            print(f"⏳ {i}...")
            time.sleep(1)
        
        print("🚀 Starting automated download process...")
        print("")
        
        main()
        
    except KeyboardInterrupt:
        print("\n❌ Cancelled by user")
        sys.exit(0)