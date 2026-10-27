// Task 2: Hospital and Emergency Inventory Management System - Complete BST Application
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class BST {
private:
    struct Node {
        int id;
        Node* left;
        Node* right;
        Node(int v) : id(v), left(nullptr), right(nullptr) {}
    };
    Node* root;

    // ---- helpers (all dynamic nodes are created with new, freed with delete) ----
    Node* insertNode(Node* r, int id, bool& inserted) {
        if (!r) { inserted = true; return new Node(id); }
        if (id < r->id)      r->left  = insertNode(r->left,  id, inserted);
        else if (id > r->id) r->right = insertNode(r->right, id, inserted);
        return r;                       // duplicate: nothing changes
    }

    bool searchNode(Node* r, int id) const {
        if (!r) return false;
        if (id == r->id) return true;
        return (id < r->id) ? searchNode(r->left, id) : searchNode(r->right, id);
    }

    Node* minNode(Node* r) const {
        while (r->left) r = r->left;
        return r;
    }

    // deleteCase: 0 = not found, 1 = leaf, 2 = one child, 3 = two children
    Node* deleteNode(Node* r, int id, int& deleteCase) {
        if (!r) return nullptr;
        if (id < r->id)      r->left  = deleteNode(r->left,  id, deleteCase);
        else if (id > r->id) r->right = deleteNode(r->right, id, deleteCase);
        else {
            if (!r->left && !r->right) {                 // leaf
                deleteCase = 1;
                delete r;
                return nullptr;
            }
            if (!r->left) {                              // one child (right)
                deleteCase = 2;
                Node* child = r->right;
                delete r;
                return child;
            }
            if (!r->right) {                             // one child (left)
                deleteCase = 2;
                Node* child = r->left;
                delete r;
                return child;
            }
            deleteCase = 3;                              // two children
            Node* successor = minNode(r->right);         // in-order successor
            r->id = successor->id;                       // copy its value up
            int dummy = 0;
            r->right = deleteNode(r->right, successor->id, dummy);
        }
        return r;
    }

    void inorder(Node* r) const   { if (!r) return; inorder(r->left);  cout << r->id << " "; inorder(r->right); }
    void preorder(Node* r) const  { if (!r) return; cout << r->id << " "; preorder(r->left); preorder(r->right); }
    void postorder(Node* r) const { if (!r) return; postorder(r->left); postorder(r->right); cout << r->id << " "; }

    void collect(Node* r, vector<int>& out) const {
        if (!r) return;
        collect(r->left, out);
        out.push_back(r->id);
        collect(r->right, out);
    }

    int countNodes(Node* r) const  { return r ? 1 + countNodes(r->left) + countNodes(r->right) : 0; }
    int heightNode(Node* r) const  {                      // height in levels (empty = 0)
        if (!r) return 0;
        int l = heightNode(r->left), rt = heightNode(r->right);
        return 1 + (l > rt ? l : rt);
    }

    void destroy(Node* r) {
        if (!r) return;
        destroy(r->left);
        destroy(r->right);
        delete r;
    }

public:
    BST() : root(nullptr) {}
    BST(const BST&) = delete;                // not needed here; avoids accidental shallow copies
    BST& operator=(const BST&) = delete;
    ~BST() { destroy(root); }                // releases every dynamically allocated node

    bool isEmpty() const { return root == nullptr; }

    // ---- separate member functions required by the task ----
    bool insert(int id) {
        bool inserted = false;
        root = insertNode(root, id, inserted);
        return inserted;
    }
    bool search(int id) const { return searchNode(root, id); }
    int  remove(int id) {
        int c = 0;
        root = deleteNode(root, id, c);
        return c;
    }
    void displayInorder() const   { if (isEmpty()) cout << "(tree is empty)"; else inorder(root); }
    void displayPreorder() const  { if (isEmpty()) cout << "(tree is empty)"; else preorder(root); }
    void displayPostorder() const { if (isEmpty()) cout << "(tree is empty)"; else postorder(root); }
    int  count() const  { return countNodes(root); }
    int  height() const { return heightNode(root); }
    vector<int> toVector() const { vector<int> v; collect(root, v); return v; }
};

// ------------------------------------------------------------
// Input helpers
// ------------------------------------------------------------
bool readInt(int& x) {
    if (cin >> x) return true;
    if (cin.eof()) return false;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    x = -1;                                   // signals invalid input to the caller
    return true;
}

int askId(const char* prompt) {
    int id;
    while (true) {
        cout << prompt;
        if (!readInt(id)) exit(0);
        if (id > 0) return id;
        cout << "Invalid ID. Please enter a positive whole number.\n";
    }
}

void reportDelete(BST& t, int id) {
    if (t.isEmpty()) { cout << "Cannot delete: the tree is empty.\n"; return; }
    int c = t.remove(id);
    switch (c) {
        case 0: cout << "ID " << id << " does not exist - nothing deleted.\n"; return;
        case 1: cout << "ID " << id << " deleted (leaf node).\n"; break;
        case 2: cout << "ID " << id << " deleted (node with one child).\n"; break;
        case 3: cout << "ID " << id << " deleted (node with two children).\n"; break;
    }
    cout << "Updated IDs (in-order): ";
    t.displayInorder();
    cout << "\n";
}

