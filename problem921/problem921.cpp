#include <bits/stdc++.h>

// We do *not* use "using namespace std;" per request.

namespace {

static const long long MOD = 398874989LL;

// Fix x into [0..MOD-1].
inline long long modFix(long long x) {
    x %= MOD;
    return (x < 0) ? x + MOD : x;
}

// (a+b) mod M
inline long long addMod(long long a, long long b) {
    long long s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}

// (a-b) mod M
inline long long subMod(long long a, long long b) {
    long long d = a - b;
    if (d < 0) d += MOD;
    return d;
}

// (a*b) mod M, using 128-bit intermediate if available
inline long long mulMod(long long a, long long b) {
    __int128 r = ( __int128 )a * b;
    r %= MOD;
    return (long long) r;
}

// fast exponent
long long powMod(long long base, long long exp) {
    long long result = 1;
    long long cur = base % MOD;
    while (exp > 0) {
        if (exp & 1) {
            __int128 tmp = ( __int128 )result * cur;
            result = (long long)(tmp % MOD);
        }
        __int128 tmp = ( __int128 )cur * cur;
        cur = (long long)(tmp % MOD);
        exp >>= 1;
    }
    return result;
}

// inverse of a mod M (M prime => use Fermat's little theorem)
long long invMod(long long a) {
    // a^(MOD-2) mod M
    return powMod(a, MOD - 2);
}

// We often need to handle expressions A + B sqrt(5).  We'll store them
// as (A,B) mod M.  We'll also keep a denominator D mod M, so the fraction
// is (A + B sqrt(5)) / D in the ring.  We'll maintain the condition that
// A = 1 mod M after each iteration (because a_n always has the constant
// part = 1 in the numerator in the problem statement).
struct ABO {
    // a_n = (A + B sqrt(5)) / D  mod M
    // For our problem: A should be 1 (mod M) once we fix the representation
    // after computing each next state.  B = p_n, D = q_n mod M.
    long long A;  
    long long B;  
    long long D;  
};

// Addition in that ring: (A1 + B1 sqrt(5))/D1 + (A2 + B2 sqrt(5))/D2
// => common denominator D1*D2
// => numerator = (A1 + B1 sqrt(5))*D2 + (A2 + B2 sqrt(5))*D1
// => final ABO with denominator D1*D2.
ABO addABO(const ABO &x, const ABO &y) {
    // newDen = x.D * y.D mod M
    long long newDen = mulMod(x.D, y.D);

    // We represent everything mod M:
    // numerator = (x.A + x.B sqrt(5)) * y.D  +  (y.A + y.B sqrt(5)) * x.D
    // So the A-part is x.A*y.D + y.A*x.D + 5*(???) ??? Actually no, careful:
    // There's no cross with 5 unless we multiply the B parts. But we're adding, not multiplying.
    // For addition:
    //   real-part-of-sqrt(5) doesn't mix because we do:
    //   (A1 + B1 sqrt(5)) * y.D => (A1*y.D) + (B1*y.D) sqrt(5)
    //   likewise for the other term.  Then we sum.
    // So:
    //   newA = x.A*y.D + y.A*x.D
    //   newB = x.B*y.D + y.B*x.D
    long long newA = addMod( mulMod(x.A, y.D), mulMod(y.A, x.D) );
    long long newB = addMod( mulMod(x.B, y.D), mulMod(y.B, x.D) );
    return ABO{ newA, newB, newDen };
}

// Multiplication:
// (A1 + B1 sqrt(5))/D1 * (A2 + B2 sqrt(5))/D2
// => numerator = (A1 + B1 sqrt(5)) * (A2 + B2 sqrt(5))
// => = (A1*A2 + 5 B1 B2) + (A1 B2 + A2 B1) sqrt(5)
// => denominator = D1 * D2
ABO mulABO(const ABO &x, const ABO &y) {
    long long newDen = mulMod(x.D, y.D);
    // numerator:
    long long A1A2 = mulMod(x.A, y.A);
    long long B1B2 = mulMod(x.B, y.B);
    long long partA = addMod(A1A2, mulMod(5LL, B1B2)); 
    long long partB = addMod( mulMod(x.A, y.B), mulMod(x.B, y.A) );
    return ABO{ partA, partB, newDen };
}

// Compute the multiplicative inverse of (A + B sqrt(5)) / D in the ring mod M.
//
// We'll do:  inv( (A + B sqrt(5))/D ) =  D / (A + B sqrt(5))  in that ring
// => multiply top and bottom by conj(A,B) => A - B sqrt(5).
// => denominator = (A + B sqrt(5)) * (A - B sqrt(5)) = A^2 - 5 B^2 mod M
// => final ABO = ( D*(A - B sqrt(5)),  1 ) / denominator
//
// So in ABO form, that means ABO{ A', B', D' }, with
//   A' =  A*(D)  [because we multiply the numerator? Actually let's be precise. 
// Actually: 
//   top = D*(A - B sqrt(5))
//        => A_top = D*A,   B_top = D*(-B) mod
//   bottom = (A^2 - 5B^2)*1
// => we must incorporate denominator "denReal" into ABO's D.
//
// So final ABO = (A_top, B_top) / [ (D_x) * denReal = 1 * denReal ? ]
// Careful: the ABO says "the fraction is (A + B sqrt(5)) / D". So we want
// "the fraction" = [D*A, -D*B sqrt(5)] / [ denReal ], i.e. ABO{ D*A mod M, -D*B mod M, denReal }. 
// But we must multiply the old denominator x.D as well?? Actually the entire old ABO is 
//   (x.A + x.B sqrt(5)) / x.D 
// We want 1 / that => x.D / (x.A + x.B sqrt(5)) => multiply top & bottom by conj => ...
// => final ABO = (x.D*x.A, x.D*(-x.B)) / [ x.A^2 - 5 x.B^2 ], ignoring mod for the moment.
//
//   Because the fraction is
//        x.D * (A - B sqrt(5))
//       / [ (A + B sqrt(5)) (A - B sqrt(5)) ]
// => denominator = A^2 - 5 B^2 (mod M).
// => That is ABO{ x.D*A, x.D*(-B), (A^2 - 5 B^2) } in mod M.
//
// We'll implement that:
ABO invABO(const ABO &x) {
    // realDen = A^2 - 5 (B^2), mod M
    long long A2 = mulMod(x.A, x.A);
    long long B2 = mulMod(x.B, x.B);
    long long realDen = subMod(A2, mulMod(5LL, B2)); // (A^2 - 5B^2) mod M
    // multiply top by x.D
    long long newA = mulMod(x.D, x.A);
    long long newB = mulMod(x.D, (MOD - x.B)); // -B mod M => (MOD - x.B)
    // ABO => ( newA, newB ) / realDen
    return ABO{ newA, newB, realDen };
}

// Division: X / Y = X * inv(Y)
ABO divABO(const ABO &x, const ABO &y) {
    ABO iy = invABO(y);
    return mulABO(x, iy);
}

// Make a constant c => (c + 0*sqrt(5)) / 1
ABO makeConst(long long c) {
    ABO ret;
    ret.A = modFix(c);
    ret.B = 0;
    ret.D = 1;
    return ret;
}

// We want a function "normalize" that forces A=1 mod M by dividing numerator & denominator
// by A.  That is how we ensure each ABO truly represents (1 + p sqrt(5))/q at the end.
ABO normalizeABO(const ABO &x) {
    // We have x = (x.A + x.B sqrt(5)) / x.D. 
    // If we want new ABO y with y.A=1 => multiply top & bottom by inv(x.A).
    // factor = invMod(x.A)
    // => newA = 1, newB = x.B * factor mod, newD = x.D * factor mod
    // Then y = (1 + newB sqrt(5))/ newD.  Perfect for our problem's form.
    // If x.A=0 mod M, that would be a problem (the real fraction might not have a constant part).
    // The problem statement's sequence never leads to an actual 0 for the constant part in real integers,
    // but mod M there's a risk.  Usually the problem's modulus is chosen to avoid that fiasco.
    long long fac = invMod(x.A); // might fail if x.A=0 mod M, but let's proceed
    ABO y;
    y.A = 1;  // forced
    y.B = mulMod(x.B, fac);
    y.D = mulMod(x.D, fac);
    return y;
}

// For the problem: a_n = (1 + p_n sqrt(5))/ q_n in real integers => ABO => (A=1, B=p_n, D=q_n) mod M.
//
// We define nextA( ) to compute
//   a_{n+1} = a_n * [a_n^4 + 10 a_n^2 + 5] / [5 a_n^4 + 10 a_n^2 + 1]
// in ABO form.  Then we "normalize" so that A=1 mod M again.
ABO nextA(const ABO &x) {
    // We'll do x^2, x^4 using repeated multiplication.
    ABO x2 = mulABO(x, x);         // a_n^2
    ABO x4 = mulABO(x2, x2);       // a_n^4

    ABO cst5 = makeConst(5);
    ABO cst10= makeConst(10);
    ABO cst1 = makeConst(1);

    // numerator portion: x^4 + 10 a_n^2 + 5
    ABO sumN = addABO(x4, mulABO(cst10, x2));  // x^4 + 10 x^2
    sumN = addABO(sumN, cst5);                // + 5

    // denominator portion: 5 a_n^4 + 10 a_n^2 + 1
    ABO sumD = addABO(mulABO(cst5, x4), mulABO(cst10, x2)); 
    sumD = addABO(sumD, cst1);

    // So the fraction is: x * sumN / sumD
    ABO top = mulABO(x, sumN);
    ABO frac = divABO(top, sumD);

    // Now normalize so that the fraction has ABO => (1 + B' sqrt(5))/ D'.
    ABO y = normalizeABO(frac);
    return y;
}

// s(n) = p_n^5 + q_n^5 mod M, given ABO => (1 + p_n sqrt(5))/ q_n => p_n=B, q_n=D
long long sOf(const ABO &x) {
    // p = x.B, q = x.D
    auto fifthPower = [&](long long v){
        // v^5 = v * v^4
        long long v2 = mulMod(v, v);
        long long v4 = mulMod(v2, v2);
        return mulMod(v, v4);
    };
    long long p5 = fifthPower(x.B);
    long long q5 = fifthPower(x.D);
    return addMod(p5, q5);
}

} // end anonymous namespace

