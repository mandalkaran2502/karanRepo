#include <iostream>

struct Node
{
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkList
{
private:
    Node* head;

public:
    // Constructor
    LinkList() : head(nullptr) {}

    // Destructor
    ~LinkList()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert at beginning
    void insertAtBeg(int val)
    {
        Node* newNode = new Node(val);

        newNode->next = head;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int val)
    {
        Node* newNode = new Node(val);

        // Empty list
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Node* temp = head;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    /*
        Insert at position (0-based indexing)

        Example:
        Position: 0  1  2
        List:    10 20 30

        insertAtPos(15, 1)

        Result:
        10 -> 15 -> 20 -> 30
    */
    void insertAtPos(int val, int pos)
    {
        // Insert at beginning
        if (pos <= 0 || head == nullptr)
        {
            insertAtBeg(val);
            return;
        }

        Node* newNode = new Node(val);
        Node* temp = head;

        // Move to (pos - 1)th node
        for (int i = 0; i < pos - 1 && temp->next != nullptr; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Delete from beginning
    void deleteAtBeg()
    {
        if (head == nullptr)
        {
            std::cout << "List is empty\n";
            return;
        }

        Node* temp = head;
        head = head->next;

        delete temp;
    }

    // Delete from end
    void deleteEnd()
    {
        if (head == nullptr)
        {
            std::cout << "List is empty\n";
            return;
        }

        // Single node case
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }

        Node* temp = head;

        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
    }

    /*
        Delete at position (0-based indexing)

        Example:
        Position: 0  1  2  3
        List:    10 20 30 40

        deleteAtPos(2)

        Result:
        10 -> 20 -> 40
    */
    void deleteAtPos(int pos)
    {
        if (head == nullptr)
        {
            std::cout << "List is empty\n";
            return;
        }

        // Delete first node
        if (pos <= 0)
        {
            deleteAtBeg();
            return;
        }

        Node* curr = head;

        // Move to (pos - 1)th node
        for (int i = 0; i < pos - 1 && curr->next != nullptr; i++)
        {
            curr = curr->next;
        }

        // Position out of range
        if (curr->next == nullptr)
        {
            std::cout << "Position out of range\n";
            return;
        }

        Node* temp = curr->next;

        curr->next = temp->next;

        delete temp;
    }

    // Reverse linked list
    void reverseList()
    {
        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;

        while (curr != nullptr)
        {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        head = prev;
    }

    // Print linked list
    void printList() const
    {
        if (head == nullptr)
        {
            std::cout << "List is empty\n";
            return;
        }

        Node* temp = head;

        while (temp != nullptr)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }

        std::cout << "NULL\n";
    }
};

int main()
{
    LinkList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);

    std::cout << "Initial List:\n";
    list.printList();

    std::cout << "\nInsert 15 at position 1:\n";
    list.insertAtPos(15, 1);
    list.printList();

    std::cout << "\nInsert 5 at position 0:\n";
    list.insertAtPos(5, 0);
    list.printList();

    std::cout << "\nDelete node at position 2:\n";
    list.deleteAtPos(2);
    list.printList();

    std::cout << "\nDelete first node:\n";
    list.deleteAtPos(0);
    list.printList();

    std::cout << "\nReverse List:\n";
    list.reverseList();
    list.printList();

    return 0;
}
