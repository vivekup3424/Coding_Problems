#!/bin/bash
pyenv_path="$HOME/.pyenv"
if [ -d "$pyenv_path" ]; then
    rm -rf $pyenv_path # remove this code in final version
    # echo "pyenv is already installed at $pyenv_path"
    # exit 0
fi

SHELL_NAME=$(basename "$SHELL")
echo "Detected shell: $SHELL_NAME"
if [ "$SHELL_NAME" = "zsh" ]; then
    SHELL_CONFIG="$HOME/.zshrc"
elif [ "$SHELL_NAME" = "bash" ]; then
    SHELL_CONFIG="$HOME/.bashrc"
else
    echo "Unsupported shell: $SHELL_NAME"
    exit 1
fi
# setting up shell environment for pyenv
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> $SHELL_CONFIG
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> $SHELL_CONFIG
echo "eval \"\$(pyenv init - $SHELL_NAME)\"" >> $SHELL_CONFIG

curl -fsSL https://pyenv.run | bash

# Load pyenv into current session manually since sourcing config might not work immediately
export PYENV_ROOT="$HOME/.pyenv"
[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"
eval "$(pyenv init - $SHELL_NAME)"

# Install python build dependencies
echo "Installing Python build dependencies..."
sudo apt update
sudo apt install -y make build-essential libssl-dev zlib1g-dev \
libbz2-dev libreadline-dev libsqlite3-dev curl git \
libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev

# Install Python versions
echo "Installing Python 3.9..."
pyenv install 3.9.10

echo "Installing Python 3.11..."
pyenv install 3.11.2

# Get the current directory
CURRENT_DIR=$(pwd)

# Setup Python 3.9 for rasa_home_assistant
echo "Setting up Python 3.9 for rasa_home_assistant directory..."
cd "$CURRENT_DIR/rasa_home_assistant"
pyenv local 3.9.10
echo "Python 3.9.10 set for rasa_home_assistant directory"
python --version

# Setup Python 3.11 for voice_agent
echo "Setting up Python 3.11 for voice_agent directory..."
cd "$CURRENT_DIR/voice_agent"
pyenv local 3.11.2
echo "Python 3.11.2 set for voice_agent directory"
python --version

# Return to original directory
cd "$CURRENT_DIR"

echo "Python 3.9.10 is configured for: $CURRENT_DIR/rasa_home_assistant"
echo "Python 3.11.2 is configured for: $CURRENT_DIR/voice_agent"

echo "Starting RASA Home Assistant setup..."
cd "$CURRENT_DIR/rasa_home_assistant"
pip install -r requirements.txt
python -m spacy download en_core_web_sm
echo "RASA Home Assistant setup completed."

echo "Starting Voice Agent setup..."
cd "$CURRENT_DIR/voice_agent"
pip install -r requirements.txt
python agent.py download_files

echo "Voice Agent setup completed."