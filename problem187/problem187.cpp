//Author: Bruce Hart <bruce.hart@gmail.com>

// Semiprimes
// Problem 187 
// A composite is a number containing at least two prime factors. For example, 15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.

// There are ten composites below thirty containing precisely two, not necessarily distinct, prime factors: 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

// How many composite integers, n < 10^8, have precisely two, not necessarily distinct, prime factors?

#include "../helpers/primes.hpp"
#include <cstdlib>
#include <set>
#include <iostream>

int main(int argc, char** argv)
{
	std::set<uint32_t> primes;
	Primes::generatePrimes(primes, (uint32_t)10000);

	std::cout << primes.size() << std::endl;
}