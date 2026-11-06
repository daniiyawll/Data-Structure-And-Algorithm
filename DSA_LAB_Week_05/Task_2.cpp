#include <iostream>
using namespace std;

template <typename T>
class Stack
{
    T* arr;
    int maxSize;
    int topIndex;

public:
    Stack(int size = 10)
    {
        maxSize = size;
        topIndex = -1;
        arr = new T[maxSize];
    }

    ~Stack()
    {
        delete[] arr;
    }

    void push(T value)
    {
        arr[++topIndex] = value;
    }

    T pop()
    {
        return arr[topIndex--];
    }

    T top() const
    {
        return arr[topIndex];
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    int size() const
    {
        return topIndex + 1;
    }

    // element at position i counted from the bottom of the stack
    T at(int i) const
    {
        return arr[i];
    }
};

// Queue built from two stacks
template <typename T>
class QueueUsingStacks
{
    Stack<T> inStack;     // used for enqueue
    Stack<T> outStack;    // used for dequeue and front
    int maxSize;

    // Move all elements from inStack to outStack only when outStack is empty
    void transfer()
    {
        if (outStack.isEmpty())
            while (!inStack.isEmpty())
                outStack.push(inStack.pop());
    }

public:
    QueueUsingStacks(int size = 10) : inStack(size), outStack(size)
    {
        maxSize = size;
    }

    bool isEmpty() const
    {
        return inStack.isEmpty() && outStack.isEmpty();
    }

    bool isFull() const
    {
        return inStack.size() + outStack.size() == maxSize;
    }

    void enqueue(T value)
    {
        if (isFull())
        {
            cout << "Queue is full." << endl;
            return;
        }
        inStack.push(value);
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        transfer();
        return outStack.pop();
    }

    T front()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        transfer();
        return outStack.top();
    }

    // Prints elements from front to rear
    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }
        for (int i = outStack.size() - 1; i >= 0; i--)
            cout << outStack.at(i) << " ";
        for (int i = 0; i < inStack.size(); i++)
            cout << inStack.at(i) << " ";
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum size of the queue: ";
    cin >> size;
    QueueUsingStacks<int> queue(size);

    int choice, value;
    do
    {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Front element";
        cout << "\n4. Display elements";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            queue.enqueue(value);
            break;
        case 2:
            if (!queue.isEmpty())
                cout << "Dequeued: " << queue.dequeue() << endl;
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
            queue.display();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 5);

    return 0;
}
