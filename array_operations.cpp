#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAt(int value, int position) {
        if (position < 1) {
            return;
        }

        if (position == 1) {
            Node* newNode = new Node(value);
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;
            } else {
                tail = newNode;
            }
            head = newNode;
            return;
        }

        Node* current = head;
        for (int index = 1; current != nullptr && index < position - 1; index++) {
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        newNode->prev = current;
        current->next = newNode;

        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        } else {
            tail = newNode;
        }
    }

    bool deleteAt(int position, int& deletedValue) {
        if (position < 1 || head == nullptr) {
            return false;
        }

        Node* current = head;
        for (int index = 1; current != nullptr && index < position; index++) {
            current = current->next;
        }

        if (current == nullptr) {
            return false;
        }

        deletedValue = current->data;
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        delete current;
        return true;
    }

    void display() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;
    int size;

    cout << "Enter the number of elements: ";
    cin >> size;

    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        int value;
        cin >> value;
        list.insertAt(value, i + 1);
    }

    cout << "\nOriginal Array: ";
    list.display();

    int insertValue, insertPos;
    cout << "\nEnter value to insert: ";
    cin >> insertValue;
    cout << "Enter position to insert at (1 to " << size + 1 << "): ";
    cin >> insertPos;

    if (insertPos < 1 || insertPos > size + 1) {
        cout << "Invalid position!" << endl;
    } else {
        list.insertAt(insertValue, insertPos);
        size++;

        cout << "Array after insertion: ";
        list.display();
    }

    int deletePos;
    cout << "\nEnter position to delete from (1 to " << size << "): ";
    cin >> deletePos;

    if (deletePos < 1 || deletePos > size) {
        cout << "Invalid position!" << endl;
    } else {
        int deletedValue;
        list.deleteAt(deletePos, deletedValue);
        cout << "Deleted element: " << deletedValue << endl;
        --size;

        cout << "Array after deletion: ";
        list.display();
    }

    return 0;
}
