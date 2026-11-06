#include <iostream>
using namespace std;

template <typename T>
class AbstractStack
{
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T>
{
protected:
    T* arr;
    int maxSize;
    int topIndex;

public:
    myStack(int size = 10)
    {
        maxSize = size;
        topIndex = -1;
        arr = new T[maxSize];
    }

    ~myStack()
    {
        delete[] arr;
    }

    // Adds an element on top of the stack
    void push(T value)
    {
        if (isFull())
        {
            cout << "Stack is full." << endl;
            return;
        }
        arr[++topIndex] = value;
    }

    // Removes and returns the top element
    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return arr[topIndex--];
    }

    // Returns the top element without removing it
    T top() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return arr[topIndex];
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxSize - 1;
    }

    // Prints all elements from top to bottom
    void display() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return;
        }
        for (int i = topIndex; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum size of the stack: ";
    cin >> size;
    myStack<int> stack(size);

    int choice, value;
    do
    {
        cout << "\n1. Push element";
        cout << "\n2. Pop element";
        cout << "\n3. Show top element";
        cout << "\n4. Check if stack is empty";
        cout << "\n5. Check if stack is full";
        cout << "\n6. Display stack elements";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            stack.push(value);
            break;
        case 2:
            if (!stack.isEmpty())
                cout << "Popped: " << stack.pop() << endl;
            else
                cout << "Stack is empty." << endl;
            break;
        case 3:
            if (!stack.isEmpty())
                cout << "Top element: " << stack.top() << endl;
            else
                cout << "Stack is empty." << endl;
            break;
        case 4:
            cout << (stack.isEmpty() ? "Stack is empty" : "Stack is not empty") << endl;
            break;
        case 5:
            cout << (stack.isFull() ? "Stack is full" : "Stack is not full") << endl;
            break;
        case 6:
            stack.display();
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
