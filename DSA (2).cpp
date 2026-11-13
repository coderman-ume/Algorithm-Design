#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void display() const {
        if (head == nullptr) {
            std::cout << "empty\n";
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << (current->next ? " <-> " : "");
            current = current->next;
        }
        std::cout << "\n";
    }

    void insertFront(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertBack(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteFront() {
        if (head == nullptr) {
            std::cout << "cant delete, empty\n";
            return;
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete temp;
        std::cout << "deleted\n";
    }

    void deleteBack() {
        if (tail == nullptr) {
            std::cout << "cant delete, empty\n";
            return;
        }

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete temp;
        std::cout << "deleted\n";
    }

    void displayReverse() const {
        if (tail == nullptr) {
            std::cout << "empty\n";
            return;
        }

        Node* current = tail;
        while (current != nullptr) {
            std::cout << current->data << (current->prev ? " <-> " : "");
            current = current->prev;
        }
        std::cout << "\n";
    }
};

int main() {
    DoublyLinkedList list;
    int n, val;

    std::cout << "how many numbers? ";
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cout << "enter num " << (i + 1) << ": ";
        std::cin >> val;
        list.insertFront(val);
    }

    std::cout << "\nstarted list:\n";
    list.display();

    std::cout << "\nadd at front\n";
    std::cout << "before: ";
    list.display();
    std::cout << "enter num: ";
    std::cin >> val;
    list.insertFront(val);
    std::cout << "after: ";
    list.display();

    std::cout << "\nadd at end\n";
    std::cout << "before: ";
    list.display();
    std::cout << "enter num: ";
    std::cin >> val;
    list.insertBack(val);
    std::cout << "after: ";
    list.display();

    std::cout << "\nremove front\n";
    std::cout << "before: ";
    list.display();
    list.deleteFront();
    std::cout << "after: ";
    list.display();

    std::cout << "\nremove end\n";
    std::cout << "before: ";
    list.display();
    list.deleteBack();
    std::cout << "after: ";
    list.display();

    std::cout << "\nbackwards: ";
    list.displayReverse();

    return 0;
}