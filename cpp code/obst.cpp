#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <numeric>

using namespace std;

float optimal_bst(const vector<float>& probs) {
    int n = probs.size();
    vector<vector<float> > cost(n + 1, vector<float>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        cost[i][i] = probs[i];
    }

    for (int L = 1; L <= n; ++L) {
        for (int i = 0; i <= n - L; ++i) {
            int j = i + L - 1;
            cost[i][j] = numeric_limits<float>::max();
            float sum = accumulate(probs.begin() + i, probs.begin() + j + 1, 0.0f);
            for (int r = i; r <= j; ++r) {
                float c = (r == n) ? 0 : cost[r + 1][j];
                float b = (i == 0) ? 0 : cost[i][r - 1];
                cost[i][j] = min(cost[i][j], c + b + sum);
            }
        }
    }

    return cost[0][n - 1];
}

vector<float> read_input(const string& file_path) {
    vector<float> probs;
    ifstream file("opt.txt");
    float probability;
    while (file >> probability) {
        probs.push_back(probability);
    }
    return probs;
}

int main() {
    string file_path = "opt.txt"; 
    vector<float> probs = read_input("opt.txt");
    float min_cost = optimal_bst(probs);
    cout << "Minimum cost of optimal BST: " << min_cost << endl;

    return 0;
}

