#include <iostream>
#include <string>
using namespace std;

struct PrintJob
{
    int jobID;
    string userName;
    int pages;
};

ostream& operator<<(ostream& out, const PrintJob& p)
{
    out << "Job ID: " << p.jobID << ", User: " << p.userName
        << ", Pages: " << p.pages;
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

// Checks if a job ID is already in the queue (queue order is preserved)
bool idExists(MyQueue<PrintJob>& queue, int id)
{
    bool found = false;
    int n = queue.size();
    for (int i = 0; i < n; i++)
    {
        PrintJob p = queue.dequeue();
        if (p.jobID == id)
            found = true;
        queue.enqueue(p);
    }
    return found;
}

int main()
{
    int size;
    cout << "Enter maximum number of print jobs in the queue: ";
    cin >> size;
    MyQueue<PrintJob> queue(size);

    int choice;
    do
    {
        cout << "\n1. Submit a new print job";
        cout << "\n2. Process the next print job";
        cout << "\n3. Display the next print job";
        cout << "\n4. Display all pending print jobs";
        cout << "\n5. Show the total number of pending print jobs";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            PrintJob p;
            cout << "Enter job ID: ";
            cin >> p.jobID;
            if (idExists(queue, p.jobID))
            {
                cout << "This job ID already exists." << endl;
                break;
            }
            cout << "Enter user name: ";
            cin.ignore();
            getline(cin, p.userName);
            cout << "Enter number of pages: ";
            cin >> p.pages;
            queue.enqueue(p);
            break;
        }
        case 2:
            if (queue.isEmpty())
                cout << "Underflow: no print jobs to process." << endl;
            else
                cout << "Completed -> " << queue.dequeue() << endl;
            break;
        case 3:
            if (queue.isEmpty())
                cout << "No print jobs in the queue." << endl;
            else
                cout << "Next job -> " << queue.peek() << endl;
            break;
        case 4:
            queue.display();
            break;
        case 5:
            cout << "Pending print jobs: " << queue.size() << endl;
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
