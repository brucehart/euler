#include <iostream>
#include <gmp.h>
#include <gmpxx.h>

// Function to calculate binomial coefficient C(n, k)
mpz_class binomial_coefficient(int n, int k) {
    mpz_class result;
    mpz_bin_uiui(result.get_mpz_t(), n, k);
    return result;
}

// Function to calculate N_k based on the given formula
mpz_class calculate_N_k(int n, int k, int d) {
    // Calculate binomial coefficient (n choose k)
    mpz_class binom = binomial_coefficient(n, k);

    // Calculate (d + 1)^k
    mpz_class d_plus_one_pow_k;
    mpz_ui_pow_ui(d_plus_one_pow_k.get_mpz_t(), d + 1, k);

    // Calculate (9 - d)^(n - k)
    mpz_class nine_minus_d_pow_n_minus_k;
    mpz_ui_pow_ui(nine_minus_d_pow_n_minus_k.get_mpz_t(), 9 - d, n - k);

    // Calculate N_k
    mpz_class N_k = binom * d_plus_one_pow_k * nine_minus_d_pow_n_minus_k;

    return N_k;
}

int main() {
    int n = 3; // Example value for n
    int k = 2;  // Example value for k
    int d = 5;  // Example value for d

    mpz_class N_k = calculate_N_k(n, k, d);
    mpz_class N_k1 = calculate_N_k(n, k, d-1);

    std::cout << "N_k = " << N_k << std::endl;
    std::cout << "N_k1 = " << N_k1 << std::endl;

    int count = 0;

    for(int i=100; i<1000; i++){
        std::string num_str = std::to_string(i);
        int count_5 = std::count(num_str.begin(), num_str.end(), '5');
        if(count_5 == 2)
            count++;
        
    }

    std::cout << "Count: " << count << std::endl;

    int x = 2;

    mpz_class term1 = binomial_coefficient(n, x);
    mpz_class term2 = binomial_coefficient(n - 1, x - 1);

    mpz_class nine_pow_n_minus_x;
    mpz_ui_pow_ui(nine_pow_n_minus_x.get_mpz_t(), 9, n - x);

    mpz_class result = term1 * nine_pow_n_minus_x - term2 * nine_pow_n_minus_x;

    std::cout << "C(n,x) * 9^(n-x) - C(n-1,x-1) * 9^(n-x) = " << result << std::endl;

    return 0;
}
