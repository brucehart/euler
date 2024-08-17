#!/bin/bash

# Loop through all subfolders named problem*
for dir in problem*/; do
    # Extract the number from the folder name
    number=$(echo "$dir" | grep -oP '\d+')

    # Construct the expected solution file name
    solution_file="solution$number.txt"

    # Check if the solution file exists in the folder
    if [ ! -f "$dir$solution_file" ]; then
        # Print the folder name if the solution file does not exist
        echo "Missing solution file in: $dir"
    fi
done
