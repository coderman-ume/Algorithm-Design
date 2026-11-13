// dsa.cpp - Common Data Structures Implementation in C++
// Covers: Singly Linked List, Stack, Queue, Binary Search Tree, Hash Table, and Graph.

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// 1. Singly Linked List
// ==========================================
struct ListNode {
    int data;
    ListNode* next;

    ListNode(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void clear() {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert a value at the end of the list
    void insert(int value) {
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = newNode;
            return;
        }
        ListNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Remove the first occurrence of a value
    bool remove(int value) {
        if (!head) return false;

        if (head->data == value) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        ListNode* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next == nullptr) return false;

        ListNode* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
        return true;
    }

    // Search for a value in the list
    bool search(int value) const {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    // Print all elements in the list
    void traverse() const {
        ListNode* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL\n";
    }
};

// ==========================================
// 2. Stack (LIFO - Linked List Implementation)
// ==========================================
struct StackNode {
    int data;
    StackNode* next;

    StackNode(int val, StackNode* nextNode = nullptr) : data(val), next(nextNode) {}
};

class Stack {
private:
    StackNode* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            int dummy;
            pop(dummy);
        }
    }

    void push(int value) {
        topNode = new StackNode(value, topNode);
    }

    bool pop(int& outValue) {
        if (isEmpty()) return false;

        outValue = topNode->data;
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return true;
    }

    bool peek(int& outValue) const {
        if (isEmpty()) return false;
        outValue = topNode->data;
        return true;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void traverse() const {
        StackNode* current = topNode;
        while (current != nullptr) {
            cout << current->data << "\n";
            current = current->next;
        }
    }
};

// ==========================================
// 3. Queue (FIFO - Linked List Implementation)
// ==========================================
struct QueueNode {
    int data;
    QueueNode* next;

    QueueNode(int val) : data(val), next(nullptr) {}
};

class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            int dummy;
            dequeue(dummy);
        }
    }

    void enqueue(int value) {
        QueueNode* newNode = new QueueNode(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
            return;
        }
        rearNode->next = newNode;
        rearNode = newNode;
    }

    bool dequeue(int& outValue) {
        if (isEmpty()) return false;

        outValue = frontNode->data;
        QueueNode* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        return true;
    }

    bool peekFront(int& outValue) const {
        if (isEmpty()) return false;
        outValue = frontNode->data;
        return true;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    void traverse() const {
        QueueNode* current = frontNode;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }
};

// ==========================================
// 4. Binary Search Tree (BST)
// ==========================================
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, int value) {
        if (node == nullptr) return new BSTNode(value);

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* removeRec(BSTNode* node, int value, bool& removed) {
        if (node == nullptr) return nullptr;

        if (value < node->data) {
            node->left = removeRec(node->left, value, removed);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value, removed);
        } else {
            removed = true;
            // Case 1: Leaf node or single child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 2: Two children -> replace with inorder successor (smallest in right subtree)
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data, removed);
        }
        return node;
    }

    bool searchRec(BSTNode* node, int value) const {
        if (node == nullptr) return false;
        if (node->data == value) return true;

        if (value < node->data) return searchRec(node->left, value);
        return searchRec(node->right, value);
    }

    void inorderRec(BSTNode* node) const {
        if (!node) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    void preorderRec(BSTNode* node) const {
        if (!node) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    void postorderRec(BSTNode* node) const {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    void destroyTree(BSTNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insertRec(root, value);
    }

    bool remove(int value) {
        bool removed = false;
        root = removeRec(root, value, removed);
        return removed;
    }

    bool search(int value) const {
        return searchRec(root, value);
    }

    void inorder() const {
        inorderRec(root);
        cout << "\n";
    }

    void preorder() const {
        preorderRec(root);
        cout << "\n";
    }

    void postorder() const {
        postorderRec(root);
        cout << "\n";
    }
};

// ==========================================
// 5. Hash Table (Separate Chaining)
// ==========================================
class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<vector<int>> table;

    int hashFunction(int key) const {
        return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(int value) {
        int index = hashFunction(value);
        table[index].push_back(value);
    }

    bool remove(int value) {
        int index = hashFunction(value);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == value) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }

    bool search(int value) const {
        int index = hashFunction(value);
        for (int item : table[index]) {
            if (item == value) return true;
        }
        return false;
    }

    void traverse() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket " << i << ": ";
            for (int item : table[i]) {
                cout << item << " -> ";
            }
            cout << "NULL\n";
        }
    }
};

// ==========================================
// 6. Graph (Undirected Adjacency List)
// ==========================================
class Graph {
private:
    unordered_map<string, vector<string>> adjList;

