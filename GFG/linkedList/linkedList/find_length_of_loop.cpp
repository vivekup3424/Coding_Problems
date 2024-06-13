
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
// method 1- using counter, brute approach
int lengthOfLoop(Node *head)
{
    unordered_map<Node *, int> freq;
    int counter = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        counter++;
        if (freq.find(temp) != freq.end())
        {
            freq[temp] = counter;
        }
        else
        {
            return freq[temp] - counter;
        }
        temp = temp->next;
    }
    // Time COmplexity = O(2n)
    // Space Complexity = O(n)
}
// method 2:- using slow and fast pointer to first detect loop, and
//  then finding the length of that loop
//  uses constant extra space

int lengthOfLoop2(Node *head)
{
    Node *fast = head,
         *slow = head;
    bool result = false;
    while (fast != NULL and fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast)
        {
            result = true;
            break;
        }
    }
    if (result == false) // no loop, return 0
    {
        return 0;
    }
    // now find the length of the loop
    Node *temp = slow;
    int length = 1;
    slow = slow->next;
    while (temp != slow)
    {
        length++;
        slow = slow->next;
    }
    return length;
}
// Function to create a linked list with a loop for testing
Node *createLinkedListWithLoop()
{
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = head->next; // Creating a loop

    return head;
}

int main()
{
    // Test the lengthOfLoop2 function
    Node *headWithLoop = createLinkedListWithLoop();
    int loopLength = lengthOfLoop2(headWithLoop);

    if (loopLength > 0)
    {
        std::cout << "Length of the loop in the linked list: " << loopLength << std::endl;
    }
    else
    {
        std::cout << "No loop in the linked list." << std::endl;
    }

    // Clean up memory
    Node *current = headWithLoop;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}
