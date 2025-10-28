#!/usr/bin/env python3
"""
Download pre-trained models for OpenWakeWord
This script uses OpenWakeWord's built-in model fetching mechanism.
"""

import sys

def main():
    """Main function to download models using OpenWakeWord's fetch feature"""
    print("="*60)
    print("OpenWakeWord Model Downloader")
    print("="*60)
    print()
    
    try:
        from openwakeword import utils
        print("Fetching available pre-trained models from OpenWakeWord...")
        print()
        
        # Download the hey_mycroft model
        model_name = "hey_mycroft_v0.1"
        print(f"Downloading model: {model_name}")
        
        try:
            # Use OpenWakeWord's download utility
            model_path = utils.download_models([model_name])
            print(f"✓ Model downloaded successfully!")
            print(f"  Location: {model_path}")
        except Exception as e:
            print(f"✗ Error downloading model: {e}")
            print("\nTrying alternative method...")
            
            # Alternative: use openwakeword CLI
            import subprocess
            result = subprocess.run(
                [sys.executable, "-m", "openwakeword", "--download-model", model_name],
                capture_output=True,
                text=True
            )
            
            if result.returncode == 0:
                print("✓ Model downloaded successfully!")
            else:
                print(f"✗ Download failed: {result.stderr}")
                print("\nPlease try manual installation:")
                print("1. Visit: https://github.com/dscripka/openWakeWord")
                print("2. Or use: python -m openwakeword --download-models")
                sys.exit(1)
        
    except ImportError:
        print("Error: openwakeword package not found. Please install it first:")
        print("  pip install openwakeword")
        sys.exit(1)
    
    print()
    print("="*60)
    print("✓ Setup complete! You can now run: python wake_word.py")
    print("="*60)

if __name__ == "__main__":
    main()
