// Lab 05 - Task 3: Game Player Turns (Circular Singly Linked List)
#include <iostream>
#include <string>
using namespace std;

// One player
class Node {
public:
    string playerName;
    Node* next;   // next player in turn order

    Node(const string& name) : playerName(name), next(NULL) {}
};

class GameTurns {
private:
    Node* head;   // first player
    Node* tail;   // last player (tail->next points back to head)

public:
    GameTurns() : head(NULL), tail(NULL) {}

    ~GameTurns() {
        if (head == NULL) return;
        tail->next = NULL;          // break the circle before deleting
        Node* cur = head;
        while (cur != NULL) {
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
    }

    void addPlayer(const string& name) {
        Node* n = new Node(name);
        if (head == NULL) {
            head = tail = n;
            tail->next = head;      // single node points to itself
        } else {
            tail->next = n;
            tail = n;
            tail->next = head;      // close the circle
        }
    }

    // Each player gets exactly one turn
    void displayTurns() const {
        cout << "Turn order (each player once):" << endl;
        Node* cur = head;
        int turn = 1;
        do {
            cout << "  Turn " << turn++ << ": " << cur->playerName << endl;
            cur = cur->next;
        } while (cur != head);
    }

    // Shows that after the last player the turn goes back to the first
    void showWrapAround() const {
        cout << "Wrap-around check:" << endl;
        cout << "  Last player  : " << tail->playerName << endl;
        cout << "  Next turn    : " << tail->next->playerName
             << "   (back to the first player)" << endl;
    }
};

int main() {
    GameTurns game;

    game.addPlayer("Ali");
    game.addPlayer("Sara");
    game.addPlayer("Ahmed");
    game.addPlayer("Fatima");
    game.addPlayer("Usman");

    game.displayTurns();
    cout << endl;
    game.showWrapAround();

    return 0;
}
