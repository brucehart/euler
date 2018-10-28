#include <vector>
#include <algorithm>
#include <cstdlib>
#include <set>

class Primes
{
	public:
		template <class T>
		static void generatePrimes(std::set<T>& result, T maxPrime);
};

template <class T>
void Primes::generatePrimes(std::set<T>& result, T maxPrime)
{
	std::set<T> exclude;
	
	result.insert(2);

	T i = 1;
	T j = 1;

	while ((i+j+2*i*j) <= maxPrime)
	{
		exclude.insert(i+j+2*i*j);

		while (i <= j)
		{
			if ((i+j+2*i*j) <= maxPrime)
				exclude.insert(i+j+2*i*j);
			i++;
		}

		j++;
		i=1;
	}

	for (i=1;(2*i+1)<=maxPrime;i++)
		if (!std::binary_search(exclude.begin(), exclude.end(), i))
			result.insert(2*i+1);

}