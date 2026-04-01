#include <iostream>
#include <string>
using namespace std;

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

struct Courier {
    string courierName;
    string vehicleType;
};

Package* stackTop = nullptr;

void push(string id, string city, int l, int w, int h) {
    Package* newNode    = new Package();
    newNode->packageID       = id;
    newNode->destinationCity = city;
    newNode->dimensions[0]   = l;
    newNode->dimensions[1]   = w;
    newNode->dimensions[2]   = h;
    newNode->next = stackTop;
    stackTop      = newNode;
    cout << "[STACK] " << id << " paketi eklendi.\n";
}

Package* pop() {
    if (stackTop == nullptr) {
        cout << "[STACK] Stack boş!\n";
        return nullptr;
    }
    Package* cikan = stackTop;
    stackTop       = stackTop->next;
    cikan->next    = nullptr;
    return cikan;
}

bool stackIsEmpty() {
    return stackTop == nullptr;
}

void displayStack() {
    if (stackIsEmpty()) {
        cout << "  Paket yok.\n";
        return;
    }
    Package* temp = stackTop;
    while (temp != nullptr) {
        cout << "  ID: "    << temp->packageID
             << " | Sehir: " << temp->destinationCity
             << " | Boyut: " << temp->dimensions[0]
             << "x"          << temp->dimensions[1]
             << "x"          << temp->dimensions[2]
             << "\n";
        temp = temp->next;
    }
}
const int SIZE = 5;

Courier courierArr[SIZE];
int qFront = 0;
int qRear  = 0;
int qCount = 0;

void enqueue(string isim, string arac) {
    if (qCount == SIZE) {
        cout << "[QUEUE] Kuyruk dolu!\n";
        return;
    }
    courierArr[qRear].courierName = isim;
    courierArr[qRear].vehicleType = arac;
    qRear  = (qRear + 1) % SIZE;
    qCount++;
    cout << "[QUEUE] " << isim << " kuyruğa eklendi.\n";
}

Courier dequeue() {
    Courier bos = {"", ""};
    if (qCount == 0) {
        cout << "[QUEUE] Kuyruk boş!\n";
        return bos;
    }
    Courier cikan = courierArr[qFront];
    qFront = (qFront + 1) % SIZE;
    qCount--;
    return cikan;
}

bool queueIsEmpty() {
    return qCount == 0;
}

void displayQueue() {
    if (queueIsEmpty()) {
        cout << "  Kurye yok.\n";
        return;
    }
    for (int i = 0; i < qCount; i++) {
        int index = (qFront + i) % SIZE;
        cout << "  Kurye: " << courierArr[index].courierName
             << " | Arac: "  << courierArr[index].vehicleType
             << "\n";
    }
}

void dispatch() {
    if (stackIsEmpty() || queueIsEmpty()) {
        cout << "[DISPATCH] Paket veya kurye yok!\n";
        return;
    }
    Package* paket = pop();
    Courier  kurye = dequeue();

    cout << "[DISPATCH] " << kurye.courierName
         << " (" << kurye.vehicleType << ") --> "
         << paket->packageID
         << " paketini " << paket->destinationCity
         << " sehrine goturuyor!\n";

    delete paket;
}
void display() {
    cout << "\n--- PAKETLER (Stack) ---\n";
    displayStack();
    cout << "--- KURYELER (Queue) ---\n";
    displayQueue();
    cout << "------------------------\n\n";
}
int main() {

    push("PKT-001", "Ankara", 30, 20, 15);
    push("PKT-002", "Izmir",  50, 40, 30);
    push("PKT-003", "Bursa",  10, 10, 10);

    enqueue("Ali",  "Motorsiklet");
    enqueue("Veli", "Van");
    enqueue("Ayse", "Bisiklet");

    display();
    dispatch(); 
    dispatch();
    display();

    return 0;
}