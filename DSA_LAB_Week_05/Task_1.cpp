#include <iostream>
using namespace std;

template <typename T>
class AbstractQueue
{
public:
    virtual void enQueue(T value) = 0;
    virtual T deQueue() = 0;
    virtual T front() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractQueue() {}
};

// Circular array implementation
template <typename T>
class myQueue : public AbstractQueue<T>
{
    T* arr;
    int maxSize;
    int frontIndex;
    int rearIndex;
    int count;

public:
    myQueue(int size = 10)
    {
        maxSize = size;
        frontIndex = 0;
        rearIndex = maxSize - 1;
        count = 0;
        arr = new T[maxSize];
    }

    ~myQueue()
    {
        delete[] arr;
    }

    // Adds an element at the rear of the queue
    void enQueue(T value)
    {
        if (isFull())
        {
            cout << "Queue is full." << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % maxSize;
        arr[rearIndex] = value;
        count++;
    }

    // Removes and returns the front element
    T deQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        T value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        count--;
        return value;
    }

    // Returns the front element without removing it
    T front() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        return arr[frontIndex];
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    bool isFull() const
    {
        return count == maxSize;
    }

    int size() const
    {
        return count;
    }

    // Prints all elements from front to rear
    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }
        for (int i = 0; i < count; i++)
            cout << arr[(frontIndex + i) % maxSize] << " ";
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum size of the queue: ";
    cin >> size;
    myQueue<int> queue(size);

    int choice, value;
    do
    {
        cout << "\n1. Enqueue element";
        cout << "\n2. Dequeue element";
        cout << "\n3. Show front element";
        cout << "\n4. Check if queue is empty";
        cout << "\n5. Check if queue is full";
        cout << "\n6. Display queue elements";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            queue.enQueue(value);
            break;
        case 2:
            if (!queue.isEmpty())
                cout << "Dequeued: " << queue.deQueue() << endl;
            else
                cout << "Queue is empty." << endl;
            break;
        case 3:
            if (!queue.isEmpty())
                cout << "Front element: " << queue.front() << endl;
            else
                cout << "Queue is empty." << endl;
            break;
        case 4:
            cout << (queue.isEmpty() ? "Queue is empty" : "Queue is not empty") << endl;
            break;
        case 5:
            cout << (queue.isFull() ? "Queue is full" : "Queue is not full") << endl;
            break;
        case 6:
            queue.display();
            break;
        case 7:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 7);

    return 0;
}