void printVec(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << " ";
}

// ------------------------------------------------------------
// Predict-then-compare demo + repeated-deletion test
// NOTE: the instructor's real sequence was not given, so this uses a SAMPLE
// sequence. Replace the ops below with the instructor's sequence and update
// the predicted values (worked out by hand BEFORE running).
// ------------------------------------------------------------
void runPredictionDemo() {
    cout << "==================== PREDICTION DEMO ====================\n";
    cout << "Sample sequence: insert 60, insert 30, delete 35, delete 85, delete 55\n";

    // Hand-worked predictions (made before running):
    vector<int> predicted = {25, 30, 40, 45, 50, 60, 65, 75};
    int predictedHeight = 4;
    cout << "Predicted in-order: "; printVec(predicted);
    cout << "\nPredicted height  : " << predictedHeight << " (levels)\n";

    BST t;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initial) t.insert(id);
    t.insert(60);
    t.insert(30);
    t.remove(35);       // two children -> replaced by successor 40
    t.remove(85);       // leaf
    t.remove(55);       // root, two children -> replaced by successor 60

    vector<int> actual = t.toVector();
    cout << "Actual in-order   : "; printVec(actual);
    cout << "\nActual height     : " << t.height() << " (levels)\n";
    bool match = (actual == predicted) && (t.height() == predictedHeight);
    cout << "Result: " << (match ? "predictions MATCH the actual output." : "MISMATCH - re-check the hand trace.") << "\n";

    cout << "\n--- Repeated deletion of the same ID (delete 85 again) ---\n";
    int c = t.remove(85);
    cout << "Second delete of 85 -> " << (c == 0 ? "reported 'not found'; tree unchanged." : "unexpected!") << "\n";
    cout << "In-order after repeat: "; t.displayInorder(); cout << "\n";
    cout << "Explanation: once a node is deleted it no longer exists in the tree, so the\n"
         << "search for it ends at a NULL pointer. The function returns 'not found' and\n"
         << "changes nothing - no crash, no extra deletion.\n";

    cout << "\n--- How the BST property survives deleting a node with two children ---\n"
         << "Every value in the left subtree is smaller and every value in the right\n"
         << "subtree is larger. The in-order successor (smallest value of the right\n"
         << "subtree) is larger than everything on the left and no larger than anything\n"
         << "else on the right. Copying it into the deleted node's place keeps both\n"
         << "sides valid; the successor's old node (a leaf or one-child node) is then\n"
         << "removed with the simple cases.\n";
    cout << "=========================================================\n\n";
}

// ------------------------------------------------------------
int main() {
    runPredictionDemo();

    BST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initial) tree.insert(id);

    int choice = 0;
    do {
        cout << "\n===== Hospital & Emergency Inventory Menu =====\n"
             << "1. Insert an ID\n"
             << "2. Search for an ID\n"
             << "3. Delete an ID\n"
             << "4. Display in-order traversal\n"
             << "5. Display pre-order traversal\n"
             << "6. Display post-order traversal\n"
             << "7. Count the total number of nodes\n"
             << "8. Calculate the height of the BST\n"
             << "9. Exit\n"
             << "Enter choice (1-9): ";
        if (!readInt(choice)) break;

        switch (choice) {
            case 1: {
                int id = askId("Enter ID to insert: ");
                if (tree.insert(id)) cout << "ID " << id << " inserted.\n";
                else                 cout << "ID " << id << " already exists - rejected, tree unchanged.\n";
                break;
            }
            case 2: {
                if (tree.isEmpty()) { cout << "The tree is empty - nothing to search.\n"; break; }
                int id = askId("Enter ID to search: ");
                cout << "ID " << id << (tree.search(id) ? " FOUND.\n" : " NOT FOUND.\n");
                break;
            }
            case 3: {
                if (tree.isEmpty()) { cout << "The tree is empty - nothing to delete.\n"; break; }
                int id = askId("Enter ID to delete: ");
                reportDelete(tree, id);
                break;
            }
            case 4: cout << "In-order  : "; tree.displayInorder();   cout << "\n"; break;
            case 5: cout << "Pre-order : "; tree.displayPreorder();  cout << "\n"; break;
            case 6: cout << "Post-order: "; tree.displayPostorder(); cout << "\n"; break;
            case 7: cout << "Total nodes: " << tree.count() << "\n"; break;
            case 8: cout << "Height of BST: " << tree.height() << " level(s)"
                         << (tree.isEmpty() ? " (empty tree)" : "") << "\n"; break;
            case 9: cout << "Exiting. All nodes will be released.\n"; break;
            default: cout << "Invalid choice. Please enter a number from 1 to 9.\n";
        }
    } while (choice != 9);

    return 0;                                  // ~BST() frees every node
}
