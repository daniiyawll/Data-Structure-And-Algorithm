#include <iostream>
#include <string>
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
    myQueue<string> printQueue(50);

    int choice;
    string document;
    do
    {
        cout << "\n1. Add a print job";
        cout << "\n2. Print the front document";
        cout << "\n3. Check the front document";
        cout << "\n4. Display remaining print jobs";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter document name: ";
            cin.ignore();
            getline(cin, document);
            printQueue.enQueue(document);
            break;
        case 2:
            if (!printQueue.isEmpty())
                cout << "Printing: " << printQueue.deQueue() << endl;
            else
                cout << "No documents in the print queue." << endl;
            break;
        case 3:
            if (!printQueue.isEmpty())
                cout << "Front document: " << printQueue.front() << endl;
            else
                cout << "No documents in the print queue." << endl;
            break;
        case 4:
            cout << "Remaining print jobs: ";
            printQueue.display();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
