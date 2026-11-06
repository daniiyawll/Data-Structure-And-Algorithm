#include <iostream>
using namespace std;

template <typename Type>
class List
{
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    List(int maxSize = 10, int currentSize = 0)
    {
        this->maxSize = maxSize;
        this->currentSize = currentSize;
        arr = new Type[maxSize];
    }

    List(const List& other)
    {
        maxSize = other.maxSize;
        currentSize = other.currentSize;
        arr = new Type[maxSize];
        for (int i = 0; i < currentSize; i++)
            arr[i] = other.arr[i];
    }

    virtual ~List()
    {
        delete[] arr;
    }

    virtual void addElementAtFirstIndex(Type) = 0;
    virtual void addElementAtLastIndex(Type) = 0;
    virtual Type removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;
};

template <typename Type>
class MyList : public List<Type>
{
public:
    MyList(int maxSize = 10, int currentSize = 0) : List<Type>(maxSize, currentSize) {}

    MyList(const MyList& other) : List<Type>(other) {}

    ~MyList() {}

    bool empty()
    {
        return this->currentSize == 0;
    }

    bool full()
    {
        return this->currentSize == this->maxSize;
    }

    int size()
    {
        return this->currentSize;
    }

    void addElementAtFirstIndex(Type value)
    {
        if (full())
        {
            cout << "List is full." << endl;
            return;
        }
        for (int i = this->currentSize; i > 0; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[0] = value;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type value)
    {
        if (full())
        {
            cout << "List is full." << endl;
            return;
        }
        this->arr[this->currentSize] = value;
        this->currentSize++;
    }

    Type removeElementFromEnd()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return Type();
        }
        this->currentSize--;
        return this->arr[this->currentSize];
    }

    void removeElementFromStart()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; i++)
            this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }

    bool insertAt(int index, Type value)
    {
        if (full() || index < 0 || index > this->currentSize)
            return false;
        for (int i = this->currentSize; i > index; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    Type last()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return Type();
        }
        return this->arr[this->currentSize - 1];
    }

    bool search(Type value)
    {
        for (int i = 0; i < this->currentSize; i++)
            if (this->arr[i] == value)
                return true;
        return false;
    }

    void display()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return;
        }
        for (int i = 0; i < this->currentSize; i++)
            cout << this->arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    int maxSize;
    cout << "Enter maximum size of the list: ";
    cin >> maxSize;
    MyList<int> list(maxSize);

    int choice, value, index;
    do
    {
        cout << "\n1. Add element at first index";
        cout << "\n2. Add element at last index";
        cout << "\n3. Remove element from end";
        cout << "\n4. Remove element from start";
        cout << "\n5. Insert at index";
        cout << "\n6. Search";
        cout << "\n7. Last element";
        cout << "\n8. Size";
        cout << "\n9. Is empty?";
        cout << "\n10. Is full?";
        cout << "\n11. Display list";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            list.addElementAtFirstIndex(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            list.addElementAtLastIndex(value);
            break;
        case 3:
            if (!list.empty())
                cout << "Removed: " << list.removeElementFromEnd() << endl;
            else
                cout << "List is empty." << endl;
            break;
        case 4:
            list.removeElementFromStart();
            break;
        case 5:
            cout << "Enter index and value: ";
            cin >> index >> value;
            if (list.insertAt(index, value))
                cout << "Value inserted." << endl;
            else
                cout << "Invalid index or list is full." << endl;
            break;
        case 6:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (list.search(value) ? "Found" : "Not found") << endl;
            break;
        case 7:
            if (!list.empty())
                cout << "Last element: " << list.last() << endl;
            else
                cout << "List is empty." << endl;
            break;
        case 8:
            cout << "Size: " << list.size() << endl;
            break;
        case 9:
            cout << (list.empty() ? "Yes, list is empty" : "No, list is not empty") << endl;
            break;
        case 10:
            cout << (list.full() ? "Yes, list is full" : "No, list is not full") << endl;
            break;
        case 11:
            list.display();
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
