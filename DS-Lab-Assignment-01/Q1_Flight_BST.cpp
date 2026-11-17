#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Node {
public:
    int flightNumber;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int fn, const string& dest, const string& time)
        : flightNumber(fn), destination(dest), departureTime(time),
          left(nullptr), right(nullptr) {}
};

class FlightBST {
private:
    Node* root;

    Node* insert(Node* node, int fn, const string& dest, const string& time, bool& ok) {
        if (node == nullptr) {
            ok = true;
            return new Node(fn, dest, time);
        }
        if (fn < node->flightNumber)
            node->left = insert(node->left, fn, dest, time, ok);
        else if (fn > node->flightNumber)
            node->right = insert(node->right, fn, dest, time, ok);
        else
            ok = false;
        return node;
    }

    Node* search(Node* node, int fn) const {
        if (node == nullptr || node->flightNumber == fn) return node;
        if (fn < node->flightNumber) return search(node->left, fn);
        return search(node->right, fn);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* findMax(Node* node) const {
        while (node && node->right) node = node->right;
        return node;
    }

    Node* remove(Node* node, int fn, bool& deleted) {
        if (node == nullptr) return nullptr;

        if (fn < node->flightNumber) {
            node->left = remove(node->left, fn, deleted);
        } else if (fn > node->flightNumber) {
            node->right = remove(node->right, fn, deleted);
        } else {
            deleted = true;

            if (node->left == nullptr && node->right == nullptr) {
                cout << "[Case 1: leaf node] ";
                delete node;
                return nullptr;
            }

            if (node->left == nullptr) {
                cout << "[Case 2: one child (right)] ";
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                cout << "[Case 2: one child (left)] ";
                Node* temp = node->left;
                delete node;
                return temp;
            }

            cout << "[Case 3: two children, replaced by in-order successor] ";
            Node* succ = findMin(node->right);
            node->flightNumber = succ->flightNumber;
            node->destination = succ->destination;
            node->departureTime = succ->departureTime;
            bool dummy = false;
            node->right = remove(node->right, succ->flightNumber, dummy);
        }
        return node;
    }

    void printNode(Node* n) const {
        cout << "Flight " << n->flightNumber << " | " << left << setw(13)
             << n->destination << right << " | " << n->departureTime << "\n";
    }

    void inorder(Node* n) const {
        if (!n) return;
        inorder(n->left);
        printNode(n);
        inorder(n->right);
    }

    void preorder(Node* n) const {
        if (!n) return;
        printNode(n);
        preorder(n->left);
        preorder(n->right);
    }

    void postorder(Node* n) const {
        if (!n) return;
        postorder(n->left);
        postorder(n->right);
        printNode(n);
    }

    int count(Node* n) const {
        if (!n) return 0;
        return 1 + count(n->left) + count(n->right);
    }

    int height(Node* n) const {
        if (!n) return 0;
        int lh = height(n->left), rh = height(n->right);
        return 1 + (lh > rh ? lh : rh);
    }

    void printTree(Node* n, int depth) const {
        if (!n) return;
        printTree(n->right, depth + 1);
        cout << string(depth * 8, ' ') << n->flightNumber
             << " (" << n->destination << ")\n";
        printTree(n->left, depth + 1);
    }

    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    FlightBST() : root(nullptr) {}
    ~FlightBST() { destroy(root); }

    void insert(int fn, const string& dest, const string& time) {
        bool ok = false;
        root = insert(root, fn, dest, time, ok);
        if (!ok) cout << "Flight " << fn << " already exists - not inserted.\n";
    }

    void search(int fn) const {
        Node* r = search(root, fn);
        if (r) {
            cout << "FOUND -> ";
            printNode(r);
        } else {
            cout << "Flight " << fn << " NOT FOUND.\n";
        }
    }

    void remove(int fn) {
        bool deleted = false;
        cout << "Deleting flight " << fn << ": ";
        root = remove(root, fn, deleted);
        if (deleted) cout << "deleted.\n";
        else cout << "flight not found.\n";
    }

    void displayInorder() const   { cout << "--- In-order ---\n";   inorder(root); }
    void displayPreorder() const  { cout << "--- Pre-order ---\n";  preorder(root); }
    void displayPostorder() const { cout << "--- Post-order ---\n"; postorder(root); }

    void displayMinMax() const {
        Node* mn = findMin(root);
        Node* mx = findMax(root);
        if (!mn) { cout << "Tree is empty.\n"; return; }
        cout << "Minimum flight number: " << mn->flightNumber << " (" << mn->destination << ")\n";
        cout << "Maximum flight number: " << mx->flightNumber << " (" << mx->destination << ")\n";
    }

    int countFlights() const { return count(root); }
    int getHeight() const    { return height(root); }

    void displayStructure() const {
        cout << "(Tree is rotated 90 degrees: root on the left, right children above, left children below)\n";
        if (!root) cout << "Tree is empty.\n";
        else printTree(root, 0);
    }
};

int main() {
    FlightBST tree;

    cout << "===== INSERTING 12 FLIGHT RECORDS =====\n";
    tree.insert(500, "Dubai",      "08:00");
    tree.insert(300, "London",     "09:30");
    tree.insert(700, "Istanbul",   "11:15");
    tree.insert(200, "Doha",       "06:45");
    tree.insert(400, "Riyadh",     "13:00");
    tree.insert(600, "Toronto",    "14:20");
    tree.insert(800, "Karachi",    "15:50");
    tree.insert(100, "Jeddah",     "05:30");
    tree.insert(250, "Muscat",     "07:10");
    tree.insert(350, "Kuala Lumpur","16:40");
    tree.insert(450, "Paris",      "18:25");
    tree.insert(900, "New York",   "21:00");

    cout << "\n===== INITIAL BST STRUCTURE =====\n";
    tree.displayStructure();

    cout << "\n===== TRAVERSALS =====\n";
    tree.displayInorder();
    cout << "\n"; tree.displayPreorder();
    cout << "\n"; tree.displayPostorder();

    cout << "\n===== SEARCH =====\n";
    tree.search(350);
    tree.search(999);

    cout << "\n===== MIN / MAX =====\n";
    tree.displayMinMax();
    cout << "\n===== TOTAL FLIGHTS & HEIGHT =====\n";
    cout << "Total flights: " << tree.countFlights() << "\n";
    cout << "Height of tree (in levels): " << tree.getHeight() << "\n";

    cout << "\n===== DELETION =====\n";
    tree.remove(100);
    tree.remove(200);
    tree.remove(300);
    tree.remove(999);

    cout << "\n===== FINAL BST STRUCTURE =====\n";
    tree.displayStructure();
    cout << "\n"; tree.displayInorder();
    cout << "\n===== FINAL STATISTICS =====\n";
    tree.displayMinMax();
    cout << "Total flights: " << tree.countFlights() << "\n";
    cout << "Height of tree (in levels): " << tree.getHeight() << "\n";

    return 0;
}
