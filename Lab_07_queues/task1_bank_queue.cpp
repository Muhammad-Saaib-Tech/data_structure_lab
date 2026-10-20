#include <iostream>
#include <limits>
using namespace std;

const int MAX_SIZE = 5;

class BankQueue {
private:
    int tokens[MAX_SIZE];
    int front;
    int rear;

public:
    BankQueue() : front(-1), rear(-1) {}

    bool isEmpty() const {
        return front == -1 || front > rear;
    }

    bool isFull() const {
        return rear == MAX_SIZE - 1;
    }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Overflow: queue is full. Token " << token
                 << " cannot join the line.\n";
            return;
        }
        if (front == -1) front = 0;
        tokens[++rear] = token;
        cout << "Customer " << token << " joined the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow: no customers are waiting.\n";
            return;
        }
        cout << "Now serving customer " << tokens[front] << ".\n";
        front++;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No customers are waiting.\n";
            return;
        }
        cout << "Waiting customers (next to be served first): ";
        for (int i = front; i <= rear; i++) {
            cout << tokens[i] << (i < rear ? ", " : "");
        }
        cout << "\n";
    }

    int count() const {
        return isEmpty() ? 0 : (rear - front + 1);
    }
};

int main() {
    BankQueue bank;
    int choice, token;

    do {
        cout << "\n===== Bank Customer Service =====\n"
             << "1. Add customer (enqueue)\n"
             << "2. Serve next customer (dequeue)\n"
             << "3. Display waiting customers\n"
             << "4. Show number of waiting customers\n"
             << "0. Exit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                cout << "Enter token number: ";
                if (cin >> token) {
                    bank.enqueue(token);
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid token.\n";
                }
                break;
            case 2: bank.dequeue(); break;
            case 3: bank.display(); break;
            case 4: cout << "Customers waiting: " << bank.count() << "\n"; break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
