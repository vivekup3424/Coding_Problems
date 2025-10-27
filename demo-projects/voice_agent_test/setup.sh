pyenv_path="$HOME/.pyenv"
if [ -d "$pyenv_path" ]; then
    echo "pyenv is already installed at $pyenv_path"
    exit 0
fi

# setting up shell environment for pyenv
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(pyenv init - bash)"' >> ~/.bashrc

curl -fsSL https://pyenv.run | bash