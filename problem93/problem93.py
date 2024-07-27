import itertools

# Define the basic arithmetic operations manually
def add(a, b): return a + b
def sub(a, b): return a - b
def mul(a, b): return a * b
def div(a, b): return a / b if b != 0 else None

# All possible arithmetic operations
operations = [add, sub, mul, div]

def all_possible_expressions(digits):
    """ Generate all possible expressions using the given digits and operations """
    expressions = set()
    for perm in itertools.permutations(digits):
        for ops in itertools.product(operations, repeat=3):
            # Different ways to parenthesize the expression
            try:
                expr1 = ops[0](perm[0], ops[1](perm[1], ops[2](perm[2], perm[3])))  # a op1 (b op2 (c op3 d))
                if expr1 > 0 and expr1 == int(expr1):
                    expressions.add(int(expr1))
            except:
                pass
            try:
                expr2 = ops[0](ops[1](perm[0], perm[1]), ops[2](perm[2], perm[3]))  # (a op1 b) op2 (c op3 d)
                if expr2 > 0 and expr2 == int(expr2):
                    expressions.add(int(expr2))
            except:
                pass
            try:
                expr3 = ops[0](ops[1](ops[2](perm[0], perm[1]), perm[2]), perm[3])  # ((a op1 b) op2 c) op3 d
                if expr3 > 0 and expr3 == int(expr3):
                    expressions.add(int(expr3))
            except:
                pass
            try:
                expr4 = ops[0](perm[0], ops[1](ops[2](perm[1], perm[2]), perm[3]))  # a op1 ((b op2 c) op3 d)
                if expr4 > 0 and expr4 == int(expr4):
                    expressions.add(int(expr4))
            except:
                pass
            try:
                expr5 = ops[0](ops[1](perm[0], ops[2](perm[1], perm[2])), perm[3])  # (a op1 (b op2 c)) op3 d
                if expr5 > 0 and expr5 == int(expr5):
                    expressions.add(int(expr5))
            except:
                pass
    return expressions

# Find the set of four distinct digits that gives the longest set of consecutive positive integers
max_consecutive_length = 0
best_digits = ()

for a in range(1, 10):
    for b in range(a+1, 10):
        for c in range(b+1, 10):
            for d in range(c+1, 10):
                digits = [a, b, c, d]
                expressions = all_possible_expressions(digits)
                n = 1
                while n in expressions:
                    n += 1
                if n - 1 > max_consecutive_length:
                    max_consecutive_length = n - 1
                    best_digits = (a, b, c, d)

print(''.join(str(digit) for digit in best_digits))

