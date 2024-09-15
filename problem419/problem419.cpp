#include <iostream>
#include <Eigen/Sparse>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>


typedef Eigen::SparseMatrix<double> SpMat;

struct SequenceElement
{
    std::string seq;
    std::vector<int> nextIdx;
};



std::vector<SequenceElement> readCSV(std::string filename) {
    std::vector<SequenceElement> data;
    std::ifstream file(filename);
    std::string line;
    // Skip the first line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string item;
        SequenceElement element;
        int col = 0;

        while (std::getline(ss, item, ',')) {
            if (col == 1) {
                element.seq = item;
            } else if (col == 3) {             
                
                item.erase(std::remove(item.begin(), item.end(), '('), item.end());
                std::replace(item.begin(), item.end(), ')', ' ');
                std::istringstream itemStream(item);
                std::string subItem;
                
                while (std::getline(itemStream, subItem, ' ')) {
                    if (subItem[0] < '0' || subItem[0] > '9' || subItem.length() == 0) continue;                    
                    element.nextIdx.push_back(std::stoi(subItem) - 1);
                }
                
            }
            col++;
        }
        data.push_back(element);
    }
    return data;
}

// Define types for convenience
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef Eigen::SparseMatrix<uint32> SpMat32;
typedef Eigen::Triplet<uint32> Triplet32;

// Custom hash function for pair<int, int>
struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        // A simple hash combination for pairs
        return std::hash<int>()(p.first) * 1000003 + std::hash<int>()(p.second);
    }
};

// Function to build a SparseMatrix<uint32> with counts
SpMat32 buildSparseMatrix(const std::vector<int>& rows, const std::vector<int>& cols) {
    // Ensure rows and cols have the same size
    if (rows.size() != cols.size()) {
        throw std::invalid_argument("Rows and Columns lists must have the same length.");
    }

    // Determine the size of the matrix
    int max_row = *std::max_element(rows.begin(), rows.end());
    int max_col = *std::max_element(cols.begin(), cols.end());
    int num_rows = max_row + 1;
    int num_cols = max_col + 1;

    // Count occurrences using a hash map
    std::unordered_map<std::pair<int, int>, uint32, pair_hash> count_map;
    for (size_t k = 0; k < rows.size(); ++k) {
        std::pair<int, int> key = {rows[k], cols[k]};
        count_map[key] += 1;
    }

    // Create triplet list from the count map
    std::vector<Triplet32> tripletList;
    tripletList.reserve(count_map.size());

    for (const auto& entry : count_map) {
        int row = entry.first.first;
        int col = entry.first.second;
        uint32 count = entry.second;
        tripletList.emplace_back(row, col, count);
    }

    // Initialize sparse matrix A
    SpMat32 A(num_rows, num_cols);
    A.setFromTriplets(tripletList.begin(), tripletList.end());

    return A;
}

// Function to perform sparse matrix multiplication with modulo 2^30
SpMat32 multiplyModulo(const SpMat32& A, const SpMat32& B, uint32 modulus) {
    // Ensure dimensions are compatible
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("Incompatible matrix dimensions for multiplication.");
    }

    // Temporary map to accumulate results
    std::unordered_map<std::pair<int, int>, uint32, pair_hash> result_map;

    // Iterate through each non-zero entry of A
    for (int k = 0; k < A.outerSize(); ++k) {
        for (SpMat32::InnerIterator itA(A, k); itA; ++itA) {
            int row = itA.row();
            int colA = itA.col();
            uint32 valA = itA.value();

            // Iterate through each non-zero entry of B corresponding to colA
            for (SpMat32::InnerIterator itB(B, colA); itB; ++itB) {
                int col = itB.col();
                uint32 valB = itB.value();

                // Compute the product and apply modulo
                uint64 product = static_cast<uint64>(valA) * static_cast<uint64>(valB);
                uint32 product_mod = static_cast<uint32>(product & (modulus - 1));

                // Accumulate the result with modulo
                std::pair<int, int> key = {row, col};
                uint32& accumulator = result_map[key];
                accumulator = (accumulator + product_mod) & (modulus - 1);
            }
        }
    }

    // Convert the result_map to triplet list
    std::vector<Triplet32> tripletList;
    tripletList.reserve(result_map.size());

    for (const auto& entry : result_map) {
        int row = entry.first.first;
        int col = entry.first.second;
        uint32 val = entry.second;
        if (val != 0) { // Only store non-zero entries
            tripletList.emplace_back(row, col, val);
        }
    }

    // Initialize the result sparse matrix
    SpMat32 C(A.rows(), B.cols());
    C.setFromTriplets(tripletList.begin(), tripletList.end());

    return C;
}

