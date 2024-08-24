#!/bin/bash

# Get the directory of the script
script_dir=$(dirname "$0")

# Get the current working directory
current_dir=$(pwd)

# Store the provided number in a variable
number=$(echo "$current_dir" | grep -o '[0-9]\+')

# Define the base command
base_command="g++ -g3 --std=c++2a"

# Determine the source file path
if [ "$script_dir" == "$current_dir" ]; then
  source_file="problem${number}/problem${number}.cpp"
  output_file="problem${number}/problem${number}"
else
  source_file="problem${number}.cpp"
  output_file="problem${number}"
fi

# Check if the .cpp file contains the #include <gmpxx.h> directive
if grep -qE '#include <gmpxx.h>|#include <gmp.h>' "$source_file"; then
  #echo "Detected #include <gmpxx.h>. Adding -lgmp -lgmpxx to the compilation."
  command="$base_command -o $output_file $source_file -lgmp -lgmpxx"
else
  #echo "No #include <gmpxx.h> detected. Compiling without -lgmp -lgmpxx."
  command="$base_command -o $output_file $source_file"
fi

# Execute the command
eval $command

