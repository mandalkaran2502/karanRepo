#include<iostream>
struct List
{
    int data;
    List* next;

    List(int val)
    :data(val),
    next(nullptr)
    {}
};

List* reverseList(List*& head)
{
    if(head == nullptr || head->next == nullptr)
    {
        return head;
    }
    List* curr = head;
    List* prev = nullptr;
    while(curr)
    {
        List* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}

List* pushback(List*& head,int val)
{
    if(!head)
    {
        head = new List(val);
        return head;
    }
    List* temp = head;
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = new List(val);
    return head;
}

void printList(List*& head) 
{
    List* temp = head;
    while(temp)
    {
        std::cout << temp->data << "-> " ;
        temp = temp->next;
    }
    std::cout << std::endl;
}

bool palindrome(List* &head)
{
    List* temp = head;
    if(!head || !head->next)
    {
        return true;    
    }
    List* slow = temp;
    List* fast = temp;
    
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    List* rev = reverseList(slow);
    List* d1 = head;
    List* d2 = rev;
    while(d2)
    {
        if(d1->data != d2->data)
        {
            return false;
            break;
        }
        d1 = d1->next;
        d2 = d2->next;
    }
    //slow = reverseList(rev);
    return true;
    
}


int main()
{
    List* head = nullptr;
    pushback(head,1);
    pushback(head,2);
    pushback(head,3);
    pushback(head,2);
    pushback(head,1);
    printList(head);
    // std::cout << "Reversing List" << std::endl;
    // head = reverseList(head);
    // printList(head);
    if(palindrome(head))
    {
        std::cout << "List is palindrome" << std::endl;
    }
    else
    
    {
        std::cout << "List is Not palindrome" << std::endl;
    }
    std::cout << palindrome(head) << std::endl;

    return 0;
}