#include <iostream>
using namespace std;

int main() {
    const int SIZE = 3;

    int A[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int B[SIZE][SIZE] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int sum[SIZE][SIZE];

    // Display Matrix A
    cout << "Matrix A:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }

    // Display Matrix B
    cout << "Matrix B:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }

    // Calculate the sum
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum[i][j] = A[i][j] + B[i][j];
        }
    }

    // Display the sum
    cout << "\nSum of Matrix A and B:\n\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << sum[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}