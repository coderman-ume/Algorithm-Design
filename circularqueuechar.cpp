#include <cassert>
#include <cstddef>
#include <iostream>

constexpr std::size_t MAX = 5;

class CircularQueue {
public:
    bool isFull() const
    {
        return count_ == MAX;
    }

    bool isEmpty() const
    {   return count_ == 0;
    }

    void insert(char item)
    {
        assert(!isFull() && "insert requires a non-full queue");
        rear_ = (rear_ + 1) % MAX;
        elements_[rear_] = item;
        ++count_;
    }

    char remove()
    {
        assert(!isEmpty() && "remove requires a non-empty queue");
        char item = elements_[front_];
        front_ = (front_ + 1) % MAX;
        --count_;
        return item;
    }

private:
    char elements_[MAX] {};
    std::size_t front_ = 0;
    std::size_t rear_ = MAX - 1;
    std::size_t count_ = 0;
};

void handleInsert(CircularQueue& queue)
{
    if (queue.isFull()) {
        std::cout << "Queue overflow: the queue is full.\n";
        return;
    }

    std::cout << "Enter a character to insert: ";
    char item;
    if (!(std::cin >> item)) {
        std::cerr << "Error: could not read a character.\n";
        return;
    }

    queue.insert(item);
    std::cout << "Inserted '" << item << "'.\n";
}

void handleDelete(CircularQueue& queue)
{
    if (queue.isEmpty()) {
        std::cout << "Queue underflow: the queue is empty.\n";
        return;
    }

    std::cout << "Deleted '" << queue.remove() << "'.\n";
}

int main()
{
    CircularQueue queue;

    while (true) {
        std::cout << "\n1. Insert an element\n";
        std::cout << "2. Delete an element\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cerr << "Error: invalid input. Exiting.\n";
            return 1;
        }

        switch (choice) {
        case 1:
            handleInsert(queue);
            break;
        case 2:
            handleDelete(queue);
            break;
        case 3:
            return 0;
        default:
            std::cout << "Invalid choice. Please enter 1, 2 or 3.\n";
            break;
        }
    }
}