// Function to perform exponentiation by squaring with modulo
SpMat32 powerModulo(const SpMat32& A, uint64 exponent, uint32 modulus) {
    // Initialize result as the identity matrix
    int num_rows = A.rows();
    int num_cols = A.cols();
    std::vector<Triplet32> identityTriplets;
    identityTriplets.reserve(std::min(num_rows, num_cols));
    for (int i = 0; i < std::min(num_rows, num_cols); ++i) {
        identityTriplets.emplace_back(i, i, 1);
    }
    SpMat32 result(num_rows, num_cols);
    result.setFromTriplets(identityTriplets.begin(), identityTriplets.end());

    // Initialize base
    SpMat32 base = A;

    // Exponentiation by squaring
    while (exponent > 0) {
        if (exponent & 1) {
            result = multiplyModulo(result, base, modulus);
        }
        base = multiplyModulo(base, base, modulus);
        exponent >>= 1;
    }

    return result;
}


SpMat32 buildMatrix(std::vector<SequenceElement>& data) {
    int n = data.size();
    std::vector<Eigen::Triplet<unsigned int>> tripletList;
    SpMat32 A(n, n);   
    
    for (int i = 0; i < n; i++) {   
        if (data[i].nextIdx.size() > 0) {
            std::sort(data[i].nextIdx.begin(), data[i].nextIdx.end());
        }
        std::unordered_map<int, int> countMap;
        for (int idx : data[i].nextIdx) {
            countMap[idx]++;
        }
        for (const auto& entry : countMap) {
            tripletList.emplace_back(i, entry.first, entry.second);
        }
    }

    A.setFromTriplets(tripletList.begin(), tripletList.end());

    return A;
}

int main(){
    std::vector<SequenceElement> data = readCSV("LookAndSay.csv");
    auto A = buildMatrix(data);

    // Print out the matrix A
    std::cout << "Matrix A:\n";
    for (int k = 0; k < A.outerSize(); ++k) {
        for (SpMat32::InnerIterator it(A, k); it; ++it) {
            std::cout << "(" << it.row() << ", " << it.col() << "): " << it.value() << "\n";
        }
    }
    
    long long exponent = 1000000000000 - 8; // 10^12 - 8
  

    // Define the modulus as 2^30
    uint32 modulus = (1U << 30); // 2^30
    // Alternatively, using unsigned long long to prevent overflow
    // uint32 modulus = static_cast<uint32>((1ULL << 30));

    // Perform exponentiation
    std::cout << "Performing matrix exponentiation...\n";
    SpMat32 A_power = powerModulo(A, exponent, modulus);
    std::cout << "Exponentiation completed.\n";

        // Create a sparse row matrix with columns 23 and 38 set to 1 and the rest zero
        SpMat32 rowVector(1, A.cols());
        std::vector<Triplet32> rowTriplets;
        rowTriplets.emplace_back(0, 23, 1);
        rowTriplets.emplace_back(0, 38, 1);
        rowVector.setFromTriplets(rowTriplets.begin(), rowTriplets.end());

        // Multiply the row vector by A_power
        SpMat32 result = rowVector * A_power;

        // Print the resulting matrix
        std::cout << "Resulting matrix after multiplication:\n";
        for (int k = 0; k < result.outerSize(); ++k) {
            for (SpMat32::InnerIterator it(result, k); it; ++it) {
                std::cout << "(" << it.row() << ", " << it.col() << "): " << it.value() << "\n";
            }
        }

    // (Optional) Display non-zero elements (only feasible for small matrices)
    // For large matrices, consider writing to a file or processing differently
    std::cout << "Non-zero entries of A^" << exponent << " modulo " << modulus << ":\n";
    for (int k = 0; k < A_power.outerSize(); ++k) {
        for (SpMat32::InnerIterator it(A_power, k); it; ++it) {
            std::cout << "(" << it.row() << ", " << it.col() << "): " << it.value() << "\n";
        }
    }
    
    return 0;
    
}