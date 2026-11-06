#include <iostream>
#include <string>
using namespace std;

struct Booking
{
    int customerID;
    string customerName;
    int numberOfTickets;
};

ostream& operator<<(ostream& out, const Booking& b)
{
    out << "ID: " << b.customerID << ", Name: " << b.customerName
        << ", Tickets: " << b.numberOfTickets;
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

// Checks if a customer ID is already booked (queue order is preserved)
bool idExists(MyQueue<Booking>& queue, int id)
{
    bool found = false;
    int n = queue.size();
    for (int i = 0; i < n; i++)
    {
        Booking b = queue.dequeue();
        if (b.customerID == id)
            found = true;
        queue.enqueue(b);
    }
    return found;
}

int main()
{
    int size;
    cout << "Enter number of bookings the hall can hold: ";
    cin >> size;
    MyQueue<Booking> queue(size);

    int choice;
    do
    {
        cout << "\n1. Book tickets";
        cout << "\n2. Cancel the first booking";
        cout << "\n3. Display the next booking";
        cout << "\n4. Display all bookings";
        cout << "\n5. Show the total number of bookings";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Booking b;
            cout << "Enter customer ID: ";
            cin >> b.customerID;
            if (idExists(queue, b.customerID))
            {
                cout << "This customer ID already exists." << endl;
                break;
            }
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, b.customerName);
            cout << "Enter number of tickets: ";
            cin >> b.numberOfTickets;
            queue.enqueue(b);
            break;
        }
        case 2:
            if (queue.isEmpty())
                cout << "Underflow: no bookings to cancel." << endl;
            else
                cout << "Cancelled -> " << queue.dequeue() << endl;
            break;
        case 3:
            if (queue.isEmpty())
                cout << "No bookings in the queue." << endl;
            else
                cout << "Next booking -> " << queue.peek() << endl;
            break;
        case 4:
            queue.display();
            break;
        case 5:
            cout << "Total bookings: " << queue.size() << endl;
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 6);

    return 0;
}
