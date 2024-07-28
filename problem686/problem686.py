import math

# Step 1: Compute alpha and beta
alpha = math.log10(1.23)
beta = math.log10(1.24)

# Step 2: Get only the decimal portions
alpha = alpha - int(alpha)
beta = beta - int(beta)

# Step 3: Precompute log10(2)
log2 = math.log10(2)

# Initialize counter and j
counter = 0
j = 2

# Step 4-7: Loop through variable j
while True:
    # Get the decimal portion of j * log2
    decimal_portion = (j * log2) % 1
    
    # Check if the decimal portion is within the range
    if alpha <= decimal_portion < beta:
        counter += 1
    
    # Check if the counter reaches 678910
    if counter == 678910:
        #result = 2 ** j
        print(f"{j}")
        break
    
    # Increment j
    j += 1
