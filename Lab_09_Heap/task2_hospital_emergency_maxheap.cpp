// Task 2: Hospital Emergency Management System (Max Heap, pointer based)
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string name; int id; int priority;
    Patient *left, *right;
    Patient(string n, int i, int p) : name(n), id(i), priority(p), left(NULL), right(NULL) {}
};

void swapData(Patient* a, Patient* b) {
    swap(a->name, b->name); swap(a->id, b->id); swap(a->priority, b->priority);
}

class EmergencyHeap {
    Patient* root;
    int count;

    Patient* nodeAt(int pos) {
        if (pos < 1 || pos > count) return NULL;
        int bits = 0;
        for (int t = pos; t > 1; t >>= 1) bits++;
        Patient* cur = root;
        for (int i = bits - 1; i >= 0; i--)
            cur = ((pos >> i) & 1) ? cur->right : cur->left;
        return cur;
    }
    void heapifyUp(int pos) {
        while (pos > 1) {
            Patient *c = nodeAt(pos), *p = nodeAt(pos / 2);
            if (c->priority > p->priority) { swapData(c, p); pos /= 2; }
            else break;
        }
    }
    void heapifyDown(Patient* n) {
        if (!n) return;
        Patient* big = n;
        if (n->left && n->left->priority > big->priority) big = n->left;
        if (n->right && n->right->priority > big->priority) big = n->right;
        if (big != n) { swapData(n, big); heapifyDown(big); }
    }
public:
    EmergencyHeap() : root(NULL), count(0) {}

    void insert(string name, int id, int priority) {
        Patient* node = new Patient(name, id, priority);
        count++;
        if (!root) root = node;
        else {
            Patient* parent = nodeAt(count / 2);
            if (!parent->left) parent->left = node; else parent->right = node;
        }
        heapifyUp(count);
    }

    void showHighestPriority() {
        if (!root) { cout << "No patients waiting.\n"; return; }
        cout << "Highest priority: " << root->name << " | ID: " << root->id
             << " | Priority: " << root->priority << "\n";
    }

    void treatPatient() {          // delete after treatment + Heapify Down
        if (!root) { cout << "No patients waiting.\n"; return; }
        Patient* last = nodeAt(count);
        cout << "Treated and removed: " << root->name << " (ID " << root->id
             << ", Priority " << root->priority << ")\n";
        if (count == 1) { delete root; root = NULL; count = 0; return; }
        Patient* parent = nodeAt(count / 2);
        swapData(root, last);
        if (parent->right == last) parent->right = NULL; else parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
    }

    void display() {
        if (!root) { cout << "No patients waiting.\n"; return; }
        queue<Patient*> q; q.push(root);
        while (!q.empty()) {
            Patient* n = q.front(); q.pop();
            cout << "  " << n->name << " | ID: " << n->id << " | Priority: " << n->priority << "\n";
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
};

int main() {
    EmergencyHeap h;
    h.insert("Ahmed", 201, 3);
    h.insert("Fatima", 202, 9);
    h.insert("Hassan", 203, 5);
    h.insert("Ayesha", 204, 7);
    h.insert("Kamran", 205, 10);
    h.insert("Mariam", 206, 4);

    cout << "All patients (Level Order Traversal):\n";
    h.display();

    cout << "\n";
    h.showHighestPriority();

    cout << "\n";
    h.treatPatient();

    cout << "\nHeap after treatment (Level Order Traversal):\n";
    h.display();

    cout << "\nNext patient who needs treatment:\n";
    h.showHighestPriority();
    return 0;
}
