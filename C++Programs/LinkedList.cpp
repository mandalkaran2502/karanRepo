#include <iostream>

struct Node
{
	int data;
	Node* next;
	
	Node(int val)
	{
	    data = val;
		next = nullptr;
	}
	
};

class LinkList
{
	public:
	Node* head;
	
	LinkList(int val)
	{
	    head = new Node(val);
	}
	
	~LinkList()
	{
		Node* temp;
		while(head)
		{
			temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
	}
	
	void insertAtEnd(int val)
	{
		Node* newNode = new Node(val);
		if(head == nullptr)
		{
			head = newNode;
		}
		else
		{
			Node* temp= head;
			while(temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
	
	void insertAtBeg(int val)
	{
	    Node* newNode = new Node(val);
	    if(head== nullptr)
	    {
	        head = newNode;
	    }
	    else
	    {
	        newNode->next = head;
	        head = newNode;
	    }
	}
	
	void insertAtpos(int val, int pos)
	{
		Node* newNode = new Node(val);
		if (pos <= 1)   // insert at beginning
		{
			newNode->next = head;
			head = newNode;
			return;
		}
		Node* temp = head;
		--pos;
		while(pos--)
		{
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
	
	void deleteAtBeg()
	{
		Node* temp = head;
		if(head == nullptr)
		{
			std::cout << "List is empty" << std::endl;
			return;
		}
		head = temp->next;
		delete temp;
	}
	
	void deleteEnd()
	{
		Node* temp = head;
		while (temp->next->next != nullptr)  // stop at second-last node
		{
			temp = temp->next;
		}
		delete temp->next;
		temp->next = nullptr;
	}
	
	//10-> 20-> 200-> 30-> 40-> NULL
	void deleteAtPos(int pos)
	{
		Node* curr = head;
		Node* temp = nullptr;
		if(pos == 0)
		{
			std::cout << "List is empty" << std::endl;
		}
		if(pos <=1)
		{
			head = curr->next;
		}
		--pos;
		while(pos--)
		{
			curr = curr->next;
		}
		temp = curr->next;
		curr->next = temp->next;
		delete temp;
		temp = nullptr;
	}
	
	void printList()
	{
	    if(head == nullptr)
	    {
	        std::cout << "List is empty" << std::endl;
	        return;
	    }
	    Node* temp = head;
	    while(temp)
	    {
	        std::cout << temp->data << "-> ";
	        temp = temp->next;
	    }
	    std::cout << "NULL" << std::endl;
	}
	
	
};

int main()
{
	LinkList li(10);
	li.insertAtEnd(20);
	li.insertAtEnd(30);
	li.insertAtEnd(40);
	//li.printList();
	//std::cout << "After insert the new node at beg" << std::endl;
	li.insertAtBeg(100);
	li.insertAtpos(200,3);
	//li.printList();
	//std::cout << "Deleting the head node" << std::endl;
	//li.deleteAtBeg();
	//li.printList();
	li.insertAtEnd(400);
	//li.printList();
	//std::cout << "Deleting the head node" << std::endl;
	//li.deleteEnd();
	std::cout << "Printing the listList" << std::endl;
	li.printList();
	std::cout << "Deleting the node at give position" << std::endl;
	li.deleteAtPos(3);
	li.printList();
	return 0;
}