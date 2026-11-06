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

// Singly linked list as an Abstract Data Type (positions start from 1)
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

    // Counts the total number of nodes
    int countNodes()
    {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    // Inserts a node at a specific position (1 to count + 1)
    bool insertAtPosition(int position, T value)
    {
        if (position < 1 || position > countNodes() + 1)
            return false;

        Node<T>* newNode = new Node<T>(value);
        if (position == 1)
        {
            newNode->next = head;
            head = newNode;
            return true;
        }

        Node<T>* current = head;
        for (int i = 1; i < position - 1; i++)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
        return true;
    }

    // Deletes the node at a specific position (1 to count)
    bool deleteAtPosition(int position)
    {
        if (position < 1 || position > countNodes())
            return false;

        Node<T>* temp;
        if (position == 1)
        {
            temp = head;
            head = head->next;
        }
        else
        {
            Node<T>* current = head;
            for (int i = 1; i < position - 1; i++)
                current = current->next;
            temp = current->next;
            current->next = temp->next;
        }
        delete temp;
        return true;
    }

    // Returns the position of the value, or -1 if it is not present
    int search(T value)
    {
        int position = 1;
        Node<T>* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
                return position;
            current = current->next;
            position++;
        }
        return -1;
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
    int choice, value, position;
    do
    {
        cout << "\n1. Insert node at a specific position";
        cout << "\n2. Delete node at a specific position";
        cout << "\n3. Search for an element";
        cout << "\n4. Count total number of nodes";
        cout << "\n5. Display list";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter position and value: ";
            cin >> position >> value;
            if (list.insertAtPosition(position, value))
                cout << "Node inserted." << endl;
            else
                cout << "Invalid position." << endl;
            break;
        case 2:
            cout << "Enter position to delete: ";
            cin >> position;
            if (list.deleteAtPosition(position))
                cout << "Node deleted." << endl;
            else
                cout << "Invalid position." << endl;
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            position = list.search(value);
            if (position == -1)
                cout << "Value not found." << endl;
            else
                cout << "Value found at position " << position << "." << endl;
            break;
        case 4:
            cout << "Total nodes: " << list.countNodes() << endl;
            break;
        case 5:
            list.display();
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
