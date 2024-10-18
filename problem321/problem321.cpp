#include <iostream>
#include <set>

typedef unsigned long long ull;

int main() {
    //M(n) = x*(x+2) and triangle numbers are y*(y+1)/2
    //Forms a Pell equation k^2 - 8*m^2 = -7 where n = (m-1)
    //Two miminum solutions are (1,1) and (2,5) and the recurrance relation is (k_n+1, m_n+1) = (3k_n + 8m_n, k_n + 3m_n)
    std::set<ull> n;

    ull m1 = 1;
    ull k1 = 1;

    ull m2 = 2;
    ull k2 = 5;

    ull m1_old, m2_old, k1_old, k2_old;
    
    //skip the zero case (m1-1)
    n.insert(m2 - 1);

    for (int i = 0; i < 40; i++)
    {       
        m1_old = m1;
        m2_old = m2;
        k1_old = k1;
        k2_old = k2;

        m1 = k1_old + 3*m1_old;
        k1 = 3*k1_old + 8*m1_old;

        m2 = k2_old + 3*m2_old;
        k2 = 3*k2_old + 8*m2_old;

        n.insert(m1 - 1);
        n.insert(m2 - 1);
    }

    ull sum = 0;
    for (auto it = n.begin(); it != n.end() && std::distance(n.begin(), it) < 40; ++it) {        
        sum += *it;
    }

    std::cout << sum << std::endl;

    return 0;
}