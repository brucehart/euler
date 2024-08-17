#!/bin/bash

# Get the directory of the script
script_dir=$(dirname "$0")

# Get the current working directory
current_dir=$(pwd)

# Store the provided number in a variable
number=$(echo "$current_dir" | grep -o '[0-9]\+')

# Define the base command
base_command="g++ -g3 --std=c++2a"

# Check if the current directory is the same as the script directory
if [ "$script_dir" == "$current_dir" ]; then
  # Include the folder name
  command="$base_command -o problem${number}/problem${number} problem${number}/problem${number}.cpp"
else
  # Leave the folder name out
  command="$base_command -o problem${number} problem${number}.cpp"
fi

# Execute the command
eval $command
