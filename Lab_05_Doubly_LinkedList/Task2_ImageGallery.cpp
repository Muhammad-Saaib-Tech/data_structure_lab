// Lab 05 - Task 2: Image Gallery (Doubly Linked List)
#include <iostream>
#include <string>
using namespace std;

// One image in the gallery
class Node {
public:
    string imageName;
    Node* prev;   // previous image
    Node* next;   // next image

    Node(const string& name) : imageName(name), prev(NULL), next(NULL) {}
};

class ImageGallery {
private:
    Node* head;   // first image
    Node* tail;   // last image

public:
    ImageGallery() : head(NULL), tail(NULL) {}

    ~ImageGallery() {
        Node* cur = head;
        while (cur != NULL) {
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
    }

    void addImage(const string& name) {
        Node* n = new Node(name);
        if (head == NULL) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    // First -> last using next
    void displayForward() const {
        cout << "Gallery (first -> last):" << endl;
        Node* cur = head;
        int i = 1;
        while (cur != NULL) {
            cout << "  " << i++ << ". " << cur->imageName << endl;
            cur = cur->next;
        }
    }

    // Start from the last image and go backward using prev
    void displayBackward() const {
        cout << "Gallery (last -> first):" << endl;
        Node* cur = tail;
        int i = 1;
        while (cur != NULL) {
            cout << "  " << i++ << ". " << cur->imageName << endl;
            cur = cur->prev;
        }
    }

    // Shows movement in both directions from the middle image
    void movementDemo() const {
        cout << "Movement demo (start at image 3):" << endl;
        Node* cur = head->next->next;
        cout << "  Viewing  : " << cur->imageName << endl;
        cur = cur->next;
        cout << "  Next     : " << cur->imageName << "   (using next)" << endl;
        cur = cur->prev;
        cout << "  Previous : " << cur->imageName << "   (using prev)" << endl;
        cur = cur->prev;
        cout << "  Previous : " << cur->imageName << "   (using prev)" << endl;
        cur = cur->next;
        cout << "  Next     : " << cur->imageName << "   (using next)" << endl;
    }
};

int main() {
    ImageGallery gallery;

    gallery.addImage("sunset.jpg");
    gallery.addImage("mountain.png");
    gallery.addImage("beach.jpg");
    gallery.addImage("city_night.png");
    gallery.addImage("forest.jpg");

    gallery.displayForward();
    cout << endl;
    gallery.displayBackward();
    cout << endl;
    gallery.movementDemo();

    return 0;
}
