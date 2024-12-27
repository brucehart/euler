import re

def parse_time_to_seconds(time_str):
    """Convert a time string to seconds."""
    if "<1 ms" in time_str:
        return 0.0001
    if "ms" in time_str:
        return float(time_str.replace("ms", "").strip()) / 1000
    if "min" in time_str:
        # Match patterns like "2 min 1.359 sec"
        match = re.match(r"(\d+)\s*min\s*([\d.]+)?\s*sec?", time_str)
        if match:
            minutes = int(match.group(1))
            seconds = float(match.group(2)) if match.group(2) else 0
            return minutes * 60 + seconds
    if "sec" in time_str:
        return float(time_str.replace("sec", "").strip())
    return 0  # Default for unexpected formats

def load_status_data(file_path):
    """Read and parse the status file."""
    with open(file_path, "r") as file:
        data = {}
        for line in file:
            match = re.match(r"(\d+)\.\s+([\d<>\.\s\w]+)", line)
            if match:
                problem_num = int(match.group(1))
                time_str = match.group(2)
                time_in_seconds = parse_time_to_seconds(time_str)
                data[problem_num] = time_in_seconds
        return data

def generate_markdown_table(data, total_problems=923, items_per_row=20):
    """Generate a Markdown table based on problem completion times."""
    markdown = "| " + " | ".join([str(i) for i in range(1, items_per_row + 1)]) + " |\n"
    markdown += "| " + " | ".join(["---"] * items_per_row) + " |\n"

    for row_start in range(1, total_problems + 1, items_per_row):
        row = []
        for i in range(row_start, row_start + items_per_row):
            if i in data:
                time = data[i]
                if time < 60:
                    row.append(f'<span style="background-color: green;">{i}</span>')
                else:
                    row.append(f'<span style="background-color: yellow;">{i}</span>')
            else:
                row.append(str(i))
        markdown += "| " + " | ".join(row) + " |\n"
    return markdown

# File path to status.txt
file_path = "status.txt"

# Process the file and generate Markdown
data = load_status_data(file_path)
markdown_output = generate_markdown_table(data)

# Output Markdown to stdout
print(markdown_output)

