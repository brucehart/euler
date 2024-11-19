#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

// Function to compute the modular inverse of 'a' modulo 'm'
boost::multiprecision::cpp_int mod_inverse(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int m)
{
    boost::multiprecision::cpp_int m0 = m, t, q;
    boost::multiprecision::cpp_int x0 = 0, x1 = 1;

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
void generate_automorphic_numbers(int base, int digits)
{
    int residues[] = {0, 1, 7, 8}; // Starting residues modulo 14
    for (int r = 0; r < 4; ++r)
    {
        boost::multiprecision::cpp_int n_k = residues[r];
        boost::multiprecision::cpp_int M = 1;

        std::cout << "Starting residue: " << residues[r] << std::endl;

        for (int k = 1; k <= digits; ++k)
        {
            M *= base; // M = 14^k
            boost::multiprecision::cpp_int n_k_square = n_k * n_k;
            boost::multiprecision::cpp_int diff = n_k_square - n_k;
            boost::multiprecision::cpp_int c = diff / (M / base);

            boost::multiprecision::cpp_int denom = 2 * n_k - 1;
            boost::multiprecision::cpp_int inv = mod_inverse(denom % base, base);

            if (inv == 0)
            {
                std::cout << "No modular inverse exists at k=" << k << ", cannot proceed." << std::endl;
                break;
            }

            boost::multiprecision::cpp_int m = (-c * inv) % base;
            if (m < 0)
                m += base;

            n_k = n_k + m * (M / base);

            // Convert n_k to base 14 representation
            boost::multiprecision::cpp_int temp = n_k;
            std::string n_base14 = "";
            while (temp > 0)
            {
                int digit = (int)(temp % base).convert_to<int>();
                char ch;
                if (digit < 10)
                    ch = '0' + digit;
                else
                    ch = 'A' + digit - 10;
                n_base14 = ch + n_base14;
                temp /= base;
            }
            if (n_base14 == "")
                n_base14 = "0";

            std::cout << "k=" << k << ", n_k=" << n_base14 << std::endl;
        }
        std::cout << std::endl;
    }
}

int main()
{
    int base = 14;
    int digits = 5; // You can adjust this to generate more digits
    generate_automorphic_numbers(base, digits);
    return 0;
}

