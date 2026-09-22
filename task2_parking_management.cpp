#include <iostream>
using namespace std;

int main() {
    const int ROWS = 4;
    const int COLS = 5;

    // 1. Create and initialize the 2D parking array (0 = empty, 1 = occupied)
    int parking[ROWS][COLS] = {
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0}
    };

    // 2. Display the complete parking layout
    cout << "===== Parking Layout =====\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << parking[i][j] << " ";
        }
        cout << "\n";
    }

    // 3 & 4. Count occupied and empty spaces
    int occupied = 0, empty = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (parking[i][j] == 1) {
                occupied++;
            } else {
                empty++;
            }
        }
    }

    cout << "\nTotal Occupied Spaces: " << occupied << "\n";
    cout << "Total Empty Spaces: " << empty << "\n";

    // 5 & 6. Ask user for a row/column and check availability
    int row, col;
    cout << "\nEnter a row number (0 to " << ROWS - 1 << "): ";
    cin >> row;
    cout << "Enter a column number (0 to " << COLS - 1 << "): ";
    cin >> col;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (parking[row][col] == 0) {
            cout << "Parking space (" << row << ", " << col << ") is AVAILABLE.\n";
        } else {
            cout << "Parking space (" << row << ", " << col << ") is OCCUPIED.\n";
        }
    } else {
        cout << "Invalid row or column entered.\n";
    }

    // 7. Total capacity and current occupancy
    int totalCapacity = ROWS * COLS;
    cout << "\nTotal Parking Capacity: " << totalCapacity << "\n";
    cout << "Current Occupancy: " << occupied << " out of " << totalCapacity << "\n";

    return 0;
}