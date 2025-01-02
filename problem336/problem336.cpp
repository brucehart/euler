#include <iostream>
#include <string>
#include <algorithm>

/**
 * Count the number of "Simple Simon" rotations needed
 * to arrange the input string into ascending order (A..Z).
 * Returns the rotation count. If it becomes clear during
 * simulation that this arrangement cannot be a "maximix"
 * (i.e., the required rotations won't reach the theoretical max),
 * the function returns an immediate value (e.g., -1) to indicate
 * early disqualification.
 */
int countSimonRotations(const std::string &arrangement)
{
    // Work on a mutable copy
    std::string s = arrangement;
    const int n = static_cast<int>(s.size());

    int rotations = 0;

    // For each position i, place the expected letter 'A' + i
    // using Simple Simon's 2-step method if needed.
    // We'll go up to n-1 because the last carriage, if out of place,
    // would still require one final rotation. We'll handle that below.
    for (int i = 0; i < n - 1; ++i)
    {
        // The expected carriage character
        char expect = static_cast<char>('A' + i);

        // If the carriage already at position i is 'expect',
        // this arrangement cannot be a maximix (it’s being solved "too easily").
        if (s[i] == expect)
        {
            return -1; // Early disqualification
        }

        // Find where 'expect' currently is, searching from i onward
        int j = i;
        while (j < n && s[j] != expect)
        {
            ++j;
        }

        // If for some reason we didn't find it (shouldn't happen if we use permutations of A..K),
        // just skip.
        if (j == n)
        {
            return -1;
        }

        // Step 1: If the expected carriage isn't already at the end, rotate to bring it to end
        if (j != n - 1)
        {
            // Reverse s[j..n-1]
            std::reverse(s.begin() + j, s.end());
            rotations++;
        }

        // Step 2: Rotate from i..n-1 to bring the expected carriage from the end to position i
        std::reverse(s.begin() + i, s.end());
        rotations++;
    }

    // At this point, the last position (index n-1) should be 'A'+(n-1).
    // If it's not, we need one more rotation. If that rotation wouldn't
    // place the correct letter at the end, it's also disqualified.
    if (s[n - 1] != 'A' + (n - 1))
    {
        // Reverse s[(n-1)..(n-1)], which is effectively a no-op,
        // or you can consider that we *would* do a rotation if the final letter
        // is wrong, but that rotation wouldn't fix anything if the wrong letter is there.
        // For correctness with Simon's method, let's see if it's indeed the correct letter
        // somewhere else to do a final move:
        // But if it's out of place, we do one last rotation.
        // We'll assume it's still fixable with one final rotation, but if the
        // correct letter is not at index n-1, Simple Simon *would* do one last reverse.
        // That means:
        rotations++;
    }

    return rotations;
}

int main()
{
    // We want to find the 2011th (default) maximix arrangement among permutations
    // of length 11 (default). However, per the problem statement we can read them
    // from stdin to keep code flexible.
    // If no input is provided, we'll default to length=11 and stopWhenFound=2011.

    int length = 11;
    int stopWhenFound = 2011;

    // If you want to allow user input, uncomment this:
    // std::cin >> length >> stopWhenFound;
    // If there's no input, the defaults above are used.

    // Create a string of letters 'A'.. up to the (length)th letter
    // For length=11, that means "ABCDEFGHIJK"
    std::string base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string train = base.substr(0, length); // e.g. "ABCDEFGHIJK" for length=11

    // Calculate the theoretical max rotations for a "maximix"
    // 2*(n-1) - 1
    unsigned int maxRotations = (length - 1) * 2 - 1;  // e.g. 19 if length=11

    // We'll iterate all permutations in lexicographic order and
    // count how many are "maximix" permutations. The 2011th we find
    // in sorted order is our answer.

    long long numFound = 0;
    std::string answer;

    // Ensure we start from the lowest lexicographic arrangement:
    // "ABC..."  Then we'll go up using next_permutation.
    std::sort(train.begin(), train.end());

    do
    {
        // Small early check: If it starts with 'A' or 'B', skip, because
        // those are never "worst" starts for Simon (too easy).
        if (train[0] == 'A' || train[0] == 'B')
        {
            continue;
        }

        // Simulate Simple Simon's rotation process on this permutation
        int rotations = countSimonRotations(train);

        // If rotations == maxRotations, we have a maximix arrangement
        if (rotations == static_cast<int>(maxRotations))
        {
            numFound++;
            if (numFound == stopWhenFound)
            {
                answer = train;
                break;
            }
        }
    }
    while (std::next_permutation(train.begin(), train.end()));

    // Output the result
    std::cout << answer << std::endl;

    return 0;
}
