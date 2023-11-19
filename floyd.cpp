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


/**
 * Applies the Floyd-Warshall algorithm to find the shortest paths between all pairs of vertices in a graph.
 *
 * @param graph a reference to a 2D vector representing the graph adjacency matrix
 * @param n the number of vertices in the graph
 * @param problemName a constant reference to a string representing the name of the problem
 *
 * @throws None
 */
void floydImplementation(vector<vector<int>>& graph, int n, const string& problemName) {
    // Print problem information to output file
    outputFile << problemName << " n = " << n << endl;
    outputFile << "P Matrix:" << endl;

    // Create matrices and vectors to store distances, intermediate nodes, and paths
    vector<vector<int>> dist(graph);
    vector<vector<vector<int>>> paths(n, vector<vector<int>>(n, vector<int>()));
    vector<vector<int>> p(n, vector<int>(n));

    // Initialize the intermediate node matrix to -1
    for (int a = 0; a < n; ++a) {
        for (int b = 0; b < n; ++b) {
            p[a][b] = -1;
        }
    }

    // Initialize paths with direct edges
for (int j = 0; j < n; ++j) {
    for (int k = 0; k < n; ++k) {
        if (graph[j][k] != INF) {
            paths[j][k] = {j, k};
        }
    }
}
    // Apply the Floyd-Warshall algorithm
    for (int l = 0; l < n; ++l) {
    for (int r = 0; r < n; ++r) {
        for (int q = 0; q < n; ++q) {
            if (dist[r][l] != INF && dist[l][q] != INF && dist[r][l] + dist[l][q] < dist[r][q]) {
                dist[r][q] = dist[r][l] + dist[l][q];
                p[r][q] = l;
                paths[r][q] = paths[r][l];
                paths[r][q].insert(paths[r][q].end(), paths[l][q].begin() + 1, paths[l][q].end());
            }
        }
    }
}
    // Print the intermediate node matrix
    for (int c = 0; c < n; c++) {
        for (int d = 0; d < n; d++) {
            outputFile << p[c][d] + 1 << " ";
        }
        outputFile << endl;
    }

    // Print shortest paths and their lengths
    for (int x = 0; x < n; ++x) {
        outputFile << "V" << x + 1 << "-Vj: shortest path and length" << endl;
        for (int y = 0; y < n; ++y) {
            outputFile << "V" << paths[x][y][0] + 1;
            for (int z = 1; z < paths[x][y].size(); ++z) {
                outputFile << " V" << paths[x][y][z] + 1;
            }
            outputFile << ": " << dist[x][y] << endl;
        }
        outputFile << endl;
    }
}

/**
 * Reads input from a file and performs the Floyd-Warshall algorithm on each problem.
 * 
 * @param inputFileName The name of the input file.
 * @param nValues A map to store the problem names and their corresponding sizes.
 * @param matrices A map to store the problem names and their corresponding adjacency matrices.
 * 
 * @return True if the file was successfully read, False otherwise.
 */
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

// Main function
int main(int argc, char* argv[]) {
    // Checking command-line arguments number
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <graph-file>" << endl;
        return 1;
    }

    // Get the input file name from the command-line arguments
    string inputFileName = argv[1];
    // Create a map to store the values of 'n'
    map<string, int> nValues;
    // Create a map to store the matrices
    map<string, vector<vector<int>>> matrices;

    // If reading the file fails, return with an error code
    if (!readFile(inputFileName, nValues, matrices)) {
        return 1;
    }

    // Close the outputFile
    outputFile.close();

    return 0;
}
