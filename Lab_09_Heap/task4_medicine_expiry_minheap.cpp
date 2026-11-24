// Task 4: Hospital Medicine Expiry Management (Min Heap, pointer based)
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Medicine {
    string name; int id; int expiry;            // expiry in YYYYMMDD
    Medicine *left, *right;
    Medicine(string n, int i, int e) : name(n), id(i), expiry(e), left(NULL), right(NULL) {}
};

void swapData(Medicine* a, Medicine* b) {
    swap(a->name, b->name); swap(a->id, b->id); swap(a->expiry, b->expiry);
}

class MinHeap {
    Medicine* root;
    int count;

    Medicine* nodeAt(int pos) {
        if (pos < 1 || pos > count) return NULL;
        int bits = 0;
        for (int t = pos; t > 1; t >>= 1) bits++;
        Medicine* cur = root;
        for (int i = bits - 1; i >= 0; i--)
            cur = ((pos >> i) & 1) ? cur->right : cur->left;
        return cur;
    }
    void heapifyUp(int pos) {
        while (pos > 1) {
            Medicine *c = nodeAt(pos), *p = nodeAt(pos / 2);
            if (c->expiry < p->expiry) { swapData(c, p); pos /= 2; }
            else break;
        }
    }
    void heapifyDown(Medicine* n) {
        if (!n) return;
        Medicine* small = n;
        if (n->left && n->left->expiry < small->expiry) small = n->left;
        if (n->right && n->right->expiry < small->expiry) small = n->right;
        if (small != n) { swapData(n, small); heapifyDown(small); }
    }
public:
    MinHeap() : root(NULL), count(0) {}

    void insert(string name, int id, int expiry) {
        Medicine* node = new Medicine(name, id, expiry);
        count++;
        if (!root) root = node;
        else {
            Medicine* parent = nodeAt(count / 2);
            if (!parent->left) parent->left = node; else parent->right = node;
        }
        heapifyUp(count);
    }

    void deleteNearestExpiry() {
        if (!root) { cout << "Heap is empty.\n"; return; }
        Medicine* last = nodeAt(count);
        cout << "Nearest expiry (deleted): " << root->name << " | ID: " << root->id
             << " | Expiry: " << root->expiry << "\n";
        if (count == 1) { delete root; root = NULL; count = 0; return; }
        Medicine* parent = nodeAt(count / 2);
        swapData(root, last);
        if (parent->right == last) parent->right = NULL; else parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
    }

    void display() {
        if (!root) { cout << "Heap is empty.\n"; return; }
        queue<Medicine*> q; q.push(root);
        while (!q.empty()) {
            Medicine* n = q.front(); q.pop();
            cout << "  " << n->name << " | ID: " << n->id << " | Expiry: " << n->expiry << "\n";
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
};

int main() {
    MinHeap h;
    h.insert("Paracetamol", 301, 20270315);
    h.insert("Amoxicillin", 302, 20261120);
    h.insert("Ibuprofen", 303, 20280601);
    h.insert("Insulin", 304, 20261005);
    h.insert("Aspirin", 305, 20270930);
    h.insert("Cough Syrup", 306, 20261230);

    cout << "Min Heap (Level Order Traversal):\n";
    h.display();

    cout << "\n";
    h.deleteNearestExpiry();

    cout << "\nUpdated Min Heap (Level Order Traversal):\n";
    h.display();
    return 0;
}
