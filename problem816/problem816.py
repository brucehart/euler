import math

# Constants from the problem
modulus = 50515093
initial_s = 290797
num_points = 2000000

def generate_points(num_points, initial_s, modulus):
    s = [0] * (num_points * 2)
    s[0] = initial_s
    for i in range(1, num_points * 2):
        s[i] = (s[i - 1] * s[i - 1]) % modulus
    points = [(s[2 * i], s[2 * i + 1]) for i in range(num_points)]
    return points

def closest_pair(points):
    # Sort points by x and y coordinates
    points_sorted_by_x = sorted(points, key=lambda point: point[0])
    points_sorted_by_y = sorted(points, key=lambda point: point[1])
    
    def closest_pair_recursive(px, py):
        if len(px) <= 3:
            return brute_force_closest_pair(px)
        
        mid = len(px) // 2
        Qx = px[:mid]
        Rx = px[mid:]
        midpoint = px[mid][0]
        
        Qy = list(filter(lambda point: point[0] <= midpoint, py))
        Ry = list(filter(lambda point: point[0] > midpoint, py))
        
        (d1, pair1) = closest_pair_recursive(Qx, Qy)
        (d2, pair2) = closest_pair_recursive(Rx, Ry)
        
        if d1 <= d2:
            d = d1
            min_pair = pair1
        else:
            d = d2
            min_pair = pair2
        
        (d3, pair3) = closest_split_pair(px, py, d, min_pair)
        
        if d <= d3:
            return (d, min_pair)
        else:
            return (d3, pair3)
    
    def brute_force_closest_pair(points):
        min_dist = float('inf')
        min_pair = None
        n = len(points)
        for i in range(n - 1):
            for j in range(i + 1, n):
                p1, p2 = points[i], points[j]
                dist = math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)
                if dist < min_dist:
                    min_dist = dist
                    min_pair = (p1, p2)
        return (min_dist, min_pair)
    
    def closest_split_pair(px, py, delta, best_pair):
        len_x = len(px)
        mx = px[len_x // 2][0]
        s_y = [x for x in py if mx - delta <= x[0] <= mx + delta]
        
        best = delta
        len_y = len(s_y)
        for i in range(len_y - 1):
            for j in range(i + 1, min(i + 7, len_y)):
                p1, p2 = s_y[i], s_y[j]
                dist = math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)
                if dist < best:
                    best_pair = (p1, p2)
                    best = dist
        return (best, best_pair)
    
    return closest_pair_recursive(points_sorted_by_x, points_sorted_by_y)

points = generate_points(num_points, initial_s, modulus)
min_distance, _ = closest_pair(points)
min_distance_rounded = round(min_distance, 9)
print(min_distance_rounded)
