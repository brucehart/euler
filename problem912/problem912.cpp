#include <bits/stdc++.h>

// We'll avoid "using namespace std"
namespace {
    static const int MOD = 1000000007;

    // We'll keep a structure to accumulate (T, M_odd, S1, S2) 
    // but interpret them differently from the original code:
    //
    //  - T       = total count of valid numbers in the subtree
    //              (including 0 if 0 fits in the subtree).
    //  - M_odd   = how many of those valid numbers are odd (mod MOD).
    //  - S1      = sum of countValid(y) for those odd numbers (mod MOD).
    //  - S2      = sum of (countValid(y))^2 for those odd numbers (mod MOD).
    //
    // Later we convert to sum of (rank(y))^2 using the formula:
    //      sum( (countValid(y)-1)^2 ) = S2 - 2*S1 + M_odd (all mod).
    //
    struct DPVal {
        long long T;    // total valid count in subtree (0..some max).
        long long M_odd; 
        long long S1;   // sum of countValid(y) for odd y
        long long S2;   // sum of (countValid(y))^2 for odd y
    };

    // Modular add / multiply
    static inline long long addMod(long long a, long long b) {
        return ( (a % MOD) + (b % MOD) ) % MOD;
    }
    static inline long long mulMod(long long a, long long b) {
        __int128 r = ( __int128 ) a * b;
        r %= MOD;
        return (long long) r;
    }

    // We'll store DP for counting how many valid in [0..x].
    // dpCount[pos][consec][less] = number of valid ways
    static long long dpCountCache[205][4][2];  
    static bool usedCount[205][4][2];

    // We'll store DP for the bigger sums:
    // dpSum[pos][consec][less] -> (T, M_odd, S1, S2)
    static DPVal dpSumCache[205][4][2];
    static bool usedSum[205][4][2];

    // Combine two DPVal sub-results with an offset in "T" for local positions
    // but here, "positions" are actually "countValid(y)", so we carefully combine:
    //
    // Suppose we have two disjoint subtrees A and B:
    //   - A has T_A valid numbers, 
    //   - B has T_B valid numbers
    // For an odd item in B with countValid-value c_B, 
    // the global countValid-value is c_B + T_A if we interpret each subtree 
    // as enumerating new valid numbers. 
    //
    // But in this problem, "countValid(y)" is actually 
    // the "number of valid integers in [0..y]" -- 
    // so we must add T_A to each c_B. Then 
    //   (c_B + T_A)^2 = c_B^2 + 2 T_A * c_B + T_A^2.
    //
    // So for the sum-of-squares portion:
    //   S2_new = A.S2
    //            + B.S2
    //            + 2*T_A*(sumOf(c_B over B_odd)) + (T_A^2)*(countOfB_odd)
    //
    // For the sum-of-lin portion:
    //   S1_new = A.S1 + [B.S1 + T_A*(countOfB_odd)]
    //
    // M_odd_new = A.M_odd + B.M_odd
    // T_new = A.T + B.T
    //
    // We'll do it all mod except T can stay 64-bit.
    //
    DPVal combineDP(const DPVal &A, const DPVal &B) {
        DPVal R;
        R.T = A.T + B.T;  
        R.M_odd = (A.M_odd + B.M_odd) % MOD;

        // We'll do T_A mod
        long long tA_mod = A.T % MOD;

        // S1
        {
            // B.S1 + tA_mod*B.M_odd
            long long addPart = addMod(B.S1, mulMod(tA_mod, B.M_odd));
            R.S1 = addMod(A.S1, addPart);
        }

        // S2
        {
            // B.S2
            // + 2*tA_mod* sumOfCount(B)    where sumOfCount(B) = B.S1
            // + tA_mod^2 * B.M_odd
            long long part = B.S2;
            // 2 * tA_mod * B.S1
            part = addMod(part, mulMod( mulMod(2LL, tA_mod), B.S1 ));
            // + tA_mod^2 * B.M_odd
            long long tA_sq = mulMod(tA_mod, tA_mod);
            part = addMod(part, mulMod(tA_sq, B.M_odd));
            R.S2 = addMod(A.S2, part);
        }

        return R;
    }

    // Convert decimal string to binary bits (MSB first). 
    std::vector<int> buildBits(const std::string &s) {
        if (s=="0") return {0};

        std::string curr = s;
        std::vector<int> revBits;
        while (curr != "0") {
            int lastDigit = curr.back() - '0';
            int parity = lastDigit % 2;
            revBits.push_back(parity);

            // Divide curr by 2
            int carry = 0;
            std::string nxt;
            bool leading = true;
            for (char c : curr) {
                int x = carry*10 + (c - '0');
                int q = x/2;
                int r = x%2;
                carry = r;
                if (leading && q==0) {
                    continue;
                }
                leading = false;
                nxt.push_back(char('0'+q));
            }
            if (nxt.empty()) nxt = "0";
            curr = nxt;
        }
        std::reverse(revBits.begin(), revBits.end());
        return revBits;
    }

