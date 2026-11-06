#include <iostream>
#include <string>
using namespace std;

struct Customer
{
    string name;
    string transaction;
};

ostream& operator<<(ostream& out, const Customer& c)
{
    out << "Name: " << c.name << ", Transaction: " << c.transaction;
    return out;
}

template <typename T>
class Queue
{
protected:
    T* arr;
    int maxSize;
    int currentSize;

public:
    Queue(int maxQueueSize)
    {
        maxSize = maxQueueSize;
        currentSize = 0;
        arr = new T[maxSize];
    }

    virtual ~Queue()
    {
        delete[] arr;
    }

    virtual void enqueue(T data) = 0;
    virtual T dequeue() = 0;
    virtual T peek() = 0;
    virtual bool isFull() = 0;
    virtual bool isEmpty() = 0;
};

// Circular array queue
template <typename T>
class MyQueue : public Queue<T>
{
    int frontIndex;
    int rearIndex;

public:
    MyQueue(int maxQueueSize) : Queue<T>(maxQueueSize)
    {
        frontIndex = 0;
        rearIndex = maxQueueSize - 1;
    }

    ~MyQueue() {}

    bool isFull()
    {
        return this->currentSize == this->maxSize;
    }

    bool isEmpty()
    {
        return this->currentSize == 0;
    }

    int size()
    {
        return this->currentSize;
    }

    // Adds data at the back of the queue (position wraps around)
    void enqueue(T data)
    {
        if (isFull())
        {
            cout << "Overflow: the queue is full." << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % this->maxSize;
        this->arr[rearIndex] = data;
        this->currentSize++;
    }

    // Removes and returns the data at the front of the queue
    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Underflow: the queue is empty." << endl;
            return T();
        }
        T data = this->arr[frontIndex];
        frontIndex = (frontIndex + 1) % this->maxSize;
        this->currentSize--;
        return data;
    }

    // Returns the data at the front without removing it
    T peek()
    {
        if (isEmpty())
        {
            cout << "Underflow: the queue is empty." << endl;
            return T();
        }
        return this->arr[frontIndex];
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "The queue is empty." << endl;
            return;
        }
        for (int i = 0; i < this->currentSize; i++)
            cout << this->arr[(frontIndex + i) % this->maxSize] << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum number of customers in the queue: ";
    cin >> size;
    MyQueue<Customer> queue(size);

    int choice;
    do
    {
        cout << "\n1. Add a customer";
        cout << "\n2. Serve a customer";
        cout << "\n3. Display all waiting customers";
        cout << "\n4. Show total number of customers waiting";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Customer c;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, c.name);
            cout << "Enter transaction type (Deposit, Withdrawal, Loan Inquiry): ";
            getline(cin, c.transaction);
            queue.enqueue(c);
            break;
        }
        case 2:
            if (queue.isEmpty())
                cout << "Underflow: no customers to serve." << endl;
            else
            {
                Customer c = queue.dequeue();
                cout << "Served -> " << c << endl;
            }
            break;
        case 3:
            queue.display();
            break;
        case 4:
            cout << "Customers waiting: " << queue.size() << endl;
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
