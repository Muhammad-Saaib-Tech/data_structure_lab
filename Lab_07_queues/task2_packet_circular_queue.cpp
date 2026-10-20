#include <iostream>
#include <limits>
using namespace std;

const int MAX_SIZE = 5;

class PacketQueue {
private:
    int packets[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    PacketQueue() : front(0), rear(-1), count(0) {}

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == MAX_SIZE; }

    void enqueue(int id) {
        if (isFull()) {
            cout << "Queue full: packet " << id << " dropped.\n";
            return;
        }
        rear = (rear + 1) % MAX_SIZE;
        packets[rear] = id;
        count++;
        cout << "Packet " << id << " stored at position " << rear << ".\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue empty: no packets to transmit.\n";
            return;
        }
        cout << "Transmitted packet " << packets[front]
             << " (position " << front << " is now free).\n";
        front = (front + 1) % MAX_SIZE;
        count--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No packets waiting.\n";
            return;
        }
        cout << "Packets waiting: ";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAX_SIZE;
            cout << packets[idx] << (i < count - 1 ? ", " : "");
        }
        cout << "\n";
    }
};

int main() {
    PacketQueue q;
    int choice, id;

    do {
        cout << "\n===== Network Packet Buffer =====\n"
             << "1. Insert packet\n"
             << "2. Transmit oldest packet\n"
             << "3. Display waiting packets\n"
             << "0. Exit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                cout << "Enter packet ID: ";
                if (cin >> id) {
                    q.enqueue(id);
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid packet ID.\n";
                }
                break;
            case 2: q.dequeue(); break;
            case 3: q.display(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