    // Digit-DP to count how many valid in [0..bits].
    long long dfsCountValid(int pos, int consec, int less,
                            const std::vector<int> &bits) 
    {
        if (consec == 3) {
            return 0;  // invalid
        }
        if (pos == (int)bits.size()) {
            // We formed one integer (including possibly 0).
            return 1;
        }
        if (usedCount[pos][consec][less]) {
            return dpCountCache[pos][consec][less];
        }
        usedCount[pos][consec][less] = true;
        long long &res = dpCountCache[pos][consec][less];
        res = 0;

        int limit = (less ? 1 : bits[pos]);
        for (int b = 0; b <= limit; b++) {
            int nextConsec = (b == 1) ? consec + 1 : 0;
            if (nextConsec == 3) continue;
            int nextLess = (less || (b < limit)) ? 1 : 0;
            res += dfsCountValid(pos+1, nextConsec, nextLess, bits);
        }
        return res;
    }

    // Public wrapper to get how many valid in [0..x], i.e. countValid(x).
    long long countValid(const std::string &xDec) {
        auto vb = buildBits(xDec);
        memset(usedCount, false, sizeof(usedCount));
        long long c = dfsCountValid(0, 0, 0, vb);
        return c;  
    }

    // Digit-DP to compute (T, M_odd, S1, S2) for valid in [0..bits].
    DPVal dfsSum(int pos, int consec, int less, const std::vector<int> &bits) {
        if (consec == 3) {
            return DPVal{0,0,0,0};
        }
        if (pos == (int)bits.size()) {
            // We formed exactly one integer (which might be 0).
            // T=1, check if it's odd => that depends on the last bit placed
            // "consec>0" means last bit was '1', but we need a certain bit to confirm oddness.
            // Actually, if consec>0, that means the last placed bit was 1 -> odd
            // if consec=0, last bit was 0 -> even
            DPVal val;
            val.T = 1;
            if (consec > 0) {
                // odd
                // countValid(y) for this y = "local position" = 1 if we consider sub-subtree,
                // but in the global build, we will add offsets. 
                // We'll store it as S1=1, S2=1 for now, then offset during combination.
                val.M_odd = 1;
                val.S1 = 1;
                val.S2 = 1;
            } else {
                val.M_odd = 0;
                val.S1 = 0;
                val.S2 = 0;
            }
            return val;
        }
        if (usedSum[pos][consec][less]) {
            return dpSumCache[pos][consec][less];
        }
        usedSum[pos][consec][less] = true;
        DPVal &res = dpSumCache[pos][consec][less];
        res = DPVal{0,0,0,0};

        int limit = (less ? 1 : bits[pos]);
        for (int b = 0; b <= limit; b++) {
            int nextConsec = (b == 1) ? consec + 1 : 0;
            if (nextConsec == 3) {
                continue;
            }
            int nextLess = (less || (b<limit)) ? 1 : 0;
            DPVal sub = dfsSum(pos+1, nextConsec, nextLess, bits);
            res = combineDP(res, sub);
        }
        return res;
    }

    // We'll define sumOddRankSquares(x) to return
    //   \sum_{y odd, valid, y <= x} [rank(y)]^2,
    // but recall rank(y) = countValid(y) - 1.
    //
    // We let our DP compute:
    //   S2 = sum of (countValid(y))^2,
    //   S1 = sum of (countValid(y)), 
    //   M_odd = count of odd y,
    // all for y <= x.
    //
    // Then final = sum( (countValid(y)-1)^2 ) 
    //             = sum( (countValid(y))^2 ) 
    //               - 2 * sum( countValid(y) )
    //               + sum( 1 ) 
    //             = S2 - 2*S1 + M_odd.
    //
    long long sumOddRankSquares(const std::string &xDec) {
        auto vb = buildBits(xDec);
        memset(usedSum, false, sizeof(usedSum));
        DPVal dpRes = dfsSum(0, 0, 0, vb);

        // Now compute sum of (rank(y))^2 = sum( (countValid(y)-1)^2 )
        // = dpRes.S2 - 2 dpRes.S1 + dpRes.M_odd, all mod.
        // We must handle the mod carefully:
        long long part = dpRes.S2;                   // (countValid(y))^2 sum
        part = (part - 2LL*dpRes.S1) % MOD;          // subtract 2*sumCount
        part = (part + dpRes.M_odd) % MOD;           // add # odd
        if (part < 0) part += MOD;
        return part;
    }

