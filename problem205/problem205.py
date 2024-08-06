import itertools
import numpy as np

# Define the number of sides and the number of dice
sides_peter = 4
sides_colin = 6
dice_peter = 9
dice_colin = 6

# Calculate all possible outcomes for Peter and Colin
outcomes_peter = np.array(list(itertools.product(range(1, sides_peter+1), repeat=dice_peter)))
outcomes_colin = np.array(list(itertools.product(range(1, sides_colin+1), repeat=dice_colin)))

# Calculate the sum of outcomes for Peter and Colin
sums_peter = np.sum(outcomes_peter, axis=1)
sums_colin = np.sum(outcomes_colin, axis=1)

# Calculate the number of times Peter's total is greater than Colin's total
peter_wins = 0

for sum_peter in sums_peter:
    peter_wins += np.sum(sum_peter > sums_colin)

# Calculate the total number of possible outcomes
total_outcomes = len(sums_peter) * len(sums_colin)

# Calculate the probability that Peter beats Colin
P_peter_beats_colin = peter_wins / total_outcomes
print(round(P_peter_beats_colin,7))
