import sys
import os
import tempfile

def update_problem_status(filepath, problem_number, execution_time):
    temp_dir = os.path.dirname(filepath)
    temp_file_path = os.path.join(temp_dir, 'temp_problem_status.txt')

    print(f"Starting update_problem_status with filepath={filepath}, problem_number={problem_number}, execution_time={execution_time}")

    try:
        problem_number = int(problem_number)
        print(f"Parsed problem_number as integer: {problem_number}")
    except ValueError:
        problem_number = str(problem_number)
        print(f"Parsed problem_number as string: {problem_number}")

    problem_updated = False
    header = True

    numeric_entries = []
    non_numeric_entries = []

    with open(filepath, 'r') as file:
        print("Reading file to categorize problems")
        for line in file:
            if header:
                if line.strip() == "------------------------------------------------":
                    header = False
                continue

            # Parse existing problem number
            try:
                current_number = int(line.split('.')[0])
                numeric_entries.append((current_number, line))
                print(f"Added numeric entry: {current_number}")
            except ValueError:
                current_number = line.split('.')[0]
                non_numeric_entries.append((current_number, line))
                print(f"Added non-numeric entry: {current_number}")

    # Add or update the problem
    if isinstance(problem_number, int):
        print("Updating numeric entries")
        for i, (current_number, line) in enumerate(numeric_entries):
            if current_number == problem_number:
                numeric_entries[i] = (problem_number, f"{problem_number}. {execution_time}\n")
                problem_updated = True
                print(f"Updated existing numeric problem: {problem_number}")
                break
            elif current_number > problem_number and not problem_updated:
                numeric_entries.insert(i, (problem_number, f"{problem_number}. {execution_time}\n"))
                problem_updated = True
                print(f"Inserted numeric problem at position {i}: {problem_number}")
                break
        if not problem_updated:
            numeric_entries.append((problem_number, f"{problem_number}. {execution_time}\n"))
            print(f"Appended numeric problem: {problem_number}")
    else:
        print("Updating non-numeric entries")
        for i, (current_number, line) in enumerate(non_numeric_entries):
            if current_number == problem_number:
                non_numeric_entries[i] = (problem_number, f"{problem_number}. {execution_time}\n")
                problem_updated = True
                print(f"Updated existing non-numeric problem: {problem_number}")
                break
        if not problem_updated:
            non_numeric_entries.append((problem_number, f"{problem_number}. {execution_time}\n"))
            print(f"Appended non-numeric problem: {problem_number}")

    # Sort numeric entries numerically and non-numeric entries alphabetically
    numeric_entries.sort(key=lambda x: x[0])
    non_numeric_entries.sort(key=lambda x: x[0])
    print("Sorted numeric and non-numeric entries")

    with open(filepath, 'r') as file, open(temp_file_path, 'w') as temp_file:
        print("Writing updated entries to temp file")
        for line in file:
            temp_file.write(line)
            if line.strip() == "------------------------------------------------":
                break

        for _, line in numeric_entries:
            temp_file.write(line)

        for _, line in non_numeric_entries:
            temp_file.write(line)

    os.replace(temp_file_path, filepath)
    print(f"Replaced original file with updated file: {filepath}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python update_problem_status.py <path_to_problem_status.txt> <problem_number> <execution_time>")
        sys.exit(1)

    filepath = sys.argv[1]
    problem_number = sys.argv[2]
    execution_time = sys.argv[3]

    print("Starting script execution")
    update_problem_status(filepath, problem_number, execution_time)
    print("Script execution completed")
