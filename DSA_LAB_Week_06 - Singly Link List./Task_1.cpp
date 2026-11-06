#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class LinkedList
{
    Node* head;     // no tail pointer is used

public:
    LinkedList()
    {
        head = nullptr;
    }

    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Creates a new node dynamically and adds it to the end of the list
    void CreateNode(int value)
    {
        Node* newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr)    // traverse to the last node
            current = current->next;
        current->next = newNode;
    }

    // Traverses the list and prints all elements
    void Display()
    {
        if (head == nullptr)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node* current = head;
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
    LinkedList list;
    int choice, value;
    do
    {
        cout << "\n1. Create node (add at end)";
        cout << "\n2. Display list";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            list.CreateNode(value);
            break;
        case 2:
            list.Display();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 3);

    return 0;
}