    // For the binary search, we want the smallest m with countValid(m) >= N+1
    // Because rank(m) = countValid(m) - 1. 
    // So rank(m) >= N => countValid(m) >= N+1.
    //
    // We'll do decimal-based binary search up to ~2^80.
    //
    int cmpDecimal(const std::string &a, const std::string &b) {
        if (a.size() < b.size()) return -1;
        if (a.size() > b.size()) return 1;
        return a.compare(b) < 0 ? -1 : (a.compare(b)==0 ? 0 : 1);
    }

    std::string addDecimal(const std::string &a, const std::string &b) {
        // Add two large decimal strings
        std::string A = a, B = b;
        if (A.size() < B.size()) A.insert(A.begin(), B.size()-A.size(), '0');
        if (B.size() < A.size()) B.insert(B.begin(), A.size()-B.size(), '0');
        int carry = 0;
        int n = A.size();
        std::string sum(n,'0');
        for (int i=n-1; i>=0; i--) {
            int d = (A[i]-'0') + (B[i]-'0') + carry;
            carry = d/10; d%=10;
            sum[i] = char('0'+d);
        }
        if (carry) sum.insert(sum.begin(), char('0'+carry));
        return sum;
    }

    // Divide decimal string by 2, returning the floor result as a string
    std::string div2(const std::string &s) {
        int carry = 0;
        std::string half;
        for (char c : s) {
            int x = carry*10 + (c - '0');
            int d = x/2;
            carry = x%2;
            if (!(half.empty() && d==0)) {
                half.push_back(char('0'+d));
            }
        }
        if (half.empty()) half = "0";
        return half;
    }

    std::string addOne(const std::string &s) {
        std::string r = s;
        int i = (int)r.size()-1;
        int c = 1;
        while (i>=0 && c) {
            int d = (r[i]-'0') + c;
            c = d/10;
            d%=10;
            r[i] = char('0'+d);
            i--;
        }
        if (c) r.insert(r.begin(),'1');
        return r;
    }

    // Compare countValid(mid) with (N+1)
    //   return -1 if countValid(mid) <  (N+1)
    //   return  0 if countValid(mid) == (N+1)
    //   return  1 if countValid(mid) >  (N+1)
    int cmpCountValid(const std::string &mid, long long target) {
        long long c = countValid(mid);
        if (c < target) return -1;
        else if (c > target) return 1;
        return 0;
    }

    // The core function: find the smallest decimal m s.t. countValid(m) >= N+1
    std::string find_sN(long long N) {
        // Large enough upper bound ~ 2^80
        // "1208925819614629174706177" ~ 2^80+1
        std::string left = "0";
        std::string right = "1208925819614629174706177";

        long long target = N + 1; // we want countValid(m) >= target
        while (true) {
            if (cmpDecimal(left, right) >= 0) {
                // left >= right => done
                return left;
            }
            // mid = (left + right)//2 in decimal
            std::string sum = addDecimal(left, right);
            std::string mid = div2(sum);

            // Compare countValid(mid) with target
            int cc = cmpCountValid(mid, target);
            if (cc >= 0) {
                // countValid(mid) >= target => can move right to mid
                right = mid;
            } else {
                // < target => need bigger
                // left = mid + 1
                // but check mid vs left to avoid infinite loop
                if (cmpDecimal(mid, left)==0) {
                    // mid == left
                    // so left -> left+1
                    left = addOne(mid);
                } else {
                    left = addOne(mid);
                }
            }
        }
    }

} // end anonymous namespace


int main(){
    // We want F(10^16) 
    // 1) find s_{10^16}
    long long N = 10000000000000000LL; // 1e16

    std::string sN = find_sN(N);  
    // sN is decimal for the smallest m s.t. countValid(m) >= N+1 => rank(m) >= N => m = s_N.

    // 2) sum over odd y <= sN of (rank(y))^2
    //    but rank(y) = countValid(y) - 1
    //    we have a DP that returns sum( (countValid(y))^2 ), sum(countValid(y)), etc.
    long long raw = sumOddRankSquares(sN);

    // raw is exactly sum_{ odd y <= sN} [ (countValid(y)-1 )^2 ], modded
    // That is F(N).
    //
    // Output result mod 1e9+7
    std::cout << (raw % MOD) << std::endl;
    return 0;
}