    void dfsRec(const string& vertex, unordered_map<string, bool>& visited) const {
        visited[vertex] = true;
        cout << vertex << " ";

        for (const auto& neighbor : adjList.at(vertex)) {
            if (!visited[neighbor]) {
                dfsRec(neighbor, visited);
            }
        }
    }

public:
    void addVertex(const string& vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = {};
        }
    }

    void addEdge(const string& src, const string& dest) {
        addVertex(src);
        addVertex(dest);
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    bool removeEdge(const string& src, const string& dest) {
        if (adjList.find(src) == adjList.end() || adjList.find(dest) == adjList.end()) {
            return false;
        }

        auto removeNeighbor = [](vector<string>& neighbors, const string& target) {
            for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
                if (*it == target) {
                    neighbors.erase(it);
                    return true;
                }
            }
            return false;
        };

        bool removedForward = removeNeighbor(adjList[src], dest);
        bool removedReverse = removeNeighbor(adjList[dest], src);
        return removedForward || removedReverse;
    }

    bool search(const string& vertex) const {
        return adjList.find(vertex) != adjList.end();
    }

    void bfs(const string& startVertex) const {
        if (adjList.find(startVertex) == adjList.end()) {
            cout << "Vertex '" << startVertex << "' not found.\n";
            return;
        }

        unordered_map<string, bool> visited;
        queue<string> q;

        q.push(startVertex);
        visited[startVertex] = true;

        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << current << " ";

            for (const auto& neighbor : adjList.at(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    void dfs(const string& startVertex) const {
        if (adjList.find(startVertex) == adjList.end()) {
            cout << "Vertex '" << startVertex << "' not found.\n";
            return;
        }

        unordered_map<string, bool> visited;
        dfsRec(startVertex, visited);
        cout << "\n";
    }

    void traverse() const {
        for (const auto& [vertex, neighbors] : adjList) {
            cout << vertex << " -> ";
            for (const auto& neighbor : neighbors) {
                cout << neighbor << " ";
            }
            cout << "\n";
        }
    }
};

// ==========================================
// Demonstration / Driver Code
// ==========================================
int main() {
    cout << "======================================\n";
    cout << "       1. Singly Linked List          \n";
    cout << "======================================\n";
    LinkedList list;
    for (int val : {10, 20, 30, 40}) {
        list.insert(val);
    }
    list.traverse();
    cout << "Search 30: " << (list.search(30) ? "Found" : "Not Found") << "\n";
    cout << "Removing 30...\n";
    list.remove(30);
    list.traverse();

    cout << "\n======================================\n";
    cout << "       2. Stack (LIFO)                \n";
    cout << "======================================\n";
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Stack contents (top to bottom):\n";
    stack.traverse();
    int poppedVal;
    while (stack.pop(poppedVal)) {
        cout << "Popped: " << poppedVal << "\n";
    }

    cout << "\n======================================\n";
    cout << "       3. Queue (FIFO)                \n";
    cout << "======================================\n";
    Queue queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    cout << "Queue contents: ";
    queue.traverse();
    int dequeuedVal;
    while (queue.dequeue(dequeuedVal)) {
        cout << "Dequeued: " << dequeuedVal << "\n";
    }

    cout << "\n======================================\n";
    cout << "       4. Binary Search Tree (BST)    \n";
    cout << "======================================\n";
    BST bst;
    for (int val : {50, 30, 70, 20, 40, 60, 80}) {
        bst.insert(val);
    }
    cout << "Inorder Traversal:   "; bst.inorder();
    cout << "Preorder Traversal:  "; bst.preorder();
    cout << "Postorder Traversal: "; bst.postorder();
    cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << "\n";
    cout << "Removing root (50)...\n";
    bst.remove(50);
    cout << "Inorder after removal: "; bst.inorder();

    cout << "\n======================================\n";
    cout << "       5. Hash Table                  \n";
    cout << "======================================\n";
    HashTable hashTable;
    for (int val : {12, 22, 32, 42, 15, 25}) {
        hashTable.insert(val);
    }
    hashTable.traverse();
    cout << "Search 25: " << (hashTable.search(25) ? "Found" : "Not Found") << "\n";
    cout << "Removing 22...\n";
    hashTable.remove(22);
    hashTable.traverse();

    cout << "\n======================================\n";
    cout << "       6. Graph (Adjacency List)      \n";
    cout << "======================================\n";
    Graph graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");
    graph.addEdge("D", "E");

    cout << "Adjacency List:\n";
    graph.traverse();

    cout << "BFS starting from A: ";
    graph.bfs("A");

    cout << "DFS starting from A: ";
    graph.dfs("A");

    cout << "Search vertex 'E': " << (graph.search("E") ? "Found" : "Not Found") << "\n";

    return 0;
}
