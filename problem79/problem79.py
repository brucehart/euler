from collections import defaultdict, deque

# Read the logins from the file
with open('0079_keylog.txt') as file:
    logins = file.read().splitlines()

# Build the graph
graph = defaultdict(set)
in_degree = defaultdict(int)

for login in logins:
    for i in range(len(login)):
        if login[i] not in in_degree:
            in_degree[login[i]] = 0
        for j in range(i + 1, len(login)):
            if login[j] not in graph[login[i]]:
                graph[login[i]].add(login[j])
                in_degree[login[j]] += 1

# Topological Sort using Kahn's algorithm
queue = deque([node for node in in_degree if in_degree[node] == 0])
sorted_chars = []

while queue:
    current = queue.popleft()
    sorted_chars.append(current)
    for neighbor in graph[current]:
        in_degree[neighbor] -= 1
        if in_degree[neighbor] == 0:
            queue.append(neighbor)

# Join the sorted characters to form the passcode
passcode = ''.join(sorted_chars)
print(passcode)
