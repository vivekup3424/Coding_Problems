#!/bin/bash
pyenv_path="$HOME/.pyenv"
if [ -d "$pyenv_path" ]; then
    rm -rf $pyenv_path # remove this code in final version
    # echo "pyenv is already installed at $pyenv_path"
    # exit 0
fi

SHELL_NAME=$(basename "$SHELL")
echo "Detected shell: $SHELL_NAME"
if [ "$SHELL_NAME" == "zsh" ]; then
    SHELL_CONFIG="$HOME/.zshrc"
elif [ "$SHELL_NAME" == "bash" ]; then
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

