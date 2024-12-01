#include <iostream>
#include <vector>
#include <cstring>

static const int N = 20;
static const int MOD = 1000000007;

// Define orientations
enum Orientation {
    RIGHT_WAY_UP = 0,
    UPSIDE_DOWN = 1
};

// Struct to represent the state of the cups
struct CupState {
    int count;                    // Number of cups placed
    unsigned char status[N];     // Status of each cup: bit 0 for used, bit 1 for orientation

    CupState() : count(0) {
        memset(status, 0, sizeof(status));
    }

    // Copy constructor for passing by value
    CupState(const CupState& other) {
        count = other.count;
        memcpy(status, other.status, sizeof(status));
    }

    // Mark a cup as used with a specific orientation
    void useCup(int idx, Orientation ori) {
        status[idx] |= (1 << 0);        // Mark as used
        status[idx] |= (ori << 1);      // Set orientation
        count++;
    }

    // Check if a cup is used
    bool isUsed(int idx) const {
        return status[idx] & (1 << 0);
    }

    // Get the orientation of a cup
    Orientation getOrientation(int idx) const {
        return (Orientation)((status[idx] & (1 << 1)) >> 1);
    }
};

// Recursive function to count valid configurations
long long updateCount(CupState state, int setIdx) {
    // Base case: if all cups are used
    if (state.count == N) {
        return 1;
    }

    long long total = 0;

    // Explore all possible stacking options from the current cup

    // 1. Nesting: Place C_k inside C_{k+1}
    if (setIdx + 1 < N && !state.isUsed(setIdx + 1)) {
        CupState newState = state;
        newState.useCup(setIdx + 1, RIGHT_WAY_UP); // Assuming nesting preserves orientation
        total = (total + updateCount(newState, setIdx + 1)) % MOD;
    }

    // 2. Base-to-Base: Place C_{k+2} or C_{k-2} on top of upside-down C_k
    if (state.getOrientation(setIdx) == UPSIDE_DOWN) {
        // Place C_{k+2}
        if (setIdx + 2 < N && !state.isUsed(setIdx + 2)) {
            CupState newState = state;
            newState.useCup(setIdx + 2, RIGHT_WAY_UP); // Right-way-up on upside-down
            total = (total + updateCount(newState, setIdx + 2)) % MOD;
        }
        // Place C_{k-2}
        if (setIdx - 2 >= 0 && !state.isUsed(setIdx - 2)) {
            CupState newState = state;
            newState.useCup(setIdx - 2, RIGHT_WAY_UP);
            total = (total + updateCount(newState, setIdx - 2)) % MOD;
        }
    }

    // 3. Rim-to-Rim: Place C_{k+2} or C_{k-2} upside-down on top of right-way-up C_k
    if (state.getOrientation(setIdx) == RIGHT_WAY_UP) {
        // Place C_{k+2} upside-down
        if (setIdx + 2 < N && !state.isUsed(setIdx + 2)) {
            CupState newState = state;
            newState.useCup(setIdx + 2, UPSIDE_DOWN);
            total = (total + updateCount(newState, setIdx + 2)) % MOD;
        }
        // Place C_{k-2} upside-down
        if (setIdx - 2 >= 0 && !state.isUsed(setIdx - 2)) {
            CupState newState = state;
            newState.useCup(setIdx - 2, UPSIDE_DOWN);
            total = (total + updateCount(newState, setIdx - 2)) % MOD;
        }
    }

    // 4. Nesting: Alternatively, place smaller cup inside current cup if not already done
    // (Depending on problem specifics; adjust as necessary)

    return total;
}

int main() {
    CupState initialState;

    // Choose a unique starting point to avoid overcounting
    // For example, start with the smallest cup, C_0
    initialState.useCup(0, RIGHT_WAY_UP); // Starting with C_0 right-way-up

    long long count = updateCount(initialState, 0);

    std::cout << "S(" << N << ") = " << count % MOD << std::endl;

    return 0;
}
