#!/bin/bash

# RASA Home Automation Assistant - Quick Setup Script

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Print functions
print_header() {
    echo -e "${BLUE}============================================${NC}"
    echo -e "${BLUE}  🏠 RASA Home Automation Assistant Setup  ${NC}"
    echo -e "${BLUE}============================================${NC}"
}

print_step() {
    echo -e "${YELLOW}➤ $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

# Check if Docker is installed
check_docker() {
    if ! command -v docker &> /dev/null; then
        print_error "Docker is not installed. Please install Docker first."
        echo "Visit: https://docs.docker.com/get-docker/"
        exit 1
    fi
    print_success "Docker is installed"
}

# Check if Docker Compose is installed
check_docker_compose() {
    if ! command -v docker-compose &> /dev/null; then
        print_error "Docker Compose is not installed. Please install Docker Compose first."
        echo "Visit: https://docs.docker.com/compose/install/"
        exit 1
    fi
    print_success "Docker Compose is installed"
}

# Build Docker image
build_image() {
    print_step "Building Docker image..."
    docker build -t rasa-home-automation . || {
        print_error "Failed to build Docker image"
        exit 1
    }
    print_success "Docker image built successfully"
}

# Validate training data
validate_data() {
    print_step "Validating training data..."
    docker run --rm -v $(pwd):/app rasa-home-automation rasa data validate || {
        print_error "Data validation failed"
        exit 1
    }
    print_success "Training data is valid"
}

# Train the model
train_model() {
    print_step "Training RASA model (this may take a few minutes)..."
    docker run --rm -v $(pwd):/app rasa-home-automation rasa train || {
        print_error "Model training failed"
        exit 1
    }
    print_success "Model trained successfully"
}

# Test NLU
test_nlu() {
    print_step "Testing NLU model..."
    docker run --rm -v $(pwd):/app rasa-home-automation rasa test nlu --nlu data/test_data.yml || {
        print_error "NLU testing failed"
        exit 1
    }
    print_success "NLU testing completed"
}

# Show usage instructions
show_usage() {
    print_info "Setup completed! Here's how to use your assistant:"
    echo ""
    echo -e "${YELLOW}Option 1: Using Docker Compose (Recommended)${NC}"
    echo "  1. Start action server:    docker-compose --profile run up rasa-actions -d"
    echo "  2. Start interactive chat: docker-compose --profile shell up rasa-shell"
    echo "  3. OR start API server:    docker-compose --profile run up rasa-server -d"
    echo ""
    echo -e "${YELLOW}Option 2: Using Docker directly${NC}"
    echo "  1. Start action server:    docker run --rm -p 5055:5055 -v \$(pwd):/app rasa-home-automation rasa run actions &"
    echo "  2. Start interactive chat: docker run --rm -it -v \$(pwd):/app rasa-home-automation rasa shell"
    echo ""
    echo -e "${YELLOW}Option 3: Using local installation${NC}"
    echo "  1. Install dependencies:   pip install -r requirements.txt && python -m spacy download en_core_web_md"
    echo "  2. Use the run script:     ./run.sh all"
    echo ""
    echo -e "${YELLOW}Example commands to try:${NC}"
    echo "  • Turn on the bedroom fan"
    echo "  • Set AC temperature to 22 degrees"
    echo "  • Turn on kitchen lights"
    echo "  • Change living room lights to blue"
    echo "  • Switch to reading mode in the study"
    echo ""
    echo -e "${GREEN}🎉 Happy automating!${NC}"
}

# Main setup process
main() {
    print_header
    
    print_step "Checking prerequisites..."
    check_docker
    check_docker_compose
    
    build_image
    validate_data
    train_model
    
    # Optional: Run tests
    if [ "${1}" == "--with-tests" ]; then
        test_nlu
    fi
    
    print_success "Setup completed successfully!"
    show_usage
}

# Run main function
main "$@"
