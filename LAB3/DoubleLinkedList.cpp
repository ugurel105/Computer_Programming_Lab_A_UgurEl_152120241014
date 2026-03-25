#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
};
void addWord(Node*& head, string word) {
    Node* newNode = new Node{word, nullptr};
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void undo(Node*& head) {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }

    if (head->next == nullptr) { 
        delete head;
        head = nullptr;
    } else {
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}

int main() {
    Node* head = nullptr;
    string input;

    while (true) {
        cout << "Enter word (UNDO/EXIT): ";
        cin >> input;

        if (input == "EXIT") break;

        if (input == "UNDO") {
            undo(head);
        } else {
            addWord(head, input);
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << "[" << temp->data << "] -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    return 0;
}