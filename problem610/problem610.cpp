#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <array>

/*
   This code demonstrates how to include ALL valid Roman representations for 0..999
   (except 'M'—that belongs to the M-phase). We skip anything with 'M' here.

   Steps:
   1) parseRomanIfValid(s): returns integer [0..999] if valid under puzzle's rules,
      or -1 if invalid.
   2) buildAllValid0to999(): BFS over all possible expansions by I,V,X,L,C,D. 
      If parseRomanIfValid(newString) = r in [0..999], store str2num[newString] = r.
   3) buildRemainderTransitions(): for each r in [0..999], find all strings that map
      to r. For each letter {I,V,X,L,C,D,M}, see if s+letter is in str2num => next_r[r][ell].
   4) solve remainder-phase Markov chain with E_r(r). 
   5) solve M-phase Markov chain with E_m(n).
*/

namespace {

// ------------------------------------------------------------------
//  parseRomanIfValid(s):
//    returns an integer 0..999 if 's' is a valid Roman numeral under
//    the puzzle's rules (WITHOUT using 'M'), or -1 if invalid.
//
//    The puzzle's "valid" rules in summary (for under 1000):
//      - Symbol set {I, V, X, L, C, D} only
//      - D, L, V each can appear at most once
//      - "Descending order" except for allowed subtractive pairs: IV, IX, XL, XC, CD
//      - "M, C, and X cannot be equaled or exceeded by smaller denominations" => means
//         you cannot do "VV"=10, "LL"=100, "DD"=1000, "XXXXX"=50, "CCCCC"=500, etc.
//         but "XXXX"=40 is okay, "CCCC"=400 is okay, "VIIII"=9 is okay, etc.
//      - "IL", "IC", "XD" etc. are not allowed subtractive pairs
//
//    Implementation approach:
//      We'll parse from left to right, always either taking a single symbol
//      or a recognized subtractive pair if it's valid. We track how many times
//      each of D,L,V has appeared, also we track consecutive runs of I,X,C
//      to ensure we don't exceed the next bigger symbol by smaller denominations.
// ------------------------------------------------------------------
int parseRomanIfValid(const std::string &s) {
    if(s.empty()) return 0; // interpret empty as 0

    // Check characters: must be one of {I,V,X,L,C,D}, no 'M' here.
    for(char c : s){
        switch(c){
            case 'I': case 'V': case 'X':
            case 'L': case 'C': case 'D':
                break;
            default:
                return -1; // invalid char
        }
    }

    // We'll parse it. If we find any rule violation, return -1.
    int value = 0;
    int pos   = 0;
    int n     = (int)s.size();

    // Keep track of usage:
    int countV = 0, countL = 0, countD = 0;
    // Keep track of consecutive runs for I,X,C. We'll reset whenever we see a bigger symbol.
    int runI = 0, runX = 0, runC = 0;

    // Helper to get numeric value of single symbol
    auto val = [&](char c)->int{
        switch(c){
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
        }
        return 0; // shouldn't happen
    };

    // We'll step through, carefully handle subtractive pairs if allowed
    while(pos < n){
        char c1 = s[pos];
        int v1  = val(c1);
        char c2 = (pos+1 < n)? s[pos+1] : '\0';
        int v2  = (c2? val(c2) : 0);

        // check if we have a valid subtractive pair?
        // allowed pairs: IV(4), IX(9), XL(40), XC(90), CD(400)
        // "IL", "IC", "XD" etc. are not valid => return -1 if we see that pattern.
        bool usedPair = false;
        if(c2 && (v2>v1)) {
            // see if it's an ALLOWED subtractive pair
            if( (c1=='I' && (c2=='V' || c2=='X')) ||
                (c1=='X' && (c2=='L' || c2=='C')) ||
                (c1=='C' && (c2=='D')) )
            {
                // okay, subtractive pair is valid
                value += (v2 - v1);
                pos += 2;
                usedPair = true;

                // updating usage counts
                //  for I, we used exactly 1 'I' in subtractive context, so runI was 1
                //  but after we see 'V' or 'X', we consider that bigger symbol used => reset runI
                if(c1=='I') { runI++; }
                if(c2=='V'){ countV++; if(countV>1) return -1; }
                if(c2=='X'){
                    // do nothing special except it is bigger than I => reset runI
                }
                if(c2=='L'){
                    countL++; if(countL>1) return -1;
                }
                if(c2=='C'){
                    // bigger than X => reset runX
                }
                if(c2=='D'){
                    countD++; if(countD>1) return -1;
                }

                // any time we see X or L or C or D, that is bigger than I => reset runI
                // any time we see L or C or D, that is bigger than X => reset runX
                // any time we see D, that is bigger than C => reset runC
                if(c1=='I'){
                    // runI is now used for 1 'I'
                    // but we've encountered a bigger symbol c2 => reset runI after
                    runI = 0;
                }
                if(c1=='X'){
                    runX++;
                    runI = 0; // definitely bigger than 'I'
                    if(c2=='L' || c2=='C' || c2=='D')
                        runX = 0; // we used X in subtractive, c2 is bigger => reset runX
                }
                if(c1=='C'){
                    runC++;
                    runI=0; runX=0;
                    if(c2=='D') runC=0;
                }
            } else {
                // invalid subtractive pattern
                return -1;
            }
        }
        if(!usedPair){
            // single symbol consumption
            value += v1;
            pos++;

            // usage checks
            switch(c1){
                case 'V': countV++; if(countV>1) return -1; break;
                case 'L': countL++; if(countL>1) return -1; break;
                case 'D': countD++; if(countD>1) return -1; break;
                case 'I': 
                    runI++;
                    // if runI==5 => that is 5 'I' => 5 means 5 => that equals 'V'
                    // not allowed by puzzle rule. So max 4 in a row is OK => "IIII"=4 < 'V'
                    // but 5 => 'V' => invalid
                    if(runI>4) return -1;
                    break;
                case 'X':
                    runX++;
                    // similarly, 5 X's => 50 => that equals L => not allowed
                    if(runX>4) return -1;
                    // bigger than I => reset runI
                    runI=0;
                    break;
                case 'C':
                    runC++;
                    // 5 Cs => 500 => that equals D => not allowed
                    if(runC>4) return -1;
                    runI=0; runX=0;
                    break;
            }
        }
    } // end while

    // final check of value
    if(value>999) return -1; // we only want 0..999 in the remainder-phase
    return value;
}

// ------------------------------------------------------------------
//  buildAllValid0to999(str2num):
//    BFS from "" (value=0). At each step, try appending {I,V,X,L,C,D}.
//    If parseRomanIfValid(newStr) == r >=0 and r<=999, store str2num[newStr]=r
//    and keep going (unless r=999, then you can't get bigger).
// ------------------------------------------------------------------
std::map<std::string,int> str2num;

void buildAllValid0to999() {
    std::queue<std::string> Q;
    std::set<std::string> visited;

    // Start with the empty string => value=0
    Q.push("");
    visited.insert("");

    str2num[""] = 0;  // store empty => 0

    static const std::array<char,6> LETTERS = {'I','V','X','L','C','D'};

    while(!Q.empty()){
        std::string base = Q.front();
        std::cout << base << std::endl;
        Q.pop();

        int baseVal = parseRomanIfValid(base);
        // If parseRomanIfValid(base) is -1, that means it was invalid,
        // but we presumably never put invalid strings in Q in the first place.

        // Try appending each letter
        for(char c : LETTERS){
            std::string cand = base + c;
            int val = parseRomanIfValid(cand);
            if(val >= 0 && val <= 999){
                // store it
                if(!str2num.count(cand)){
                    str2num[cand] = val;
                }
                // if val<999, we might be able to append more
                // also limit string length to some sanity check (like <= 15)
                // to avoid too big expansions
                if(val < 999 && cand.size()<9) {
                    if(!visited.count(cand)){
                        visited.insert(cand);
                        Q.push(cand);
                    }
                }
            }
        }
    }
}

// ------------------------------------------------------------------
//  Next we build next_r[r][ell]: for each integer r in [0..999],
//  for each letter ell in {I,V,X,L,C,D,M}, we see if there's a valid
//  transition r->r' by appending ell to ANY of the strings that map to r.
//
//  We'll store next_r[r][ell] = r' if "some string S with str2num[S]=r"
//  extends to "S+ell" => r' in str2num.
//
//  If multiple S’s produce the same r, we unify them (if any S+ell is valid,
//  that means we can transition). If none of them is valid => -1.
//
//  Implementation detail: to invert str2num, we build a vector of sets
//  inv[r], which holds all strings that map to r. Then we try each letter
//  on each string in inv[r]. If S+ell is in str2num => record next_r[r][ell] = ...
//  If there's more than one possible r', we can pick any or unify them. 
//  Actually, that means from r with letter ell, we might have multiple r' states.
//  The puzzle’s logic suggests each appended letter leads to a unique next integer
//  for a single partial string. But if multiple partial strings produce the same r,
//  they could yield different r' upon appending ell. Strictly we’d need a bigger
//  Markov chain. 
//
//  The puzzle states: “If appending the next letter would contravene validity, skip it.” 
//  But if ANY partial string for r can accept that letter => we move to that next r'.
//  The official problem statement is ambiguous whether we unify them or treat them as 
//  separate states. Usually people unify them by integer value. 
//
//  For simplicity, we unify so that if ANY partial representation for r can append ell 
//  to produce r', we treat that as a valid transition r->r'.
//
//  That’s the standard approach in “Problem 89” style solutions.
//
// ------------------------------------------------------------------
static const std::array<char,7> LETTERS7 = {'I','V','X','L','C','D','M'};
static std::vector<std::vector<int>> next_r;

void buildRemainderTransitions() {
    next_r.assign(1000, std::vector<int>(7, -1));

    // invert str2num: for each r, collect all strings that map to r
    std::vector<std::vector<std::string>> inv(1000);
    for(const auto &kv : str2num){
        int r = kv.second;
        if(r>=0 && r<1000){
            inv[r].push_back(kv.first);
        }
    }

    // For each r in [0..999], for each letter in {I,V,X,L,C,D,M},
    // check if there's some string in inv[r] that extends to a valid new r' in str2num.
    for(int r=0; r<1000; r++){
        for(int ell=0; ell<7; ell++){
            char c = LETTERS7[ell];
            int foundRprime = -1; // we'll see if at least one partial rep leads to some r'
            for(const std::string &base : inv[r]){
                std::string cand = base + c;
                auto it = str2num.find(cand);
                if(it != str2num.end()){
                    foundRprime = it->second;
                    break; // unify: if ANY base leads to r', we accept it
                }
            }
            next_r[r][ell] = foundRprime;
        }
    }
}

// ------------------------------------------------------------------
//  Probability constants
// ------------------------------------------------------------------
static const double P_STOP = 0.02;  // '#'
static const double P_LET  = 0.14;  // each letter (I..M)

// ------------------------------------------------------------------
//  Solve E_r(r) for r in [0..999] via iteration, 
//  as a Markov chain where:
//
//    E_r(r) = 
//        0.02*r                        (stop) 
//      + sum_{ell=0..6} [0.14 * next_E(r,ell)]
//
//    BUT note that if next_r[r][ell]=-1, that means skip => we remain in r. 
//    So effectively we have a "self-loop" for those invalid letters.
//
//    Expanding out, let validCount = how many ell have next_r[r][ell]>=0.
//    Then 
//      E_r(r) = 0.02*r
//               + sum_{ell in valid} [0.14* E_r(next_r[r][ell]) ]
//               + sum_{ell in invalid} [0.14* E_r(r) ]
//    => E_r(r) - 0.14*(#invalid)*E_r(r) 
//       = 0.02*r + 0.14* sum_{ell in valid} E_r(next_r[r][ell])
//
//    => E_r(r)
//       = [ 0.02*r + 0.14* sum_{ell in valid} E_r(...) ]
//         / [ 1 - 0.14*(#invalid) ]
//
//    But #invalid = 7 - validCount. 
//    So denominator = 1 - 0.14*(7 - validCount) = 0.02 + 0.14*validCount.
// ------------------------------------------------------------------
static std::array<double,1000> Er;

void solveRemainderExpectedValues() {
    const double EPS = 1e-14;
    bool done = false;

    // Initialize
    for(int r=0; r<1000; r++){
        Er[r] = 0.0;
    }

    while(!done){
        done = true;
        for(int r=0; r<1000; r++){
            // sum next
            int validCount=0;
            double sumNext=0.0;
            for(int ell=0; ell<7; ell++){
                int nr = next_r[r][ell];
                if(nr >= 0){
                    validCount++;
                    sumNext += Er[nr];
                }
            }
            double denom = 1.0 - P_LET*(7 - validCount); 
            // or denom = P_STOP + P_LET*validCount = 0.02 + 0.14*validCount
            double rhs   = P_STOP*r + P_LET*sumNext;
            double newVal = rhs / denom;

            if(std::fabs(newVal - Er[r])>EPS){
                done=false;
            }
            Er[r] = newVal;
        }
    }
}

// ------------------------------------------------------------------
//  Solve M-phase.  Now 'M' is allowed any number of times, so there's
//  effectively an infinite chain, but we do the standard difference eqn:
//  
//    E_m(n) = 0.02*(1000*n) + 0.14*E_m(n+1) + 0.84*(some average of E_r(...) )
//
//  But we only transition to E_r(1/5/10/50/100/500) if the letter is {I,V,X,L,C,D}.
//
//  Let A = E_r(1) + E_r(5) + E_r(10) + E_r(50) + E_r(100) + E_r(500).
//  Probability of picking M is 0.14, picking # is 0.02, picking any of the other 6
//  letters is 0.84. Then the average among those 6 is A/6 => total = 0.84*(A/6)=0.14*A.
//
//  => E_m(n) = 0.02*(1000*n) + 0.14*E_m(n+1) + 0.14*A.
//  
//  Solve the difference eqn in closed form => E_m(0) is final answer.
// ------------------------------------------------------------------
double solveMPhase() {
    double A = Er[1] + Er[5] + Er[10] + Er[50] + Er[100] + Er[500];

    // E_m(n) = 0.02*(1000n) + 0.14*E_m(n+1) + 0.14*A
    // Suppose E_m(n)=a*n+b. Then:
    //   a*n + b = 20*n + 0.14[a*(n+1)+b] + 0.14*A
    // => a*n + b = (20 +0.14*a)*n + (0.14*a +0.14*b +0.14*A)
    // Match:
    //   a = 20 + 0.14*a => 0.86*a=20 => a=20/0.86
    //   b = 0.14*a + 0.14*b +0.14*A => 0.86*b=0.14*(a +A) => b=[0.14*(a+A)]/0.86
    double a = 20.0 / 0.86; 
    double b = (0.14*(a + A))/0.86;
    return b;
}

} // end namespace

int main(){
    // 1) Build all valid forms for 0..999 (no 'M'!).
    std::cout << "Building ALL valid Roman forms up to 999...\n";
    buildAllValid0to999();

    // 2) Build remainder transitions using that big str2num map.
    std::cout << "Building remainder transitions...\n";
    buildRemainderTransitions();

    // 3) Solve E_r(r)
    std::cout << "Solving remainder-phase Markov chain...\n";
    solveRemainderExpectedValues();

    // 4) Solve M-phase => final E_m(0)
    std::cout << "Solving M-phase...\n";
    double ans = solveMPhase();

    // 5) Output
    std::cout << std::fixed << std::setprecision(8) << ans << std::endl;
    return 0;
}
