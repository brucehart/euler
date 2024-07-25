# Constants
INITIAL_EULERCOIN = 1504170715041707
MODULO = 4503599627370517
SWITCH_THRESHOLD = 15806432

def compute():
    eulercoins = [INITIAL_EULERCOIN]
    current_eulercoin = INITIAL_EULERCOIN
    inv = pow(INITIAL_EULERCOIN, -1, MODULO)
    n = 2
    
    # Downward search for Eulercoins
    while True:
        number = INITIAL_EULERCOIN * n % MODULO
        if number < current_eulercoin:
            current_eulercoin = number
            eulercoins.append(number)
            #print(f"Downward: n = {n}, number = {number}")
        
        # Switch to upward search strategy
        if current_eulercoin == SWITCH_THRESHOLD:
            new_curr_eulercoin = 1
            curr_max = MODULO
            
            # Upward search for Eulercoins
            while new_curr_eulercoin != SWITCH_THRESHOLD: 
                number = (inv * new_curr_eulercoin) % MODULO
                if number < curr_max:
                    curr_max = number
                    eulercoins.append(new_curr_eulercoin)
                    #print(f"Upward: number = {number}, new_curr_eulercoin = {new_curr_eulercoin}")
                new_curr_eulercoin += 1
            break
        n += 1
        
    return sum(eulercoins)

# Call the function to get the result
result = compute()
#print("Sum of all eulercoins: ", result)
print(result)

