#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T>* next;

    Node(T value)
    {
        data = value;
        next = nullptr;
    }
};

// Singly linked list as an Abstract Data Type
template <typename T>
class LinkedList
{
    Node<T>* head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtBeginning(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node<T>* current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newNode;
    }

    // Deletes the first node holding the given value
    bool deleteByValue(T value)
    {
        if (head == nullptr)
            return false;

        if (head->data == value)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != value)
            current = current->next;

        if (current->next == nullptr)
            return false;

        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node<T>* current = head;
        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

int main()
{
    LinkedList<int> list;
    int choice, value;
    do
    {
        cout << "\n1. Insert at beginning";
        cout << "\n2. Insert at end";
        cout << "\n3. Delete a node by value";
        cout << "\n4. Display list";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            list.insertAtBeginning(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            list.insertAtEnd(value);
            break;
        case 3:
            cout << "Enter value to delete: ";
            cin >> value;
            if (list.deleteByValue(value))
                cout << "Value deleted." << endl;
            else
                cout << "Value not found." << endl;
            break;
        case 4:
            list.display();
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
