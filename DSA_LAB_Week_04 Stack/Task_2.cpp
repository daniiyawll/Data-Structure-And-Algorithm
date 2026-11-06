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
    T* arr;
    T* minArr;        // additional stack that keeps track of minimum elements
    int maxSize;
    int topIndex;
    int minTop;

public:
    myStack(int size = 10)
    {
        maxSize = size;
        topIndex = -1;
        minTop = -1;
        arr = new T[maxSize];
        minArr = new T[maxSize];
    }

    ~myStack()
    {
        delete[] arr;
        delete[] minArr;
    }

    // Adds an element; also pushes it on the min stack if it is a new minimum
    void push(T value)
    {
        if (isFull())
        {
            cout << "Stack is full." << endl;
            return;
        }
        arr[++topIndex] = value;
        if (minTop == -1 || value <= minArr[minTop])
            minArr[++minTop] = value;
    }

    // Removes the top element; also pops the min stack if it was the minimum
    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        T value = arr[topIndex--];
        if (value == minArr[minTop])
            minTop--;
        return value;
    }

    T top() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return arr[topIndex];
    }

    // Returns the minimum element in O(1)
    T getMin() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return minArr[minTop];
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxSize - 1;
    }

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
        cout << "\n7. Show minimum element";
        cout << "\n8. Exit";
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
            if (!stack.isEmpty())
                cout << "Minimum element: " << stack.getMin() << endl;
            else
                cout << "Stack is empty." << endl;
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 8);

    return 0;
}
