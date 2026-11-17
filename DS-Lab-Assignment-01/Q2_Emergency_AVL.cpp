#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
using namespace std;

class Node {
public:
    int emergencyId;
    string location;
    int severity;
    int height;
    Node* left;
    Node* right;

    Node(int id, const string& loc, int sev)
        : emergencyId(id), location(loc), severity(sev),
          height(1), left(nullptr), right(nullptr) {}
};

class EmergencyAVL {
private:
    Node* root;

    int height(Node* n) const { return n ? n->height : 0; }

    int balanceFactor(Node* n) const {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        int lh = height(n->left), rh = height(n->right);
        n->height = 1 + (lh > rh ? lh : rh);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* B = x->right;
        x->right = y;
        y->left = B;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* B = y->left;
        y->left = x;
        x->right = B;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* rebalance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) >= 0) {
                cout << "   [Rotation LL at node " << node->emergencyId << " -> Right Rotation]\n";
                return rotateRight(node);
            } else {
                cout << "   [Rotation LR at node " << node->emergencyId
                     << " -> Left Rotation on " << node->left->emergencyId
                     << ", then Right Rotation]\n";
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (bf < -1) {
            if (balanceFactor(node->right) <= 0) {
                cout << "   [Rotation RR at node " << node->emergencyId << " -> Left Rotation]\n";
                return rotateLeft(node);
            } else {
                cout << "   [Rotation RL at node " << node->emergencyId
                     << " -> Right Rotation on " << node->right->emergencyId
                     << ", then Left Rotation]\n";
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    Node* insert(Node* node, int id, const string& loc, int sev, bool& ok) {
        if (!node) {
            ok = true;
            return new Node(id, loc, sev);
        }
        if (id < node->emergencyId)
            node->left = insert(node->left, id, loc, sev, ok);
        else if (id > node->emergencyId)
            node->right = insert(node->right, id, loc, sev, ok);
        else {
            ok = false;
            return node;
        }
        return rebalance(node);
    }

    Node* findMin(Node* n) const {
        while (n && n->left) n = n->left;
        return n;
    }

    Node* remove(Node* node, int id, bool& deleted) {
        if (!node) return nullptr;

        if (id < node->emergencyId) {
            node->left = remove(node->left, id, deleted);
        } else if (id > node->emergencyId) {
            node->right = remove(node->right, id, deleted);
        } else {
            deleted = true;
            if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }

            Node* succ = findMin(node->right);
            node->emergencyId = succ->emergencyId;
            node->location = succ->location;
            node->severity = succ->severity;
            bool dummy = false;
            node->right = remove(node->right, succ->emergencyId, dummy);
        }
        return rebalance(node);
    }

    Node* search(Node* node, int id) const {
        if (!node || node->emergencyId == id) return node;
        return id < node->emergencyId ? search(node->left, id) : search(node->right, id);
    }

    void inorder(Node* n) const {
        if (!n) return;
        inorder(n->left);
        printRecord(n);
        inorder(n->right);
    }

    void printRecord(Node* n) const {
        cout << "ID " << setw(3) << n->emergencyId << " | " << left << setw(16)
             << n->location << right << " | Severity " << setw(2) << n->severity
             << " | Height " << n->height << " | BF " << balanceFactor(n) << "\n";
    }

    void printTree(Node* n, int depth) const {
        if (!n) return;
        printTree(n->right, depth + 1);
        cout << string(depth * 8, ' ') << n->emergencyId
             << " [h=" << n->height << ", bf=" << balanceFactor(n) << "]\n";
        printTree(n->left, depth + 1);
    }

    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    EmergencyAVL() : root(nullptr) {}
    ~EmergencyAVL() { destroy(root); }

    void insert(int id, const string& loc, int sev) {
        cout << "Inserting ID " << id << " (" << loc << ", severity " << sev << ")\n";
        bool ok = false;
        root = insert(root, id, loc, sev, ok);
        if (!ok) cout << "   ID " << id << " already exists - not inserted.\n";
    }

    void remove(int id) {
        cout << "Deleting ID " << id << "\n";
        bool deleted = false;
        root = remove(root, id, deleted);
        if (!deleted) cout << "   ID " << id << " not found.\n";
    }

    void search(int id) const {
        Node* r = search(root, id);
        if (r) { cout << "FOUND -> "; printRecord(r); }
        else   { cout << "ID " << id << " NOT FOUND.\n"; }
    }

    void displayLevelOrder() const {
        cout << "--- Level-order (BFS) ---\n";
        if (!root) { cout << "Tree is empty.\n"; return; }
        queue<Node*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = (int)q.size();
            cout << "Level " << level++ << ":\n";
            while (sz--) {
                Node* n = q.front(); q.pop();
                cout << "   "; printRecord(n);
                if (n->left)  q.push(n->left);
                if (n->right) q.push(n->right);
            }
        }
    }

    void displayInorder() const {
        cout << "--- In-order (sorted by Emergency ID) ---\n";
        inorder(root);
    }

    void displayAllById() const {
        cout << "--- All Emergency Records by ID ---\n";
        inorder(root);
    }

    void displayStructure() const {
        cout << "(Tree is rotated 90 degrees: root on the left, right children above, left children below)\n";
        if (!root) cout << "Tree is empty.\n";
        else printTree(root, 0);
    }

    int getHeight() const { return height(root); }

    bool isBalanced() const { return checkBalanced(root); }

private:
    bool checkBalanced(Node* n) const {
        if (!n) return true;
        int bf = balanceFactor(n);
        if (bf < -1 || bf > 1) return false;
        return checkBalanced(n->left) && checkBalanced(n->right);
    }
};

int main() {
    EmergencyAVL tree;

    cout << "===== INSERTING EMERGENCY RECORDS (watch the rotations) =====\n";
    tree.insert(50, "Mansehra",        7);
    tree.insert(40, "Muzaffarabad",    9);
    tree.insert(30, "Balakot",         10);
    tree.insert(60, "Abbottabad",      4);
    tree.insert(70, "Haripur",         3);
    tree.insert(35, "Kohala",          8);
    tree.insert(33, "Garhi Habibullah",7);
    tree.insert(20, "Neelum Valley",   9);
    tree.insert(25, "Bagh",            5);
    tree.insert(65, "Rawalakot",       6);
    tree.insert(80, "Kotli",           2);
    tree.insert(55, "Shinkiari",       5);

    cout << "\n===== BALANCED AVL TREE AFTER INSERTIONS =====\n";
    tree.displayStructure();
    cout << "Tree height: " << tree.getHeight()
         << " | All nodes balanced: " << (tree.isBalanced() ? "YES" : "NO") << "\n";

    cout << "\n===== TRAVERSALS =====\n";
    tree.displayInorder();
    cout << "\n";
    tree.displayLevelOrder();

    cout << "\n===== SEARCH =====\n";
    tree.search(35);
    tree.search(99);

    cout << "\n===== DELETION (with automatic rebalancing) =====\n";
    tree.remove(35);
    tree.remove(99);
    tree.remove(40);
    tree.remove(55);

    cout << "\n===== FINAL BALANCED AVL TREE =====\n";
    tree.displayStructure();
    cout << "Tree height: " << tree.getHeight()
         << " | All nodes balanced: " << (tree.isBalanced() ? "YES" : "NO") << "\n";

    cout << "\n";
    tree.displayAllById();
    cout << "\n";
    tree.displayLevelOrder();

    return 0;
}
