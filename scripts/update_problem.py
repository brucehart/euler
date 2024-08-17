import sys
import os
import tempfile

def update_problem_status(filepath, problem_number, execution_time):
    temp_dir = os.path.dirname(filepath)
    temp_file_path = os.path.join(temp_dir, 'temp_problem_status.txt')

    problem_number = int(problem_number)
    problem_updated = False
    header = True
    
    with open(filepath, 'r') as file, open(temp_file_path, 'w') as temp_file:
        for line in file:
            if header:
                temp_file.write(line)
                if line.strip() == "------------------------------------------------":
                    header = False
            else:
                current_number = int(line.split('.')[0])
                if current_number == problem_number:
                    temp_file.write(f"{problem_number}. {execution_time}\n")
                    problem_updated = True
                elif current_number > problem_number and not problem_updated:
                    temp_file.write(f"{problem_number}. {execution_time}\n")
                    temp_file.write(line)
                    problem_updated = True
                else:
                    temp_file.write(line)
        
        if not problem_updated:
            temp_file.write(f"{problem_number}. {execution_time}\n")
    
    os.replace(temp_file_path, filepath)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python update_problem_status.py <path_to_problem_status.txt> <problem_number> <execution_time>")
        sys.exit(1)
    
    filepath = sys.argv[1]
    problem_number = sys.argv[2]
    execution_time = sys.argv[3]
    
    update_problem_status(filepath, problem_number, execution_time)
