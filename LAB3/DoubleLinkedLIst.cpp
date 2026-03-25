#include <iostream>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next = nullptr;
    Song* prev = nullptr;
};

Song* head = nullptr;
Song* tail = nullptr;
Song* current = nullptr;

void add(string title, string artist, int r0, int r1, int r2) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->ratings[0] = r0;
    newSong->ratings[1] = r1;
    newSong->ratings[2] = r2;

    if (tail == nullptr) {
        head = newSong;
        tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
    current = newSong;
}
void goNext() {
    if (current == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    if (current->next == nullptr) {
        cout << "Already at the last song!" << endl;
        return;
    }
    current = current->next;
    cout << "Now playing: " << current->title << endl;
}

void goPrev() {
    if (current == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    if (current->prev == nullptr) {
        cout << "Already at the first song!" << endl;
        return;
    }
    current = current->prev;
    cout << "Now playing: " << current->title << endl;
}

void removeCurrent() {
    if (current == nullptr) {
        cout << "Nothing to remove!" << endl;
        return;
    }

    Song* temp = current;

    if (temp->prev != nullptr)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != nullptr)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    if (temp->next != nullptr)
        current = temp->next;
    else
        current = temp->prev;

    cout << "Removed: " << temp->title << endl;
    delete temp;
}
void display() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    cout << "\n--- Playlist ---" << endl;
    for (Song* node = head; node != nullptr; node = node->next) {
        if (node == current)
            cout << "-> ";
        else
            cout << "   ";

        cout << node->title << " - " << node->artist << "  |  Ratings: ";
        for (int i = 0; i < 3; i++) {
            cout << node->ratings[i];
            if (i < 2) cout << ", ";
        }
        cout << endl;
    }
    cout << "----------------" << endl;
}

int main() {
    add("Bohemian Rhapsody", "Queen", 9, 10, 9);
    add("Hotel California", "Eagles", 8, 9, 8);
    add("Stairway to Heaven", "Led Zeppelin", 9, 9, 10);

    int choice;
    do {
        cout << "\n1. Display\n2. Next\n3. Previous\n4. Remove Current\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) display();
        else if (choice == 2) goNext();
        else if (choice == 3) goPrev();
        else if (choice == 4) removeCurrent();

    } while (choice != 0);

    return 0;
}