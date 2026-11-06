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

template <typename T>
class Stack
{
    T* arr;
    int topIndex;

public:
    Stack(int size)
    {
        topIndex = -1;
        arr = new T[size];
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

    bool isEmpty() const
    {
        return topIndex == -1;
    }
};

// Reverses only the first k elements of the queue
void reverseFirstK(myQueue<int>& queue, int k)
{
    int n = queue.size();
    if (k > n)
        k = n;              // k larger than the queue: reverse the whole queue
    if (k <= 1)
        return;             // k = 0 or 1: nothing to reverse

    Stack<int> stack(k);

    // take the first k elements out and keep them on a stack
    for (int i = 0; i < k; i++)
        stack.push(queue.deQueue());

    // put them back reversed
    while (!stack.isEmpty())
        queue.enQueue(stack.pop());

    // move the remaining elements behind them to restore their original order
    for (int i = 0; i < n - k; i++)
        queue.enQueue(queue.deQueue());
}

int main()
{
    int n, k, value;
    cout << "Enter number of elements in the queue: ";
    cin >> n;
    myQueue<int> queue(n);

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        queue.enQueue(value);
    }

    cout << "Queue: ";
    queue.display();

    cout << "Enter K: ";
    cin >> k;
    cout << "K = " << k << endl;

    reverseFirstK(queue, k);

    cout << "Output: ";
    queue.display();

    return 0;
}
