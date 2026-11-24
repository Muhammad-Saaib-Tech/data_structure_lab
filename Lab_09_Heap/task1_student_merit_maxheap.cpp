// Task 1: University Student Merit Ranking (Max Heap, pointer based)
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Student {
    string name; int roll; int marks;
    Student *left, *right;
    Student(string n, int r, int m) : name(n), roll(r), marks(m), left(NULL), right(NULL) {}
};

void swapData(Student* a, Student* b) {
    swap(a->name, b->name); swap(a->roll, b->roll); swap(a->marks, b->marks);
}

class MaxHeap {
    Student* root;
    int count;

    // Find node at 1-based level-order position using the binary path of pos
    Student* nodeAt(int pos) {
        if (pos < 1 || pos > count) return NULL;
        int bits = 0;
        for (int t = pos; t > 1; t >>= 1) bits++;
        Student* cur = root;
        for (int i = bits - 1; i >= 0; i--)
            cur = ((pos >> i) & 1) ? cur->right : cur->left;
        return cur;
    }
    void heapifyUp(int pos) {
        while (pos > 1) {
            Student *c = nodeAt(pos), *p = nodeAt(pos / 2);
            if (c->marks > p->marks) { swapData(c, p); pos /= 2; }
            else break;
        }
    }
    void heapifyDown(Student* n) {
        if (!n) return;
        Student* big = n;
        if (n->left && n->left->marks > big->marks) big = n->left;
        if (n->right && n->right->marks > big->marks) big = n->right;
        if (big != n) { swapData(n, big); heapifyDown(big); }
    }
public:
    MaxHeap() : root(NULL), count(0) {}

    void insert(string name, int roll, int marks) {
        Student* node = new Student(name, roll, marks);
        count++;
        if (!root) root = node;
        else {
            Student* parent = nodeAt(count / 2);
            if (!parent->left) parent->left = node; else parent->right = node;
        }
        heapifyUp(count);                       // Heapify Up after every insertion
    }

    void deleteMax() {
        if (!root) { cout << "Heap is empty.\n"; return; }
        Student* last = nodeAt(count);
        cout << "Deleted: " << root->name << " (Roll " << root->roll << ", Marks " << root->marks << ")\n";
        if (count == 1) { delete root; root = NULL; count = 0; return; }
        Student* parent = nodeAt(count / 2);
        swapData(root, last);                   // move last node's data to root
        if (parent->right == last) parent->right = NULL; else parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);                      // Heapify Down
    }

    void display() {
        if (!root) { cout << "Heap is empty.\n"; return; }
        queue<Student*> q; q.push(root);
        while (!q.empty()) {
            Student* n = q.front(); q.pop();
            cout << "  " << n->name << " | Roll: " << n->roll << " | Marks: " << n->marks << "\n";
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
};

int main() {
    MaxHeap h;
    h.insert("Ali", 101, 78);
    h.insert("Sara", 102, 92);
    h.insert("Usman", 103, 65);
    h.insert("Hina", 104, 88);
    h.insert("Bilal", 105, 95);
    h.insert("Zainab", 106, 70);
    h.insert("Omar", 107, 83);

    cout << "Max Heap (Level Order Traversal):\n";
    h.display();

    cout << "\nDeleting student with highest marks...\n";
    h.deleteMax();

    cout << "\nUpdated Max Heap (Level Order Traversal):\n";
    h.display();
    return 0;
}
