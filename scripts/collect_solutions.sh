#!/bin/bash

# Create or empty the solutions.txt file
> solutions.txt

# Loop through all subfolders named problem{number}
for folder in problem*; do
    if [ -d "$folder" ]; then
        # Extract the number from the folder name
        number=$(echo "$folder" | grep -o '[0-9]\+')
        
        # Find the solution file
        solution_file="$folder/solution$number.txt"
        
        if [ -f "$solution_file" ]; then
            # Get the content of the solution file
            solution_content=$(cat "$solution_file")
            
            # Append the number and content to solutions.txt in the desired format
            echo "$number. $solution_content" >> solutions.txt
        else
            # Print out the folder name if solution{number}.txt is missing
            echo "No solution file found in folder: $folder"
        fi
    fi
done

# Sort the solutions.txt by numeric value of the number
sort -n -k1,1 solutions.txt -o solutions.txt

