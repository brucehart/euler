#include <bits/stdc++.h>

// Define symbol values
const std::unordered_map<std::string, int> symbol_values = {
    {"I", 1}, {"V", 5}, {"X", 10}, {"L", 50},
    {"C", 100}, {"D", 500}, {"M", 1000},
    {"IV", 4}, {"IX", 9}, {"XL", 40}, {"XC", 90},
    {"CD", 400}, {"CM", 900}
};

// List of symbols ordered from longest to shortest for validation
const std::vector<std::string> symbols_ordered = {
    "CM", "CD", "XC", "XL", "IX", "IV",
    "M", "D", "C", "L", "X", "V", "I"
};

// Probability definitions
const double PROB_SYMBOL = 0.14; // 14% for each symbol
const double PROB_STOP = 0.02;    // 2% for '#'
const int MAX_CONSECUTIVE_M = 15; // To prevent infinite 'M's

// Function to compute the value of a Roman numeral string
int roman_value(const std::string& s) {
    int total = 0;
    int i = 0;
    while (i < static_cast<int>(s.length())) {
        // Check for subtractive pair
        if (i + 1 < static_cast<int>(s.length())) {
            std::string pair = s.substr(i, 2);
            auto it = symbol_values.find(pair);
            if (it != symbol_values.end()) {
                total += it->second;
                i += 2;
                continue;
            }
        }
        // Single symbol
        std::string single = s.substr(i, 1);
        auto it_single = symbol_values.find(single);
        if (it_single != symbol_values.end()) {
            total += it_single->second;
            i += 1;
            continue;
        }
        // Invalid symbol
        return -1;
    }
    return total;
}

// Function to check if a string is a valid prefix of some minimal Roman numeral
bool is_valid_prefix(const std::string& s) {
    int n = static_cast<int>(s.length());
    if (n == 0) return true;

    // Dynamic Programming approach
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;

    for(int i = 0; i < n; ++i){
        if(!dp[i]) continue;
        for(const auto& sym : symbols_ordered){
            int len = static_cast<int>(sym.length());
            if(i + len > n){
                // Check if sym starts with s[i..]
                if(sym.substr(0, n - i) == s.substr(i, n - i)){
                    dp[n] = true;
                }
                continue;
            }
            if(s.substr(i, len) == sym){
                dp[i + len] = true;
            }
        }
    }
    return dp[n];
}

// Memoization cache
std::unordered_map<std::string, double> memo;

// Recursive function to compute expected value
double compute_expected_value(const std::string& current) {
    // Check if already computed
    auto it = memo.find(current);
    if(it != memo.end()) {
        return it->second;
    }

    // Compute the value of the current string
    int current_value = 0;
    if(!current.empty()) {
        current_value = roman_value(current);
        if(current_value == -1){
            // Invalid string should not be processed
            return 0.0;
        }
    }

    // Start with the stopping probability
    double expected = PROB_STOP * static_cast<double>(current_value);

    // Probability mass for symbols
    double total_prob = 0.0;

    // Iterate over all possible symbols
    const std::vector<char> append_symbols = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for(auto c : append_symbols){
        // Compute new string
        std::string new_s = current + static_cast<char>(c);

        // Count consecutive 'M's
        int cnt_M = 0;
        int len = static_cast<int>(new_s.length());
        for(int i = len - 1; i >=0 && new_s[i] == 'M'; --i){
            cnt_M++;
        }
        if(c == 'M' && cnt_M > MAX_CONSECUTIVE_M){
            // Exceeds maximum consecutive 'M's, skip
            continue;
        }

        // Check if new_s is a valid prefix
        if(is_valid_prefix(new_s)){
            // Valid, recurse
            double sub_expected = compute_expected_value(new_s);
            expected += PROB_SYMBOL * sub_expected;
            total_prob += PROB_SYMBOL;
        }
        else{
            // Invalid append, skip
            // According to the problem statement, invalid appends are skipped and we try the next symbol
            // So effectively, we ignore this symbol and do not add anything to expected
            // Alternatively, since symbols are selected independently, we might need to adjust probabilities
            // However, based on the initial problem description, invalid symbols are simply skipped
            // without affecting the overall probabilities
            // Therefore, we don't add anything to expected for invalid symbols
            // and they contribute to the probability of attempting other symbols
            // So PROB_SYMBOL is effectively redistributed to valid symbols
            // To maintain the total probability, we need to account for skipped symbols
            // This is implicitly handled by the recursive function, as skipped symbols do not contribute
            // to the expected value
            continue;
        }
    }

    // Normalize expected value by the total probability of valid symbol appends
    // However, in the original problem, symbols are generated one by one,
    // and if a symbol is invalid, it is skipped, and the process continues with the next symbol
    // Therefore, the actual probability of stopping remains PROB_STOP,
    // and the PROB_SYMBOL for invalid symbols is effectively ignored.

    // Memoize and return
    memo[current] = expected;
    return expected;
}

int main(){
    // Start with empty string
    std::string start = "";
    double expected_value = compute_expected_value(start);

    // Output the expected value with 8 decimal places
    printf("%.8lf\n", expected_value);

    return 0;
}
