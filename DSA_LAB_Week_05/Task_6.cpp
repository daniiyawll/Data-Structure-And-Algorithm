#include <iostream>
#include <string>
using namespace std;

// A package with its delivery time window (times in 24-hour HHMM format, e.g. 1430)
struct Package
{
    int id;
    string address;
    int startTime;
    int endTime;
};

ostream& operator<<(ostream& out, const Package& p)
{
    out << "[ID: " << p.id << ", Address: " << p.address
        << ", Window: " << p.startTime << "-" << p.endTime << "] ";
    return out;
}

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

// Checks the front package against the current time.
// Expired packages are logged and skipped. Returns true if the front package
// can be delivered now.
bool timeToDeliver(myQueue<Package>& queue, int currentTime)
{
    while (!queue.isEmpty())
    {
        Package p = queue.front();
        if (currentTime > p.endTime)
        {
            cout << "LOG: Package " << p.id << " expired (window ended at "
                 << p.endTime << "). Skipped." << endl;
            queue.deQueue();
        }
        else if (currentTime < p.startTime)
        {
            cout << "Package " << p.id << " is too early; its window opens at "
                 << p.startTime << "." << endl;
            return false;
        }
        else
        {
            cout << "Package " << p.id << " can be delivered now." << endl;
            return true;
        }
    }
    cout << "No packages left in the queue." << endl;
    return false;
}

int main()
{
    myQueue<Package> packages(100);

    int choice;
    do
    {
        cout << "\n1. Add a new package";
        cout << "\n2. Deliver (remove) the front package";
        cout << "\n3. View the front package";
        cout << "\n4. Display all packages";
        cout << "\n5. Check time to deliver";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Package p;
            cout << "Enter package ID: ";
            cin >> p.id;
            cout << "Enter delivery address: ";
            cin.ignore();
            getline(cin, p.address);
            cout << "Enter window start time (HHMM): ";
            cin >> p.startTime;
            cout << "Enter window end time (HHMM): ";
            cin >> p.endTime;
            if (p.startTime >= p.endTime)
                cout << "Invalid time window." << endl;
            else
            {
                packages.enQueue(p);
                cout << "Package " << p.id << " added." << endl;
            }
            break;
        }
        case 2:
            if (!packages.isEmpty())
                cout << "Delivered package " << packages.deQueue().id << "." << endl;
            else
                cout << "No packages in the queue." << endl;
            break;
        case 3:
            if (!packages.isEmpty())
                cout << "Front package: " << packages.front() << endl;
            else
                cout << "No packages in the queue." << endl;
            break;
        case 4:
            cout << "Packages: ";
            packages.display();
            break;
        case 5:
        {
            int currentTime;
            cout << "Enter current time (HHMM): ";
            cin >> currentTime;
            timeToDeliver(packages, currentTime);
            break;
        }
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
