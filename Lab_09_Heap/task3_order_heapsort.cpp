// Task 3: Online Shopping Order Sorting (Heap Sort using repeated root deletion)
#include <iostream>
#include <string>
using namespace std;

struct Order {
    int orderID; string customer; double amount;
    Order *left, *right;
    Order(int id, string c, double a) : orderID(id), customer(c), amount(a), left(NULL), right(NULL) {}
};

void swapData(Order* a, Order* b) {
    swap(a->orderID, b->orderID); swap(a->customer, b->customer); swap(a->amount, b->amount);
}

class OrderHeap {
    Order* root;
    int count;

    Order* nodeAt(int pos) {
        if (pos < 1 || pos > count) return NULL;
        int bits = 0;
        for (int t = pos; t > 1; t >>= 1) bits++;
        Order* cur = root;
        for (int i = bits - 1; i >= 0; i--)
            cur = ((pos >> i) & 1) ? cur->right : cur->left;
        return cur;
    }
    void heapifyUp(int pos) {
        while (pos > 1) {
            Order *c = nodeAt(pos), *p = nodeAt(pos / 2);
            if (c->amount > p->amount) { swapData(c, p); pos /= 2; }
            else break;
        }
    }
    void heapifyDown(Order* n) {
        if (!n) return;
        Order* big = n;
        if (n->left && n->left->amount > big->amount) big = n->left;
        if (n->right && n->right->amount > big->amount) big = n->right;
        if (big != n) { swapData(n, big); heapifyDown(big); }
    }
public:
    OrderHeap() : root(NULL), count(0) {}
    int size() { return count; }

    void insert(int id, string customer, double amount) {
        Order* node = new Order(id, customer, amount);
        count++;
        if (!root) root = node;
        else {
            Order* parent = nodeAt(count / 2);
            if (!parent->left) parent->left = node; else parent->right = node;
        }
        heapifyUp(count);                       // Heapify Up during insertion
    }

    // Removes the root (largest) and returns its amount
    double deleteRoot() {
        double top = root->amount;
        Order* last = nodeAt(count);
        if (count == 1) { delete root; root = NULL; count = 0; return top; }
        Order* parent = nodeAt(count / 2);
        swapData(root, last);
        if (parent->right == last) parent->right = NULL; else parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
        return top;
    }
};

int main() {
    OrderHeap h;
    h.insert(1, "Ali", 4500);
    h.insert(2, "Sara", 1200);
    h.insert(3, "Usman", 9800);
    h.insert(4, "Hina", 2300);
    h.insert(5, "Bilal", 7600);
    h.insert(6, "Zainab", 3100);
    h.insert(7, "Omar", 500);

    int n = h.size();
    double* sorted = new double[n];             // stores deleted order amounts
    int k = 0;
    while (h.size() > 0)
        sorted[k++] = h.deleteRoot();           // comes out largest -> smallest

    cout << "Order amounts in ascending order (smallest to largest):\n";
    for (int i = n - 1; i >= 0; i--)
        cout << sorted[i] << (i > 0 ? ", " : "\n");

    delete[] sorted;
    return 0;
}
