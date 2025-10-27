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
