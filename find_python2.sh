#!/bin/bash

# Path to search from, default is current directory
SEARCH_PATH="${1:-.}"

# Function to check files for Python 2 specific syntax
check_python2_syntax() {
    local file=$1
    # Search for common Python 2 patterns
    if grep -q "print " "$file" ||
       grep -q "except .*," "$file" ||
       grep -q "exec " "$file"; then
        echo "$file"
    fi
}

export -f check_python2_syntax

# Find all .py files and check each for Python 2 specific syntax
find "$SEARCH_PATH" -name '*.py' -type f -exec bash -c 'check_python2_syntax "$0"' {} \;

