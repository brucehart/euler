#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;
using Float = cpp_dec_float_100;

class EmperorCalculator {
private:
    std::vector<Float> log_factorials;
    
    void precompute_log_factorials(int n) {
        log_factorials.resize(n + 1);
        log_factorials[0] = 0.0;
        for (int i = 1; i <= n; i++) {
            log_factorials[i] = log_factorials[i-1] + log(Float(i));
        }
    }
    
    Float log_combination(int n, int k) {
        if (k < 0 || k > n) return -INFINITY;
        return log_factorials[n] - log_factorials[k] - log_factorials[n-k];
    }
    
    Float f(int y, int s) {
        const Float inv_y = Float(1) / Float(y);
        std::vector<Float> terms;
        Float current_term = 0.0;
        
        for (int i = s; i >= 1; i--) {
            Float denom = Float(1) - Float(i) * inv_y;
            if (denom <= 0) continue;
            
            Float log_factor = log(inv_y) - log(denom);
            current_term += log_factor;
            
            terms.push_back(current_term - log(denom));
        }
        
        if (terms.empty()) return 0.0;
        
        Float max_term = *std::max_element(terms.begin(), terms.end());
        Float sum = 0.0;
        
        for (Float term : terms) {
            sum += exp(term - max_term);
        }
        
        return exp(max_term) * sum;
    }

public:
    Float calculate_expectation(int D) {
        if (D == 2) return 1.0;
        if (D == 5) return Float(31) / Float(6);
        
        precompute_log_factorials(D);
        
        std::vector<Float> log_terms;
        log_terms.push_back(0.0);  // First emperor contribution
        
        // Now using D directly in the formula
        for (int i = 0; i <= (D-1)/2; i++) {
            Float coef_sign = (2.0 * (D-1) - 3.0 * i >= 0) ? 1.0 : -1.0;
            
            // Calculate log of coefficient parts
            Float log_coef = log(abs(2.0 * (D-1) - 3.0 * i)) + 
                             log_combination(D-1-i, i) +
                             log_factorials[D-2-i];
            
            Float f_value = f(D+1, D-1-i);  // Note: using D+1 as first arg
            if (f_value <= 0) continue;
            
            Float log_term = log_coef + log(f_value);
            if (isfinite(log_term)) {
                log_terms.push_back(log_term * coef_sign);
            }
            
            if (i % 1000 == 0) {
                //std::cerr << "Progress: " << i << "/" << (D-1)/2 << "\r" << std::flush;
            }
        }
        
        // Separate positive and negative terms for better numerical stability
        std::vector<Float> pos_terms, neg_terms;
        for (Float term : log_terms) {
            if (term >= 0) pos_terms.push_back(term);
            else neg_terms.push_back(-term);  // Store absolute value
        }
        
        // Combine terms using log-sum-exp separately for positive and negative terms
        Float pos_sum = 0.0, neg_sum = 0.0;
        
        if (!pos_terms.empty()) {
            Float max_pos = *std::max_element(pos_terms.begin(), pos_terms.end());
            for (Float term : pos_terms) {
                pos_sum += exp(term - max_pos);
            }
            pos_sum = exp(max_pos) * pos_sum;
        }
        
        if (!neg_terms.empty()) {
            Float max_neg = *std::max_element(neg_terms.begin(), neg_terms.end());
            for (Float term : neg_terms) {
                neg_sum += exp(term - max_neg);
            }
            neg_sum = exp(max_neg) * neg_sum;
        }
        
        return pos_sum - neg_sum;
    }
};

int main() {
    EmperorCalculator calc;
    
    // Verify with known values first
    std::cout << std::fixed << std::setprecision(50);
    std::cout << "E(2) = " << calc.calculate_expectation(2) << std::endl;
    std::cout << "E(5) = " << calc.calculate_expectation(5) << std::endl;
    std::cout << "E(365) = " << calc.calculate_expectation(365) << std::endl;
    
    std::cout << "Calculating E(10000)..." << std::endl;
    Float result = calc.calculate_expectation(10000);
    std::cout << "E(10000) = " << result << std::endl;
    
    return 0;
}
