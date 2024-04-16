#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find minimum of two values
float min(float a, float b) {
    return (a < b) ? a : b;
}
int i,j,L,r,k;
// Function to calculate optimal BST cost using dynamic programming
float optimal_bst(float *probs, int n) {
    float cost[n + 1][n + 1];

    // Initializing cost matrix
    for (i = 0; i <= n; ++i) {
        for (j = 0; j <= n; ++j) {
            cost[i][j] = 0;
        }
    }

    // Constructing cost matrix
    for (L = 1; L <= n; ++L) {
        for (i = 0; i <= n - L; ++i) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;
            float sum = 0;
            for (k = i; k <= j; ++k) {
                sum += probs[k];
            }
            for (r = i; r <= j; ++r) {
                float c = (r == n) ? 0 : cost[r + 1][j];
                float b = (i == 0) ? 0 : cost[i][r - 1];
                cost[i][j] = min(cost[i][j], c + b + sum);
            }
        }
    }

    return cost[0][n - 1];
}

// Function to read input from file
float *read_input(const char *file_path, int *n) {
	int i;
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        exit(1);
    }

    // Read the number of probabilities
    fscanf(file, "%d", n);

    // Allocate memory for probabilities
    float *probs = (float *)malloc((*n) * sizeof(float));

    // Read probabilities from the file
    for ( i = 0; i < *n; ++i) {
        fscanf(file, "%f", &probs[i]);
    }

    // Close the file
    fclose(file);

    return probs;
}

int main() {
    const char *file_path = "opt.txt"; 
    int n;
    float *probs = read_input(file_path, &n);
    float min_cost = optimal_bst(probs, n);
    printf("Minimum cost of optimal BST: %.2f\n", min_cost);

    // Free allocated memory
    free(probs);

    return 0;
}
