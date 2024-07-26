def is_bouncy(number):
    increasing = decreasing = False
    num_str = str(number)
    for i in range(len(num_str) - 1):
        if num_str[i] < num_str[i + 1]:
            increasing = True
        elif num_str[i] > num_str[i + 1]:
            decreasing = True
        if increasing and decreasing:
            return True
    return False

def find_bouncy_proportion(target_proportion):
    bouncy_count = 0
    number = 99  # Start from 100 as no number below 100 is bouncy
    while True:
        number += 1
        if is_bouncy(number):
            bouncy_count += 1
        if bouncy_count / number == target_proportion:
            return number

# Find the least number for which the proportion of bouncy numbers is exactly 99%
target_proportion = 0.99
result = find_bouncy_proportion(target_proportion)
print(result)
