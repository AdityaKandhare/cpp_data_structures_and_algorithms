#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

// Input and output file streams
ifstream inputFile("input.txt");
ofstream outputFile("output.txt");

// Infinity value for representing unreachable distances
const int INF = INT_MAX;

bool readFile(const string& inputFileName, map<string, int>& nValues, map<string, vector<vector<int>>>& matrices) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cout << "Error opening the input file." << endl;
        return false;
    }

    string line;
    string inLineProblem;

    // Read input file line by line
    while (getline(inputFile, line)) {
        // Look for the line containing "n ="
        size_t found = line.find("n =");
        if (found != string::npos) {
            // Extract problem name and size
            inLineProblem = line.substr(0, found - 1);
            int n;
            istringstream(line.substr(found + 3)) >> n;
            nValues[inLineProblem] = n;

            // Read the adjacency matrix for the problem
            vector<vector<int>> matrix;
            for (int i = 0; i < n; ++i) {
                getline(inputFile, line);
                istringstream iss(line);
                matrix.emplace_back(istream_iterator<int>(iss), istream_iterator<int>());
            }
            matrices[inLineProblem] = matrix;

            // Call floydImplementation with problem information
            floydImplementation(matrix, n, inLineProblem);
        }
    }

    inputFile.close();
    return true;
}