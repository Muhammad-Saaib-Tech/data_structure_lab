#include <iostream>
#include <limits>
using namespace std;

const int MAX_SIZE = 5;

class PassengerDeque {
private:
    int requests[MAX_SIZE];
    int front;
    int count;

    int rearIndex() const { return (front + count - 1) % MAX_SIZE; }

public:
    PassengerDeque() : front(0), count(0) {}

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == MAX_SIZE; }

    void insertFront(int id) {
        if (isFull()) {
            cout << "Deque full: cannot insert " << id << ".\n";
            return;
        }
        front = (front - 1 + MAX_SIZE) % MAX_SIZE;
        requests[front] = id;
        count++;
        cout << "Request " << id << " inserted at the front.\n";
    }

    void insertRear(int id) {
        if (isFull()) {
            cout << "Deque full: cannot insert " << id << ".\n";
            return;
        }
        requests[(front + count) % MAX_SIZE] = id;
        count++;
        cout << "Request " << id << " inserted at the rear.\n";
    }

    void removeFront() {
        if (isEmpty()) {
            cout << "Deque empty: nothing to remove.\n";
            return;
        }
        cout << "Removed request " << requests[front] << " from the front.\n";
        front = (front + 1) % MAX_SIZE;
        count--;
    }

    void removeRear() {
        if (isEmpty()) {
            cout << "Deque empty: nothing to remove.\n";
            return;
        }
        cout << "Removed request " << requests[rearIndex()] << " from the rear.\n";
        count--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No requests in the deque.\n";
            return;
        }
        cout << "Front -> ";
        for (int i = 0; i < count; i++) {
            cout << requests[(front + i) % MAX_SIZE] << (i < count - 1 ? ", " : "");
        }
        cout << " <- Rear\n";
    }
};

int main() {
    PassengerDeque d;
    int choice, id;

    do {
        cout << "\n===== Train Station Requests =====\n"
             << "1. Insert at front\n"
             << "2. Insert at rear\n"
             << "3. Remove from front\n"
             << "4. Remove from rear\n"
             << "5. Display (front to rear)\n"
             << "0. Exit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
            case 2:
                cout << "Enter passenger request ID: ";
                if (cin >> id) {
                    if (choice == 1) d.insertFront(id); else d.insertRear(id);
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid ID.\n";
                }
                break;
            case 3: d.removeFront(); break;
            case 4: d.removeRear(); break;
            case 5: d.display(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
