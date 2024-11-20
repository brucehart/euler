#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <set>
#include <vector>

using boost::multiprecision::cpp_int;

std::string to_base_14(cpp_int x)
{
    std::string n_base14 = "";
    int base = 14;

    while (x > 0){
        int digit = (int)(x % base).convert_to<int>();
        char ch;
        if (digit < 10)
            ch = '0' + digit;
        else
            ch = 'a' + digit - 10;
        n_base14 = ch + n_base14;
        x /= base;
    }
    if (n_base14 == "")
        n_base14 = "0";

    return n_base14;
}

// Function to compute the modular inverse of 'a' modulo 'm'
cpp_int mod_inverse(cpp_int a, cpp_int m)
{
    cpp_int m0 = m, t, q;
    cpp_int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algorithm
        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to generate automorphic numbers in base 14
std::string calculate_sum(int base, int max_digits)
{
    cpp_int total_sum = 1;
    std::set<cpp_int> visited;
    visited.insert(1);

    std::vector<int> residues = {7, 8}; // Starting residues modulo 14
    for (int r = 0; r < residues.size(); ++r)
    {
        cpp_int n_k = residues[r];
        cpp_int M = 1;        

        for (int k = 1; true; ++k)
        {
            M *= base; // M = 14^k
            cpp_int n_k_square = n_k * n_k;
            cpp_int diff = n_k_square - n_k;
            cpp_int c = diff / (M / base);

            cpp_int denom = 2 * n_k - 1;
            cpp_int inv = mod_inverse(denom % base, base);

            if (inv == 0)
            {
                std::cout << "No modular inverse exists at k=" << k << ", cannot proceed." << std::endl;
                break;
            }

            cpp_int m = (-c * inv) % base;
            if (m < 0)
                m += base;

            n_k = n_k + m * (M / base);
            cpp_int element = n_k;

            

            cpp_int single_sum = 0;
            int num_digits = 0;

            while (element > 0)
            {
                single_sum += element % base;
                element /= base;
                num_digits++;
            }            

            if (num_digits > max_digits)
                break;

            if (visited.find(n_k) != visited.end())
                continue;

            visited.insert(n_k);
            
            total_sum += single_sum;

            if (num_digits % 1000 == 0)
                std::cout << num_digits << std::endl;            
        }        
    }

    return to_base_14(total_sum);
}


int main()
{
    int base = 14;
    int max_digits = 10000; // You can adjust this to generate more digits
    
    std::cout << calculate_sum(base, max_digits) << std::endl;

    return 0;
}
