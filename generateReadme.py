#!/usr/bin/env python3

import re
import os
import sys
from PIL import Image, ImageDraw, ImageFont

def parse_time_to_seconds(time_str):
    """
    Convert a time string to seconds.
    """
    if "<1 ms" in time_str:
        return 0.0001
    if "ms" in time_str:
        # e.g. "100 ms" -> 0.1 sec
        return float(time_str.replace("ms", "").strip()) / 1000
    if "min" in time_str:
        # e.g. "2 min 30 sec"
        match = re.match(r"(\d+)\s*min\s*([\d.]+)?\s*sec?", time_str)
        if match:
            minutes = int(match.group(1))
            seconds = float(match.group(2)) if match.group(2) else 0
            return minutes * 60 + seconds
    if "sec" in time_str:
        # e.g. "5 sec" -> 5.0
        return float(time_str.replace("sec", "").strip())
    return 0

def load_status_data(file_path):
    """
    Read and parse the status file (e.g., 'status.txt'), which contains lines like:
    1. 12.345 sec
    2. 2 min 12 sec
    3. <1 ms
    ...
    """
    data = {"completed_problems": 0}

    with open(file_path, "r") as file:
        for line in file:
            # Regex for lines like "1. 12.345 sec"
            match = re.match(r"(\d+)\.\s+([\d<>\.\s\w]+)", line)
            if match:
                problem_num = int(match.group(1))
                time_str = match.group(2).strip()
                time_in_seconds = parse_time_to_seconds(time_str)
                data[problem_num] = time_in_seconds
                data["completed_problems"] += 1

    return data

def generate_cell_image(problem_num, time_in_seconds=None, cell_size=40, padding=4):
    """
    Generate a single Pillow Image (e.g., 40x40) for the problem cell.
    - Green if time_in_seconds < 120
    - Yellow if time_in_seconds >= 120
    - White if time_in_seconds is None (problem not completed)
    - The problem number is drawn in black text, centered, 10pt bold font.
    
    Parameters:
    - cell_size: Size of the cell in pixels (both width and height).
    - padding: Padding around the text within the cell.
    """
    # Determine background color
    if time_in_seconds is not None:
        color = "green" if time_in_seconds < 120 else "yellow"
    else:
        color = "white"

    # Create the image
    img = Image.new("RGB", (cell_size, cell_size), color)
    draw = ImageDraw.Draw(img)

    # Attempt a 10-pt bold font; fallback to default if not found
    try:
        font = ImageFont.truetype("DejaVuSans-Bold.ttf", 10)
    except OSError:
        font = ImageFont.load_default()

    text = str(problem_num)
    
    # Use textbbox instead of textsize
    text_bbox = draw.textbbox((0, 0), text, font=font)
    text_w = text_bbox[2] - text_bbox[0]
    text_h = text_bbox[3] - text_bbox[1]

    # Calculate position to center the text
    x = (cell_size - text_w) / 2
    y = (cell_size - text_h) / 2
    draw.text((x, y), text, fill="black", font=font)

    return img

def generate_individual_cell_images(data, folder="status", total_problems=925, cell_size=40, padding=4):
    """
    Generate separate PNG files for each problem cell:
      status/problem1.png
      status/problem2.png
      ...
    in the given folder. The folder will be created if it doesn't exist.
    
    Parameters:
    - cell_size: Size of each cell image in pixels.
    - padding: Padding around the text within each cell.
    """
    if not os.path.exists(folder):
        os.makedirs(folder)

    for i in range(1, total_problems + 1):
        time_in_seconds = data.get(i, None)
        img = generate_cell_image(i, time_in_seconds, cell_size=cell_size, padding=padding)
        filename = os.path.join(folder, f"problem{i}.png")
        img.save(filename)

def generate_markdown_table_with_images(data, folder="status", total_problems=925, items_per_row=10):
    """
    Build a Markdown table that uses each problem's PNG as a clickable link with tooltips:
      [![1](status/problem1.png "Completed in 1.5 minutes")](https://github.com/.../problem1)
    
    Each row in the table has 'items_per_row' cells.
    """
    # Initialize the Markdown table with headers
    markdown = "| " + " | ".join(["" for _ in range(items_per_row)]) + " |\n"
    markdown += "| " + " | ".join(["---"] * items_per_row) + " |\n"

    for row_start in range(1, total_problems + 1, items_per_row):
        row = []
        for i in range(row_start, row_start + items_per_row):
            if i > total_problems:
                row.append("")
            else:
                url = f"https://github.com/brucehart/euler/tree/master/problem{i}"
                image_path = f"{folder}/problem{i}.png"
                
                if i in data:
                    time_sec = data[i]
                    # Format the time for the tooltip
                    if time_sec < 1:
                        time_str = "<1 ms"
                    elif time_sec < 60:
                        time_str = f"{time_sec:.2f} sec"
                    else:
                        minutes = int(time_sec // 60)
                        seconds = time_sec % 60
                        time_str = f"{minutes} min {seconds:.2f} sec" if seconds else f"{minutes} min"
                    
                    tooltip = f"Completed in {time_str}"
                    # Wrap the image in a link with tooltip
                    markdown_cell = f"[![{i}]({image_path} \"{tooltip}\")]({url})"
                else:
                    # Tooltip for not completed
                    tooltip = "Not completed"
                    markdown_cell = f"![{i}]({image_path} \"{tooltip}\")"
                
                row.append(markdown_cell)
        markdown += "| " + " | ".join(row) + " |\n"
    return markdown

if __name__ == "__main__":
    # Default settings
    status_file_path = "status.txt"
    output_folder = "status"
    total_problems = 925
    items_per_row = 10
    cell_size = 40  # Reduced from 50 to 40 for closer spacing
    padding = 4     # Reduced padding

    # Optionally pass a custom status file as first argument
    if len(sys.argv) > 1:
        status_file_path = sys.argv[1]
    # Optionally pass a custom output folder as second argument
    if len(sys.argv) > 2:
        output_folder = sys.argv[2]

    # Load data from status file
    data = load_status_data(status_file_path)

    # Generate the individual cell images
    generate_individual_cell_images(data, folder=output_folder, total_problems=total_problems, cell_size=cell_size, padding=padding)

    # Create the Markdown table referencing each cell image with tooltips
    clickable_table = generate_markdown_table_with_images(
        data,
        folder=output_folder,
        total_problems=total_problems,
        items_per_row=items_per_row
    )

    # Build the final Markdown README content
    markdown_output = f"""# Project Euler

Completing the Project Euler (http://www.projecteuler.net) problems in Python and C++.

**{data["completed_problems"]}** problems completed so far.

Below is a table of small PNG images.  
- **Green** = Completed in <2 minutes  
- **Yellow** = Completed in ≥2 minutes  
- **White** = Not completed

Each completed problem cell links to its source code folder in GitHub and displays a tooltip with the completion time.

{clickable_table}
"""

    # Output to stdout (so you can redirect to README.md if desired)
    print(markdown_output)
