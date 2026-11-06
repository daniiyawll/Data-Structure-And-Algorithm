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

// Checks if a ticket id is already in the queue (queue is restored afterwards)
bool ticketExists(myQueue<int>& queue, int id)
{
    bool found = false;
    int n = queue.size();
    for (int i = 0; i < n; i++)
    {
        int t = queue.deQueue();
        if (t == id)
            found = true;
        queue.enQueue(t);
    }
    return found;
}

int main()
{
    myQueue<int> tickets(100);

    int choice, id;
    do
    {
        cout << "\n1. Add a new ticket";
        cout << "\n2. Resolve the next ticket";
        cout << "\n3. Check the next ticket to be resolved";
        cout << "\n4. Display all pending tickets";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter 4-digit ticket ID: ";
            cin >> id;
            if (id < 1000 || id > 9999)
                cout << "Ticket ID must be 4 digits." << endl;
            else if (ticketExists(tickets, id))
                cout << "Ticket ID already exists." << endl;
            else
            {
                tickets.enQueue(id);
                cout << "Ticket " << id << " added." << endl;
            }
            break;
        case 2:
            if (!tickets.isEmpty())
                cout << "Ticket " << tickets.deQueue() << " resolved." << endl;
            else
                cout << "No pending tickets." << endl;
            break;
        case 3:
            if (!tickets.isEmpty())
                cout << "Next ticket: " << tickets.front() << endl;
            else
                cout << "No pending tickets." << endl;
            break;
        case 4:
            cout << "Pending tickets: ";
            tickets.display();
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
