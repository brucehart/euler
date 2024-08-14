import math

def euler63():
    count = 0
    n = 1
    
    while True:
        c = math.ceil(math.exp(math.log(10) * (n - 1) / n))
        if c >= 10:
            break
        else:
            count += int(10 - c)
            
        n += 1
        
    print(count)

if __name__ == '__main__':
    euler63()

