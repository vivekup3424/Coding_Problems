#!/bin/bash

# Navigate to the repository directory
cd /home/vivekup3424/personal/Coding_Problems

# Add all changes
git add .

# Check if there are any changes to commit
if git diff-index --quiet HEAD --; then
    echo "No changes to commit"
else
    # Commit with timestamp
    git commit -m "Auto-commit: $(date '+%Y-%m-%d %H:%M:%S')"
    
    # Push to remote
    git push origin main
    
    echo "Changes committed and pushed at $(date '+%Y-%m-%d %H:%M:%S')"
fi
