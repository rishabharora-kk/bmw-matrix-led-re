#!/usr/bin/env bash
# Publish this original local repository when the OWNER explicitly runs it on
# a machine with the official GitHub CLI installed and authorized.
set -euo pipefail
cd "$(dirname "$0")/.."
REPO="rishabharora-kk/bmw-matrix-led-re"
command -v git >/dev/null || { echo 'git is required' >&2; exit 1; }
command -v gh >/dev/null || { echo 'Install GitHub CLI (gh) first' >&2; exit 1; }
gh auth status >/dev/null || { echo 'Run: gh auth login' >&2; exit 1; }
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  git init -b main
fi
if ! git rev-parse HEAD >/dev/null 2>&1; then
  echo 'No local commit; set your Git author first: git config user.name / user.email'
  git add .
  git commit -m 'Research: bench-only BMW HELLA G30 LCI matrix LED feasibility scaffold'
fi
if gh repo view "$REPO" >/dev/null 2>&1; then
  echo "$REPO already exists; will not overwrite or force-push it."
  git remote get-url origin >/dev/null 2>&1 || git remote add origin "https://github.com/$REPO.git"
  git push -u origin HEAD:main
else
  gh repo create "$REPO" --public --description 'Bench-only BMW G30 LCI HELLA matrix headlight interoperability research' --source=. --remote=origin --push
fi
python3 scripts/seed_issues.py "$REPO"
echo "Published: https://github.com/$REPO"
