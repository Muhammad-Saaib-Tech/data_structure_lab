#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_SIZE = 10;

struct Patient {
    string id;
    int priority;
};

class EmergencyQueue {
private:
    Patient patients[MAX_SIZE];
    int size;

public:
    EmergencyQueue() : size(0) {}

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == MAX_SIZE; }

    void insertPatient(const string& id, int priority) {
        if (isFull()) {
            cout << "Queue full: cannot admit patient " << id << ".\n";
            return;
        }
        int i = size - 1;
        while (i >= 0 && patients[i].priority > priority) {
            patients[i + 1] = patients[i];
            i--;
        }
        patients[i + 1] = {id, priority};
        size++;
        cout << "Patient " << id << " added with priority " << priority << ".\n";
    }

    void treatNext() {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Treating patient " << patients[0].id
             << " (priority " << patients[0].priority << ").\n";
        for (int i = 1; i < size; i++) {
            patients[i - 1] = patients[i];
        }
        size--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Waiting patients (most urgent first):\n";
        for (int i = 0; i < size; i++) {
            cout << "  " << (i + 1) << ". " << patients[i].id
                 << "  - priority " << patients[i].priority << "\n";
        }
    }
};

int main() {
    EmergencyQueue er;
    int choice, priority;
    string id;

    do {
        cout << "\n===== Emergency Department =====\n"
             << "(Priority 1 = highest urgency)\n"
             << "1. Add patient\n"
             << "2. Treat next patient\n"
             << "3. Display waiting patients\n"
             << "0. Exit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                cout << "Enter patient ID (e.g. P102): ";
                cin >> id;
                cout << "Enter priority (1 = highest): ";
                if (cin >> priority && priority >= 1) {
                    er.insertPatient(id, priority);
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid priority. Use a whole number of 1 or more.\n";
                }
                break;
            case 2: er.treatNext(); break;
            case 3: er.display(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
