// Lab 05 - Task 1: Browser History (Doubly Linked List)
#include <iostream>
#include <string>
using namespace std;

// One visited website
class Node {
public:
    string website;
    Node* prev;   // the site visited before this one
    Node* next;   // the site visited after this one

    Node(const string& site) : website(site), prev(NULL), next(NULL) {}
};

class BrowserHistory {
private:
    Node* head;   // first visited
    Node* tail;   // last visited

public:
    BrowserHistory() : head(NULL), tail(NULL) {}

    ~BrowserHistory() {
        Node* cur = head;
        while (cur != NULL) {
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
    }

    // Add a new website at the end of the history
    void visit(const string& site) {
        Node* n = new Node(site);
        if (head == NULL) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    // First visited -> last visited (follows next pointers)
    void displayForward() const {
        cout << "History (first visited -> last visited):" << endl;
        Node* cur = head;
        int i = 1;
        while (cur != NULL) {
            cout << "  " << i++ << ". " << cur->website << endl;
            cur = cur->next;
        }
    }

    // Last visited -> first visited (follows prev pointers)
    void displayReverse() const {
        cout << "History (last visited -> first visited):" << endl;
        Node* cur = tail;
        int i = 1;
        while (cur != NULL) {
            cout << "  " << i++ << ". " << cur->website << endl;
            cur = cur->prev;
        }
    }

    // Demonstrates navigating with prev (Back) and next (Forward)
    void navigateDemo() const {
        cout << "Navigation demo (starting at the last page):" << endl;
        Node* cur = tail;
        cout << "  Current page : " << cur->website << endl;
        cur = cur->prev;
        cout << "  Back         : " << cur->website << endl;
        cur = cur->prev;
        cout << "  Back         : " << cur->website << endl;
        cur = cur->next;
        cout << "  Forward      : " << cur->website << endl;
    }
};

int main() {
    BrowserHistory history;

    history.visit("www.google.com");
    history.visit("www.github.com");
    history.visit("www.stackoverflow.com");
    history.visit("www.youtube.com");
    history.visit("www.wikipedia.org");

    history.displayForward();
    cout << endl;
    history.displayReverse();
    cout << endl;
    history.navigateDemo();

    return 0;
}
