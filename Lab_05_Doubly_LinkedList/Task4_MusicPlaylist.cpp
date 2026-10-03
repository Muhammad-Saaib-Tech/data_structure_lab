// Lab 05 - Task 4: Music Playlist (Circular Singly Linked List)
#include <iostream>
#include <string>
using namespace std;

// One song
class Node {
public:
    string songName;
    Node* next;   // next song (the last song points back to the first)

    Node(const string& name) : songName(name), next(NULL) {}
};

class Playlist {
private:
    Node* head;   // first song
    Node* tail;   // last song (tail->next == head, never NULL)
    int count;

public:
    Playlist() : head(NULL), tail(NULL), count(0) {}

    ~Playlist() {
        if (head == NULL) return;
        tail->next = NULL;          // break the circle before deleting
        Node* cur = head;
        while (cur != NULL) {
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
    }

    void addSong(const string& name) {
        Node* n = new Node(name);
        if (head == NULL) {
            head = tail = n;
            tail->next = head;
        } else {
            tail->next = n;
            tail = n;
            tail->next = head;      // last node connects to first, not NULL
        }
        count++;
    }

    // Display every song once
    void displaySongs() const {
        cout << "Playlist (all songs once):" << endl;
        Node* cur = head;
        int i = 1;
        do {
            cout << "  " << i++ << ". " << cur->songName << endl;
            cur = cur->next;
        } while (cur != head);
    }

    // Play the playlist for the given number of complete rounds
    void play(int rounds) const {
        Node* cur = head;
        for (int r = 1; r <= rounds; r++) {
            cout << "Round " << r << ":" << endl;
            for (int i = 0; i < count; i++) {
                cout << "  Now playing: " << cur->songName << endl;
                cur = cur->next;    // after the last song this returns to the first
            }
        }
    }
};

int main() {
    Playlist playlist;

    playlist.addSong("Tum Hi Ho");
    playlist.addSong("Shape of You");
    playlist.addSong("Blinding Lights");
    playlist.addSong("Kun Faya Kun");
    playlist.addSong("Believer");

    playlist.displaySongs();
    cout << endl;
    cout << "Playing the playlist for 2 complete rounds:" << endl;
    playlist.play(2);

    return 0;
}
