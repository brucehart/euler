#include <iostream>
#include <string>
#include <gmpxx.h>
#include <set>
#include <vector>
#include <numeric>
#include <algorithm>
#include <thread>
#include <mutex>

// Function to convert a big integer to a base-14 string
std::string to_base_14(const mpz_class& x) {
    if (x == 0)
        return "0";

    mpz_class n = x;
    std::string result;
    int base = 14;

    while (n > 0) {
        mpz_class digit = n % base;
        char ch;
        if (digit < 10)
            ch = '0' + digit.get_ui();
        else
            ch = 'a' + digit.get_ui() - 10;
        result = ch + result;
        n /= base;
    }

    return result;
}

// Function to compute the modular inverse of 'a' modulo 'm'
mpz_class mod_inverse(const mpz_class& a, const mpz_class& m) {
    mpz_class inv;
    if (mpz_invert(inv.get_mpz_t(), a.get_mpz_t(), m.get_mpz_t()) == 0)
        return 0; // No inverse exists
    else
        return inv;
}

// Worker function to process a single residue
void process_residue(int base, int max_digits, int residue, mpz_class& partial_sum) {
    mpz_class n_k = residue;
    mpz_class M = 1;

    std::set<mpz_class> visited;
    visited.insert(n_k);

    while (true) {
        M *= base; // M = 14^k
        mpz_class n_k_square = n_k * n_k;
        mpz_class diff = n_k_square - n_k;
        mpz_class c = diff / (M / base);

        mpz_class denom = 2 * n_k - 1;
        mpz_class denom_mod_base = denom % base;
        mpz_class inv = mod_inverse(denom_mod_base, base);

        if (inv == 0) {
            // No modular inverse exists; cannot proceed further
            break;
        }

        mpz_class c_mod_base = c % base;
        mpz_class m = (-c_mod_base * inv) % base;
        if (m < 0)
            m += base;

        n_k = n_k + m * (M / base);

        // Compute single_sum and num_digits
        mpz_class element = n_k;
        mpz_class single_sum = 0;
        int num_digits = 0;

        while (element > 0) {
            single_sum += element % base;
            element /= base;
            num_digits++;
        }

        if (num_digits > max_digits)
            break;

        if (visited.find(n_k) != visited.end())
            continue;

        visited.insert(n_k);
        partial_sum += single_sum;            
    }
}

// Function to generate automorphic numbers in base 14 using parallel processing
std::string calculate_sum_parallel(int base, int max_digits) {
    mpz_class total_sum = 1; // Initialize to 1 to match the original version
    std::vector<int> residues = {7, 8}; // Starting residues modulo 14

    // Vector to hold all threads
    std::vector<std::thread> threads;
    // Vector to hold partial sums from each thread
    std::vector<mpz_class> partial_sums(residues.size(), 0);

    // Launch a thread for each residue
    for (size_t i = 0; i < residues.size(); ++i) {
        threads.emplace_back(process_residue, base, max_digits, residues[i], std::ref(partial_sums[i]));
    }

    // Wait for all threads to finish
    for (auto& th : threads) {
        if (th.joinable())
            th.join();
    }

    // Aggregate the partial sums
    for (const auto& part_sum : partial_sums) {
        total_sum += part_sum;
    }

    return to_base_14(total_sum);
}

int main() {
    int base = 14;
    int max_digits = 10000; // Adjust this to generate more digits

    std::string result = calculate_sum_parallel(base, max_digits);
    std::cout << result << std::endl;

    return 0;
}
