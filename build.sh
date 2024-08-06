#!/bin/bash

# Check if a number is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <number>"
  exit 1
fi

# Store the provided number in a variable
number=$1

# Get the directory of the script
script_dir=$(dirname "$0")

# Get the current working directory
current_dir=$(pwd)

# Define the base command
base_command="g++ -g3 --std=c++20"

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
