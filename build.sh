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

# Initialize flags
gmp_flags=""
primesieve_flag=""

# Check if the .cpp file contains the #include <gmpxx.h> directive
if grep -qE '#include <gmpxx.h>|#include <gmp.h>' "$source_file"; then
  #echo "Detected #include <gmpxx.h>. Adding -lgmp -lgmpxx to the compilation."
  gmp_flags="-lgmp -lgmpxx"
fi

# Check if the .cpp file contains the #include <primesieve.hpp> directive
if grep -q '#include <primesieve.hpp>' "$source_file"; then
  #echo "Detected #include <primesieve.hpp>. Adding -lprimesieve to the compilation."
  primesieve_flag="-lprimesieve"
fi

# Combine the flags
command="$base_command -O3 -o $output_file $source_file $gmp_flags $primesieve_flag"

# Execute the command
eval $command
