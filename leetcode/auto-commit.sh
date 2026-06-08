#!/bin/bash
REPO_DIR="/Users/keusautomation/personal/Coding_Problems/"
CLAUDE="/Users/keusautomation/.local/bin/claude"
LOG="$HOME/.local/logs/leetcode-autocommit.log"

mkdir -p "$(dirname "$LOG")"
cd "$REPO_DIR" || exit 1

# Nothing to commit
if ! git status --porcelain | grep -q .; then
    exit 0
fi

git add .

FILES=$(git diff --staged --name-only | tr '\n' ' ')
DIFF_STAT=$(git diff --staged --stat | tail -1)

COMMIT_MSG=$("$CLAUDE" -p "Generate a concise git commit message (one line, under 72 chars) for changes to a LeetCode Java solutions repo. Changed files: $FILES. Summary: $DIFF_STAT. Return only the commit message text, no quotes, no explanation." 2>/dev/null)

if [ -z "$COMMIT_MSG" ]; then
    COMMIT_MSG="update solutions: $FILES"
fi

git commit -m "$COMMIT_MSG" >> "$LOG" 2>&1
git push origin main >> "$LOG" 2>&1
echo "$(date '+%Y-%m-%d %H:%M:%S') committed: $COMMIT_MSG" >> "$LOG"
