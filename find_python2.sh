#!/bin/bash

# Path to search from, default is current directory
SEARCH_PATH="${1:-.}"

# Function to check if a file does not contain Python 3 style print() function
check_for_python2() {
    local file=$1
    # Check if file does not contain the Python 3 print function
    if ! grep -q 'print(.*' "$file"; then
        echo "$file"
    fi
}

export -f check_for_python2

# Find all .py files and check each for absence of Python 3 print() function
find "$SEARCH_PATH" -name '*.py' -type f -exec bash -c 'check_for_python2 "$0"' {} \;
