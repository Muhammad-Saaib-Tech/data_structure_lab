// Task 1: University Staff Management System - Binary Tree and BST
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ============================================================
// PART A: General binary tree (names, no ordering rule)
// ============================================================
class Node {
public:
    string name;
    Node* left;
    Node* right;
    Node(const string& n) : name(n), left(nullptr), right(nullptr) {}
};

void displayGeneralTree(Node* root) {           // pre-order walk
    if (!root) return;
    cout << "  " << root->name
         << " | Left: "  << (root->left  ? root->left->name  : "NULL")
         << " | Right: " << (root->right ? root->right->name : "NULL") << "\n";
    displayGeneralTree(root->left);
    displayGeneralTree(root->right);
}

void inorderNames(Node* root) {
    if (!root) return;
    inorderNames(root->left);
    cout << root->name << "  ";
    inorderNames(root->right);
}

void freeGeneralTree(Node* root) {
    if (!root) return;
    freeGeneralTree(root->left);
    freeGeneralTree(root->right);
    delete root;
}

// ============================================================
// PART B: Binary Search Tree of unique staff IDs
// ============================================================
class BST {
private:
    struct BSTNode {
        int id;
        BSTNode* left;
        BSTNode* right;
        BSTNode(int v) : id(v), left(nullptr), right(nullptr) {}
    };
    BSTNode* root;

    BSTNode* insertNode(BSTNode* r, int id, bool& inserted) {
        if (!r) { inserted = true; return new BSTNode(id); }
        if (id < r->id)      r->left  = insertNode(r->left,  id, inserted);
        else if (id > r->id) r->right = insertNode(r->right, id, inserted);
        // equal -> duplicate, inserted stays false, tree untouched
        return r;
    }

    BSTNode* minNode(BSTNode* r) {
        while (r->left) r = r->left;
        return r;
    }

    // deleteCase: 0 = not found, 1 = leaf, 2 = one child, 3 = two children
    BSTNode* removeNode(BSTNode* r, int id, int& deleteCase) {
        if (!r) return nullptr;
        if (id < r->id)      r->left  = removeNode(r->left,  id, deleteCase);
        else if (id > r->id) r->right = removeNode(r->right, id, deleteCase);
        else {
            if (!r->left && !r->right) {            // Case 1: leaf
                deleteCase = 1;
                delete r;
                return nullptr;
            }
            if (!r->left) {                         // Case 2: only right child
                deleteCase = 2;
                BSTNode* child = r->right;
                delete r;
                return child;
            }
            if (!r->right) {                        // Case 2: only left child
                deleteCase = 2;
                BSTNode* child = r->left;
                delete r;
                return child;
            }
            deleteCase = 3;                         // Case 3: two children
            BSTNode* successor = minNode(r->right); // smallest in right subtree
            r->id = successor->id;                  // copy its value up
            int dummy = 0;
            r->right = removeNode(r->right, successor->id, dummy); // remove duplicate below
        }
        return r;
    }

    void inorder(BSTNode* r) const {
        if (!r) return;
        inorder(r->left);
        cout << r->id << " ";
        inorder(r->right);
    }

    BSTNode* copyTree(BSTNode* r) {
        if (!r) return nullptr;
        BSTNode* n = new BSTNode(r->id);
        n->left  = copyTree(r->left);
        n->right = copyTree(r->right);
        return n;
    }

    void destroy(BSTNode* r) {
        if (!r) return;
        destroy(r->left);
        destroy(r->right);
        delete r;
    }

public:
    BST() : root(nullptr) {}
    BST(const BST& other) : root(nullptr) { root = copyTree(other.root); } // fresh deep copy
    ~BST() { destroy(root); }

    bool insert(int id) {
        bool inserted = false;
        root = insertNode(root, id, inserted);
        return inserted;
    }

    // returns true if found; 'visits' = number of nodes examined
    bool search(int id, int& visits) const {
        visits = 0;
        BSTNode* cur = root;
        while (cur) {
            visits++;
            if (id == cur->id) return true;
            cur = (id < cur->id) ? cur->left : cur->right;
        }
        return false;
    }

    int remove(int id) {                            // returns the delete case
        int deleteCase = 0;
        root = removeNode(root, id, deleteCase);
        return deleteCase;
    }

    void displayInorder() const {
        if (!root) { cout << "(empty)"; return; }
        inorder(root);
    }
};

// ------------------------------------------------------------
// Helpers
// ------------------------------------------------------------
int readInt(const string& prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a whole number: ";
    }
    return x;
}

void runSearch(const BST& t, int id) {
    int visits = 0;
    bool found = t.search(id, visits);
    cout << "  Search " << id << ": " << (found ? "FOUND" : "NOT FOUND")
         << " | nodes visited = " << visits << "\n";
}

