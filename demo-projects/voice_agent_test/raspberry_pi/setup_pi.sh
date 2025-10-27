#!/bin/bash
#
# Raspberry Pi Voice Assistant Setup Script
# Sets up the voice assistant on a Raspberry Pi with all dependencies
#

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored messages
print_info() {
    echo -e "${BLUE}ℹ ${NC}$1"
}

print_success() {
    echo -e "${GREEN}✅${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠️ ${NC} $1"
}

print_error() {
    echo -e "${RED}❌${NC} $1"
}

print_header() {
    echo ""
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================${NC}"
    echo ""
}

# Check if running on Raspberry Pi
check_raspberry_pi() {
    if [[ ! -f /proc/device-tree/model ]] || ! grep -q "Raspberry Pi" /proc/device-tree/model 2>/dev/null; then
        print_warning "This doesn't appear to be a Raspberry Pi"
        print_warning "The script will continue, but some features may not work correctly"
        read -p "Continue anyway? (y/n) " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            exit 1
        fi
    else
        PI_MODEL=$(cat /proc/device-tree/model)
        print_success "Detected: $PI_MODEL"
    fi
}

# Update system packages
update_system() {
    print_header "Updating System Packages"
    
    print_info "Updating package lists..."
    sudo apt update
    
    print_info "Upgrading installed packages..."
    sudo apt upgrade -y
    
    print_success "System updated"
}

# Install system dependencies
install_system_dependencies() {
    print_header "Installing System Dependencies"
    
    print_info "Installing audio and Python development packages..."
    sudo apt install -y \
        python3-pip \
        python3-dev \
        python3-venv \
        portaudio19-dev \
        libportaudio2 \
        libasound2-dev \
        alsa-utils \
        git \
        curl
    
    print_success "System dependencies installed"
}

# Create Python virtual environment
setup_python_venv() {
    print_header "Setting up Python Virtual Environment"
    
    cd "$SCRIPT_DIR"
    
    if [ -d "venv" ]; then
        print_warning "Virtual environment already exists"
        read -p "Remove and recreate? (y/n) " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            rm -rf venv
        else
            print_info "Using existing virtual environment"
            return
        fi
    fi
    
    print_info "Creating virtual environment..."
    python3 -m venv venv
    
    print_info "Activating virtual environment..."
    source venv/bin/activate
    
    print_info "Upgrading pip..."
    pip install --upgrade pip
    
    print_success "Virtual environment created"
}

# Install Python dependencies
install_python_dependencies() {
    print_header "Installing Python Dependencies"
    
    cd "$SCRIPT_DIR"
    source venv/bin/activate
    
    print_info "Installing required packages..."
    pip install -r requirements.txt
    
    print_success "Python dependencies installed"
}

# Download openWakeWord models
download_wake_word_models() {
    print_header "Downloading Wake Word Models"
    
    source "$SCRIPT_DIR/venv/bin/activate"
    
    print_info "Downloading openWakeWord models..."
    python3 << 'EOF'
from openwakeword.model import Model
import os

print("📦 Downloading wake word models...")
# This will download the default models on first run
model = Model()
print("✅ Models downloaded successfully!")
print(f"   Available models: {', '.join(model.models.keys())}")
EOF
    
    print_success "Wake word models downloaded"
}

# Configure audio devices
configure_audio() {
    print_header "Audio Configuration"
    
    print_info "Testing audio devices..."
    
    # List audio devices
    source "$SCRIPT_DIR/venv/bin/activate"
    python3 << 'EOF'
import pyaudio

p = pyaudio.PyAudio()
print("\n🎤 Available Audio Input Devices:\n")
print("-" * 60)

for i in range(p.get_device_count()):
    device_info = p.get_device_info_by_index(i)
    if device_info['maxInputChannels'] > 0:
        print(f"Device {i}: {device_info['name']}")
        print(f"  Sample Rate: {int(device_info['defaultSampleRate'])} Hz")
        print(f"  Channels: {device_info['maxInputChannels']}")
        print()

p.terminate()
EOF
    
    print_info "If your microphone isn't listed, check connections and run 'arecord -l'"
}

# Setup environment file
setup_environment() {
    print_header "Environment Configuration"
    
    cd "$SCRIPT_DIR"
    
    if [ -f ".env" ]; then
        print_warning ".env file already exists"
        read -p "Overwrite with example? (y/n) " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            print_info "Keeping existing .env file"
            return
        fi
    fi
    
    print_info "Copying .env.example to .env..."
    cp .env.example .env
    
    print_warning "IMPORTANT: Edit .env file with your LiveKit credentials"
    print_info "Required settings:"
    print_info "  - LIVEKIT_URL"
    print_info "  - LIVEKIT_API_KEY"
    print_info "  - LIVEKIT_API_SECRET"
    print_info ""
    print_info "Run: nano .env"
}

# Test wake word detection
test_wake_word() {
    print_header "Testing Wake Word Detection"
    
    print_info "You can test the wake word detector by running:"
    print_info "  cd $SCRIPT_DIR"
    print_info "  source venv/bin/activate"
    print_info "  python wake_word_detector.py"
    print_info ""
    
    read -p "Run test now? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        cd "$SCRIPT_DIR"
        source venv/bin/activate
        print_info "Starting wake word test... (Press Ctrl+C to stop)"
        print_info "Say 'Alexa' to test detection"
        sleep 2
        python wake_word_detector.py || true
    fi
}

# Create startup script
create_startup_script() {
    print_header "Creating Startup Script"
    
    cat > "$SCRIPT_DIR/start.sh" << 'EOF'
#!/bin/bash
# Start Voice Assistant

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR"
source venv/bin/activate
python voice_assistant_client.py
EOF
    
    chmod +x "$SCRIPT_DIR/start.sh"
    
    print_success "Created start.sh script"
    print_info "Run the voice assistant with: ./start.sh"
}

# Main installation flow
main() {
    print_header "Raspberry Pi Voice Assistant Setup"
    
    check_raspberry_pi
    update_system
    install_system_dependencies
    setup_python_venv
    install_python_dependencies
    download_wake_word_models
    configure_audio
    setup_environment
    create_startup_script
    
    print_header "Setup Complete! 🎉"
    
    print_success "Installation finished successfully!"
    print_info ""
    print_info "Next steps:"
    print_info "  1. Edit .env file with your LiveKit credentials:"
    print_info "     nano $SCRIPT_DIR/.env"
    print_info ""
    print_info "  2. Test wake word detection:"
    print_info "     cd $SCRIPT_DIR && source venv/bin/activate"
    print_info "     python wake_word_detector.py"
    print_info ""
    print_info "  3. Start the voice assistant:"
    print_info "     cd $SCRIPT_DIR"
    print_info "     ./start.sh"
    print_info ""
    print_info "  4. (Optional) Set up autostart with systemd"
    print_info ""
    
    # Offer to test
    test_wake_word
}

# Run main installation
main
