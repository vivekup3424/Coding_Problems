#!/bin/bash

# RASA Home Automation Assistant - Training and Running Script

set -e

echo "🏠 RASA Home Automation Assistant Setup"
echo "======================================"

# Function to print colored output
print_status() {
    echo -e "\033[1;34m$1\033[0m"
}

print_success() {
    echo -e "\033[1;32m$1\033[0m"
}

print_error() {
    echo -e "\033[1;31m$1\033[0m"
}

# Check if rasa is installed
if ! command -v rasa &> /dev/null; then
    print_error "RASA is not installed. Please install requirements first:"
    echo "pip install -r requirements.txt"
    exit 1
fi

# Training function
train_model() {
    print_status "Training RASA model..."
    rasa train --config config.yml --domain domain.yml --data data/
    
    if [ $? -eq 0 ]; then
        print_success "✅ Model training completed successfully!"
    else
        print_error "❌ Model training failed!"
        exit 1
    fi
}

# Test NLU function
test_nlu() {
    print_status "Testing NLU model..."
    rasa test nlu --nlu data/nlu.yml
    
    if [ $? -eq 0 ]; then
        print_success "✅ NLU testing completed!"
    else
        print_error "❌ NLU testing failed!"
    fi
}

# Run action server function
run_actions() {
    print_status "Starting action server..."
    print_status "Press Ctrl+C to stop the action server"
    rasa run actions --port 5055
}

# Run shell function
run_shell() {
    print_status "Starting RASA shell..."
    print_status "You can now chat with your home automation assistant!"
    print_status "Try commands like:"
    echo "  - Turn on the bedroom fan"
    echo "  - Set AC temperature to 22 degrees"
    echo "  - Turn on kitchen lights"
    echo "  - Change living room lights to blue"
    echo ""
    print_status "Type 'exit' or press Ctrl+C to quit"
    rasa shell
}

# Run API server function
run_server() {
    print_status "Starting RASA API server..."
    print_status "Server will be available at http://localhost:5005"
    print_status "Press Ctrl+C to stop the server"
    rasa run --enable-api --cors "*" --port 5005
}

# Validate data function
validate_data() {
    print_status "Validating training data..."
    rasa data validate
    
    if [ $? -eq 0 ]; then
        print_success "✅ Data validation passed!"
    else
        print_error "❌ Data validation failed!"
        exit 1
    fi
}

# Main menu
show_menu() {
    echo ""
    echo "Available commands:"
    echo "1. train     - Train the RASA model"
    echo "2. test      - Test the NLU model"
    echo "3. validate  - Validate training data"
    echo "4. actions   - Start action server"
    echo "5. shell     - Start interactive shell"
    echo "6. server    - Start API server"
    echo "7. all       - Train model and start shell"
    echo "8. exit      - Exit script"
    echo ""
}

# Handle command line arguments
case "${1:-menu}" in
    "train")
        train_model
        ;;
    "test")
        test_nlu
        ;;
    "validate")
        validate_data
        ;;
    "actions")
        run_actions
        ;;
    "shell")
        run_shell
        ;;
    "server")
        run_server
        ;;
    "all")
        validate_data
        train_model
        print_status "Starting shell in 3 seconds..."
        sleep 3
        run_shell
        ;;
    "menu")
        show_menu
        read -p "Enter your choice (1-8): " choice
        case $choice in
            1) train_model ;;
            2) test_nlu ;;
            3) validate_data ;;
            4) run_actions ;;
            5) run_shell ;;
            6) run_server ;;
            7) 
                validate_data
                train_model
                print_status "Starting shell in 3 seconds..."
                sleep 3
                run_shell
                ;;
            8) exit 0 ;;
            *) print_error "Invalid choice. Please select 1-8." ;;
        esac
        ;;
    *)
        print_error "Invalid command: $1"
        echo "Usage: $0 [train|test|validate|actions|shell|server|all|menu]"
        exit 1
        ;;
esac