void describeDelete(int c, int id) {
    switch (c) {
        case 0: cout << "  ID " << id << " not found - nothing deleted.\n"; break;
        case 1: cout << "  ID " << id << " deleted (leaf node).\n"; break;
        case 2: cout << "  ID " << id << " deleted (node with ONE child).\n"; break;
        case 3: cout << "  ID " << id << " deleted (node with TWO children).\n"; break;
    }
}

// ------------------------------------------------------------
int main() {
    // ---------- Req 1 & 2: general binary tree ----------
    cout << "=== PART A: General Binary Tree ===\n";
    Node* gRoot = new Node("Dr. Ahmed");
    gRoot->left  = new Node("Prof. Sara");
    gRoot->right = new Node("Dr. Bilal");
    gRoot->left->left   = new Node("Mr. Ali");
    gRoot->left->right  = new Node("Ms. Hina");
    gRoot->right->left  = new Node("Mr. Usman");
    gRoot->right->right = new Node("Ms. Zainab");
    displayGeneralTree(gRoot);
    cout << "In-order of names: ";
    inorderNames(gRoot);
    cout << "\n(Not alphabetical - the tree has no ordering rule.)\n";
    freeGeneralTree(gRoot);

    // ---------- Req 3 & 4: BST with initial IDs ----------
    cout << "\n=== PART B: Binary Search Tree ===\n";
    BST staff;
    int initial[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : initial) staff.insert(id);
    cout << "Initial IDs (in-order): ";
    staff.displayInorder();
    cout << "\n";

    // ---------- Req 5: three user IDs, reject duplicates ----------
    cout << "\nEnter three additional staff IDs:\n";
    for (int i = 1; i <= 3; i++) {
        int id = readInt("  ID #" + to_string(i) + ": ");
        if (staff.insert(id)) cout << "  Inserted " << id << ".\n";
        else                  cout << "  REJECTED: " << id << " already exists (tree unchanged).\n";
    }
    cout << "Current IDs (in-order): ";
    staff.displayInorder();
    cout << "\n";

    // ---------- Req 6 & 7: search tests ----------
    cout << "\n--- Search tests ---\n";
    cout << "Existing ID:\n";
    runSearch(staff, 58);
    cout << "Missing ID (not in tree, within range):\n";
    runSearch(staff, 50);
    cout << "ID smaller than all registered IDs:\n";
    runSearch(staff, 5);

    int userSearch = readInt("\nEnter a staff ID to search: ");
    runSearch(staff, userSearch);

    // ---------- Req 8: delete user-entered ID ----------
    int userDelete = readInt("\nEnter a staff ID to delete: ");
    int c = staff.remove(userDelete);
    describeDelete(c, userDelete);
    cout << "IDs after deletion: ";
    staff.displayInorder();
    cout << "\n";

    // ---------- Req 8: each deletion case on a FRESH copy of the original BST ----------
    cout << "\n--- Deletion case tests (each on a fresh copy of the original BST) ---\n";
    BST original;
    for (int id : initial) original.insert(id);

    {   // Case 1: leaf
        BST t(original);
        cout << "Case 1 - leaf (delete 18):\n";
        describeDelete(t.remove(18), 18);
        cout << "  In-order: "; t.displayInorder(); cout << "\n";
    }
    {   // Case 2: one child (original has none, so add 98 under 78 first)
        BST t(original);
        t.insert(98);
        cout << "Case 2 - one child (added 98, so 78 has only a right child; delete 78):\n";
        describeDelete(t.remove(78), 78);
        cout << "  In-order: "; t.displayInorder(); cout << "\n";
    }
    {   // Case 3: two children
        BST t(original);
        cout << "Case 3 - two children (delete 28):\n";
        describeDelete(t.remove(28), 28);
        cout << "  In-order: "; t.displayInorder(); cout << "\n";
    }

    // ---------- Req 9: final in-order ----------
    cout << "\n--- Remaining staff IDs (ascending, from the user's tree) ---\n";
    staff.displayInorder();
    cout << "\n";

    // ---------- Req 10: explanation ----------
    cout << "\n--- Why in-order is sorted for a BST but not a general tree ---\n"
         << "In a BST every left subtree holds smaller values and every right subtree\n"
         << "holds larger values. In-order visits left, then node, then right, so it\n"
         << "always emits smaller values first - the output is sorted. A general binary\n"
         << "tree has no such rule: children can be placed anywhere, so in-order just\n"
         << "follows the shape of the tree and the values come out in arbitrary order.\n";

    return 0;   // BST destructors free all nodes automatically
}