int main(){
    // 1) Build the sequence a_n in ABO form, starting with
    //    a_0 = (sqrt(5}+1)/2  => p_0=1, q_0=2 => ABO => (A=1, B=1, D=2).
    //    We'll detect the cycle by storing (B, D) in a map.

    ABO cur; 
    cur.A = 1 % MOD;    // constant part
    cur.B = 1 % MOD;    // p_0 = 1
    cur.D = 2 % MOD;    // q_0 = 2

    // We'll store ABO states in a vector so sVals[n] = s( a_n ).
    // We'll do cycle detection using (B,D) as the "state key."
    std::unordered_map< long long, int > seen; 
    // But we must store both B and D in the key.  A quick hack:
    //   key = ( (long long)B << 32 ) ^ D
    // (assuming 32 bits each).  Or use a 128-bit approach.  Or use an std::map with pair. 
    // For speed, we can do:
    auto makeKey = [&](long long b, long long d){
        // b,d in [0..MOD-1], combine into 64 bits:
        // risk of collisions if MOD>2^31, but let's assume it is safe or do a 128-bit hash.
        // We'll do a 64-bit approach with a big shift. 
        return ( (unsigned long long)b << 32 ) ^ (unsigned long long)d;
    };
    // We also need to store an index. 
    // We'll keep sVals in a vector, so sVals[n] = s( a_n ).

    std::vector<long long> sVals;
    sVals.reserve(2000000);

    // Store n=0
    sVals.push_back( sOf(cur) );
    long long key0 = makeKey(cur.B, cur.D);
    seen[key0] = 0;

    int prePeriod = 0, cycleLen = 0;

    // Generate until cycle found:
    while (true) {
        ABO nxt = nextA(cur);
        long long sNext = sOf(nxt);
        int nNext = (int) sVals.size();
        sVals.push_back(sNext);

        long long k = makeKey(nxt.B, nxt.D);
        if (seen.find(k) != seen.end()) {
            // found cycle
            prePeriod = seen[k];
            cycleLen = nNext - prePeriod;
            break;
        }
        seen[k] = nNext;
        cur = nxt;
    }

    // We have s(n) for n=0..(prePeriod+cycleLen-1).
    // define a function getS(n) that returns s(n) mod M for all n>=0
    auto getS = [&](long long n){
        if (n < prePeriod) {
            return sVals[(size_t)n];
        } else {
            long long pos = prePeriod + ((n - prePeriod) % cycleLen);
            return sVals[(size_t)pos];
        }
    };

    // Now we compute S(m) = sum_{i=2..m} s( F_i ), with m=1,618,034. 
    // We'll do a straightforward O(m) loop, building fibonacci mod (prePeriod+cycleLen).
    const long long m = 1618034LL;
    long long bigMod = prePeriod + cycleLen; // for indexing s(n)

    // build fibonacci mod bigMod
    std::vector<long long> fib(m+1, 0LL);
    fib[1] = 1 % bigMod;
    if (m>=2) fib[2] = 1 % bigMod;
    for (int i=3; i<=(int)m; i++){
        fib[i] = ( fib[i-1] + fib[i-2] ) % bigMod;
    }

    // sum s( F_i )
    long long answer = 0LL;
    for (int i=2; i<=(int)m; i++){
        long long idx = fib[i];
        long long val = getS(idx);
        answer = addMod(answer, val);
    }

    std::cout << answer << std::endl;
    return 0;
}

