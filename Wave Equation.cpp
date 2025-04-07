#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

const int MAX_SIZE = 100;

double P(double t) {
    return 0;  // Boundary condition at x=0
}

double Q(double t) {
    return 0;  // Boundary condition at x=l
}

double f(double x){
    return 100*(x - x*x);  // Initial condition function
}

double g(double x){
    return 0;  // Initial velocity (set to 0)
}

int main() {
    int n, m;
    double h, k, c, l;

    cout << "We are solving the Wave Equation Utt = c^2Uxx using finite difference scheme!" << endl;
    cout << "Enter the value of space step h, time step k, and value of c^2: ";
    cin >> h >> k >> c;
    cout << "Enter the length of the rod (l): ";
    cin >> l;

    // Total time duration is implicitly handled by the number of time steps.
    // double T;
    // cout << "Enter the total time duration T: ";
    // cin >> T;

    // Calculate the number of spatial and time steps
    n = l / h;  // Number of spatial steps
    m = 1.0 / k;  // Number of time steps

    double u[MAX_SIZE][MAX_SIZE] = {0};
    double lambda = (c * k / h) * (c * k / h);  // Wave equation coefficient

    // Initialize u[i][0] (initial displacement) based on f(x)
    for (int i = 0; i <= n; i++) {
        double x = i * h;
        u[i][0] = f(x);
    }

    // Set boundary conditions u[0][j] and u[n][j] for all time steps
    for (int j = 0; j <= m; j++) {
        double t = j * k;  // t represents the current time step
        u[0][j] = P(t);
        u[n][j] = Q(t);
    }

    // Initial velocity condition (u_i1 = g(x), for all i)
    for (int i = 1; i < n; i++) {
        u[i][1] = (1 - lambda) * u[i][0] + (lambda / 2) * (u[i + 1][0] + u[i - 1][0]);
    }

    // Use the finite difference method for time-stepping
    for (int j = 1; j < m; j++) {
        for (int i = 1; i < n; i++) {
            u[i][j + 1] = 2 * (1 - lambda) * u[i][j] + lambda * (u[i + 1][j] + u[i - 1][j]) - u[i][j - 1];
        }
    }

    // Print the computed values starting from time step j = 1
    cout << fixed << setprecision(4);
    cout << "Computed Values: " << endl;
    for (int j = 1; j <= m; j++) {  // Start from j = 1 to avoid printing the first line
        for (int i = 0; i <= n; i++) {
            cout << u[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
