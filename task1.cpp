#include <iostream>
using namespace std;

int main() {
    const int STUDENTS = 6;
    const int SUBJECTS = 4;
    string subjectNames[SUBJECTS] = {"English", "Mathematics", "Programming", "AI"};

    // 1. Store the marks of all students in a 2D array
    int marks[STUDENTS][SUBJECTS] = {
        {78, 85, 90, 88},
        {65, 70, 60, 75},
        {92, 88, 95, 91},
        {55, 60, 58, 62},
        {80, 76, 82, 79},
        {70, 65, 72, 68}
    };

    // 2. Display the complete marks table
    cout << "===== Marks Table =====\n";
    cout << "Student\t";
    for (int j = 0; j < SUBJECTS; j++)
        cout << subjectNames[j] << "\t";
    cout << "\n";

    for (int i = 0; i < STUDENTS; i++) {
        cout << "S" << (i + 1) << "\t";
        for (int j = 0; j < SUBJECTS; j++) {
            cout << marks[i][j] << "\t";
        }
        cout << "\n";
    }

    // 3 & 4. Total and average marks of each student
    int totalMarks[STUDENTS];
    double averageMarks[STUDENTS];

    cout << "\n===== Totals and Averages =====\n";
    for (int i = 0; i < STUDENTS; i++) {
        int sum = 0;
        for (int j = 0; j < SUBJECTS; j++) {
            sum += marks[i][j];
        }
        totalMarks[i] = sum;
        averageMarks[i] = (double)sum / SUBJECTS;

        cout << "Student S" << (i + 1)
             << " -> Total: " << totalMarks[i]
             << ", Average: " << averageMarks[i] << "\n";
    }

    // 5. Highest marks in each subject
    cout << "\n===== Highest Marks Per Subject =====\n";
    for (int j = 0; j < SUBJECTS; j++) {
        int highest = marks[0][j];
        for (int i = 1; i < STUDENTS; i++) {
            if (marks[i][j] > highest) {
                highest = marks[i][j];
            }
        }
        cout << subjectNames[j] << ": " << highest << "\n";
    }

    // 6. Student with the highest total marks
    int topStudent = 0;
    for (int i = 1; i < STUDENTS; i++) {
        if (totalMarks[i] > totalMarks[topStudent]) {
            topStudent = i;
        }
    }
    cout << "\nStudent with the highest total marks: S" << (topStudent + 1)
         << " (Total: " << totalMarks[topStudent] << ")\n";

    return 0;
}