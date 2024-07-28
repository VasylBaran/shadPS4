#!/bin/bash -ex

# SPDX-FileCopyrightText: 2023 Citra Emulator Project
# SPDX-License-Identifier: GPL-2.0-or-later

fix=false
if [ "$1" == "--fix" ]; then
    fix=true
fi

if grep -nrI '\s$' src *.yml *.txt *.md Doxyfile .gitignore .gitmodules .ci* dist/*.desktop \
                 dist/*.svg dist/*.xml; then
    echo Trailing whitespace found, aborting
    exit 1
fi

# Default clang-format points to default 3.5 version one
CLANG_FORMAT=clang-format-17
$CLANG_FORMAT --version

if [ "$GITHUB_EVENT_NAME" = "pull_request" ]; then
    # Get list of every file modified in this pull request
    files_to_lint="$(git diff --name-only --diff-filter=ACMRTUXB $COMMIT_RANGE | grep '^src/[^.]*[.]\(cpp\|h\)$' || true)"
else
    # Check everything for branch pushes
    files_to_lint="$(find src/ -name '*.cpp' -or -name '*.h')"
fi

# Turn off tracing for this because it's too verbose
set +x

for f in $files_to_lint; do
    if [ "$fix" = true ]; then
        $CLANG_FORMAT -i "$f"
    else
        d=$(diff -u "$f" <($CLANG_FORMAT "$f") || true)
        if ! [ -z "$d" ]; then
            echo "!!! $f not compliant to coding style, here is the fix:"
            echo "$d"
            fail=1
        fi
    fi
done

set -x

if [ "$fail" = 1 ]; then
    exit 1
fi
