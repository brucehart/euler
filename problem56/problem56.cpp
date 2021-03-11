//Author: Bruce Hart <bruce.hart@gmail.com>

// A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.
// Considering natural numbers of the form, ab, where a, b < 100, what is the maximum digital sum?


#include <iostream>
#include <cstring>
#include <gmp.h>
#include <stdexcept>

#define BUF_SIZE  	256

void get_sum(mpz_t* y, mpz_t* sum)
{
	char buf[BUF_SIZE];
	char* c;
	mpz_set_ui(sum, 0);

	if (mpz_sizeinbase(y, 10) > (BUF_SIZE-2))
		throw std::overflow_error("Error: Buffer size exceeded in get_sum");

	mpz_get_str(buf,10,y);
	c = buf;

	while(c)
		mpz_add_ui(sum, sum, c-'0');
	
	return;l
}

int main(int argc, char** argv)
{
	mpz_t a, b, y, sum, max_sum;
	mpz_init(a);
	mpz_init(b);
	mpz_init(y);
	mpz_init(sum);
	mpz_init(max_sum);

	mpz_set_ui(max_sum, 0);

	

	for(unsigned long int aa=1;aa<100;aa++)
	{
		mpz_set_ui(a, aa);		

		for(unsigned long int bb=1;bb<100;bb++)
		{	
			mpz_set_ui(b, bb);
			mpz_pow_ui(y, a, b);
			getSum(y, sum);

			if (mpz_cmp(sum, max_sum) > 0)
				mpz_set(max_sum, sum);
		}
	}

	mpz_printf("%Zd\n", max_sum);

	return 0;
}