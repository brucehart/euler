import re

def parse_time_to_seconds(time_str):
    """Convert a time string to seconds."""
    if "<1 ms" in time_str:
        return 0.0001
    if "ms" in time_str:
        return float(time_str.replace("ms", "").strip()) / 1000
    if "min" in time_str:
        match = re.match(r"(\d+)\s*min\s*([\d.]+)?\s*sec?", time_str)
        if match:
            minutes = int(match.group(1))
            seconds = float(match.group(2)) if match.group(2) else 0
            return minutes * 60 + seconds
    if "sec" in time_str:
        return float(time_str.replace("sec", "").strip())
    return 0

def load_status_data(file_path):
    """Read and parse the status file."""
    with open(file_path, "r") as file:
        data = {}
        data["completed_problems"] = 0
        for line in file:
            match = re.match(r"(\d+)\.\s+([\d<>\.\s\w]+)", line)
            if match:
                problem_num = int(match.group(1))
                time_str = match.group(2)
                time_in_seconds = parse_time_to_seconds(time_str)
                data[problem_num] = time_in_seconds
                data["completed_problems"] += 1
        return data

def generate_markdown_table(data, total_problems=925, items_per_row=10):
    """Generate a Markdown table with links for completed problems only."""
    markdown = "| " + " | ".join(["" for i in range(1, items_per_row + 1)]) + " |\n"
    markdown += "| " + " | ".join(["---"] * items_per_row) + " |\n"

    for row_start in range(1, total_problems + 1, items_per_row):
        row = []
        for i in range(row_start, row_start + items_per_row):
            if i > total_problems:
                row.append("")  # Fill empty cells beyond the problem count
            elif i in data:                
                time = data[i]
                url = f"https://github.com/brucehart/euler/tree/master/problem{i}"
                if time < 60:
                    row.append(f"[&#9989;<br>{i}]({url})")  # Green with link
                else:
                    row.append(f"[&#9888;<br>{i}]({url})")  # Yellow with link
            else:
                row.append(f"{i}")  # No link for unsolved problems
        markdown += "| " + " | ".join(row) + " |\n"
    return markdown

# File path to status.txt
file_path = "status.txt"

# Process the file and generate Markdown
data = load_status_data(file_path)
markdown_output = f"""Project Euler
=====

Completing the Project Euler (http://www.projecteuler.net) problems in 
Python and C++.

{data["completed_problems"]} problems completed so far
&#9989; - Completed in <1 minute execution time
&#9888; - Completed but needs to be optimized

"""

markdown_output += generate_markdown_table(data)

# Output Markdown to stdout
print(markdown_output)

