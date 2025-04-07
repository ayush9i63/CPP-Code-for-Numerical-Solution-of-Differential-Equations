#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

// Boundary conditions
double u_x0(double y) {
    return 0;
}

double u_xn(double y) {
    return 1;
}

double u_y0(double x) {
    return 0;
}

double u_yn(double x) {
    return 0;
}

int main(){
    // Initialize grid boundaries and step sizes
    double x0 = 0, xn = 3, y0 = 0, yn = 3, h = 1, k = 1;
    
    // Calculate grid dimensions
    int n = (xn - x0) / h + 1;
    int l = (yn - y0) / k + 1;
    
    // Create and initialize solution grid
    double u[n][l];
    
    // Initialize grid with boundary conditions
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < l; j++) {
            u[i][j] = 0;
        }
    }

    // Boundary conditions for u_x0 and u_xn
    for(int i = 0; i < l; i++) {
        u[0][i] = u_x0(y0 + i * k);
        u[n - 1][i] = u_xn(y0 + i * k);
    }
    
    // Boundary conditions for u_y0 and u_yn
    for(int i = 0; i < n; i++) {
        u[i][0] = u_y0(x0 + i * h);
        u[i][l - 1] = u_yn(x0 + i * h);
    }
    
    // Initialize temporary grid for Jacobi iteration
    double temp[n][l];
    double diff = 1, max_diff = -1;
    
    // Copy the initial values of u to temp
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < l; j++) {
            temp[i][j] = u[i][j];
        }
    }

    int q = 1;
    cout << "The iterations with respect to Jacobi's Iterations are as follows: " << endl;
    
    // Jacobi iteration
    while(diff > 0.001) {
        cout << "Iteration " << q++ << ": ";
        max_diff = -1;
        
        // Copy current values to temp and perform the Jacobi update
        for(int i = 1; i < n - 1; i++) {
            for(int j = 1; j < l - 1; j++) {
                temp[i][j] = u[i][j]; // Store old value
                u[i][j] = 0.25 * (u[i][j + 1] + u[i - 1][j] + u[i][j - 1] + u[i + 1][j]);
                cout << setw(10) << u[i][j];
                
                // Calculate the maximum difference between old and new values
                double current_diff = abs(u[i][j] - temp[i][j]);
                if(current_diff > max_diff) {
                    max_diff = current_diff;
                }
            }
        }
        
        // Update the diff for convergence check
        diff = max_diff;
        cout << endl;
    }

    cout << endl;
    
    // Print the final solution grid
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < l; j++) {
            cout << setw(15) << u[i][j];
        }
        cout << endl;
    }

    return 0;
}
