#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <set>

using boost::multiprecision::cpp_int;


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
            ch = 'A' + digit - 10;
        n_base14 = ch + n_base14;
        x /= base;
    }
    if (n_base14 == "")
        n_base14 = "0";

    return n_base14;
}

std::string add_digits(std::set<std::string> automorphic_numbers)
{
    cpp_int sum = 0;

    for (auto it = automorphic_numbers.begin(); it != automorphic_numbers.end(); ++it)
    {
        std::string n_base14 = *it;
        for (int i = 0; i < n_base14.length(); ++i)
        {
            if (n_base14[i] >= 'A')
                sum += n_base14[i] - 'A' + 10;
            else
                sum += n_base14[i] - '0';
        }
    }

    return to_base_14(sum);
}

// Function to generate automorphic numbers in base 14
cpp_int generate_automorphic_numbers(int base, int max_digits, std::set<std::string>& automorphic_numbers)
{
    int residues[] = {7, 8}; // Starting residues modulo 14
    cpp_int total_sum = 0;
    cpp_int MAX_VALUE = pow(cpp_int(base), max_digits+1) - 1;

    for (int r = 0; r < 2; ++r)
    {
        cpp_int n_k = residues[r];
        cpp_int M = 1;
        std::cout << "Starting residue: " << residues[r] << std::endl;

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
            
            
            
            if (k > 10000)
            {
                std::cout << k << std::endl;
                std::cout << "***" << n_k << std::endl;
                std::cout << MAX_VALUE << std::endl;
                break;
            }

            while (n_k > 0)
            {
                total_sum += n_k % base;
                n_k /= base;
            }                      
        }        
    }

    return total_sum;
}

int main()
{
    int base = 14;
    int max_digits = 10000; // You can adjust this to generate more digits
    std::set<std::string> automorphic_numbers;
    automorphic_numbers.insert("1");    
    generate_automorphic_numbers(base, max_digits, automorphic_numbers);
    
    std::cout << add_digits(automorphic_numbers) << std::endl;

    return 0;
}
