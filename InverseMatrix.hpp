#include <iostream>
#include <vector>
using namespace std;

// Function to get cofactor of mat[p][q] in cof[][]. n is
// current dimension of mat[][]
void getCof(vector<vector<int>>& mat, vector<vector<int>>& cof, 
                                        int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                cof[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Recursive function for finding determinant 
// of matrix mat of dimension n
int getDet(vector<vector<int>>& mat, int n) {
    if (n == 1) return mat[0][0];
    
    int det = 0;
  
    // To store cofactors
    vector<vector<int>> cof(mat.size(), vector<int>(mat.size()));
  
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCof(mat, cof, 0, f, n);
        det += sign * mat[0][f] * getDet(cof, n - 1);
        sign = -sign;
    }
    return det;
}

// Function to get adjoint of mat in adj
void adjoint(vector<vector<int>>& mat, vector<vector<int>>& adj) {
    int n = mat.size();
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }
    
    int sign = 1;
    vector<vector<int>> cof(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCof(mat, cof, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * getDet(cof, n - 1);
        }
    }
}

// Function to calculate and store inverse, returns 
// false if matrix is singular
bool inverse(vector<vector<int>>& mat, vector<vector<double>>& inv) {
    int n = mat.size();
    int det = getDet(mat, n);
    if (det == 0) {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }

    vector<vector<int>> adj(n, vector<int>(n));
    adjoint(mat, adj);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = adj[i][j] / double(det);

    return true;
}