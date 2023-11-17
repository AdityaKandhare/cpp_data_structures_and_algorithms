#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Calculates the length of the Longest Common Subsequence (LCS) between two strings.
 * Also prints the LCS string.
 *
 * @param stringOne The first string.
 * @param stringTwo The second string.
 * @return The length of the LCS.
 */
int lcs(string stringOne, string stringTwo);

/**
 * Constructs the Longest Common Subsequence (LCS) string.
 *
 * @param stringOne The first string.
 * @param stringTwo The second string.
 * @param tempArray The dynamic programming table.
 * @return The LCS string.
 */
string constructLcs(const string& stringOne, const string& stringTwo, const vector<vector<int>>& tempArray);

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        cout << "Usage: ./lcs <input-string1> <input-string2>" << endl;
        return 1;  // Exit with an error code
    }

    // Extract input strings from command-line arguments
    string value1 = argv[1];
    string value2 = argv[2];

    // Calculate and print the length of the Longest Common Subsequence
    int result = lcs(value1, value2);

    return 0;  // Exit successfully
}

/**
 * Calculates the length of the longest common subsequence (LCS) between two strings.
 *
 * @param stringOne the first string
 * @param stringTwo the second string
 *
 * @return the length of the LCS
 *
 * @throws None
 */
int lcs(string stringOne, string stringTwo) {
    int p = stringOne.length();
    int q = stringTwo.length();

    // Create a 2D vector to store dynamic programming table
    vector<vector<int>> tempArray(p + 1, vector<int>(q + 1, 0));

    // Populate the dynamic programming table
    for (int g = 1; g <= p; g++) {
        for (int h = 1; h <= q; h++) {
            if (stringOne[g - 1] == stringTwo[h - 1]) {
                tempArray[g][h] = tempArray[g - 1][h - 1] + 1;
            } else {
                tempArray[g][h] = max(tempArray[g - 1][h], tempArray[g][h - 1]);
            }
        }
    }

    // Get the result (length of LCS)
    int result = tempArray[p][q];
    cout << "Length of LCS is : " << result << endl;

    // Construct and print the LCS string
    string lcsStr = constructLcs(stringOne, stringTwo, tempArray);
    cout << "LCS: " << lcsStr << endl;

    return result;
}

/**
 * Returns the longest common subsequence (LCS) of two input strings.
 *
 * @param stringOne The first input string.
 * @param stringTwo The second input string.
 * @param tempArray A 2D vector representing the temporary array used in the LCS calculation.
 *
 * @return The LCS of stringOne and stringTwo.
 *
 * @throws None.
 */
string constructLcs(const string& stringOne, const string& stringTwo, const vector<vector<int>>& tempArray) {
    string lcsStr;
    int s = stringOne.length(), t = stringTwo.length();

    // Reconstruct the LCS string by backtracking through the table
    while (s > 0 && t > 0) {
        if (stringOne[s - 1] == stringTwo[t - 1]) {
            lcsStr = stringOne[s - 1] + lcsStr;
            s--;
            t--;
        } else if (tempArray[s - 1][t] > tempArray[s][t - 1]) {
            s--;
        } else {
            t--;
        }
    }

    return lcsStr;
}
