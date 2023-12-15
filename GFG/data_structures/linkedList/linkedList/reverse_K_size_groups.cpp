struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *current = head;
        while (current != nullptr)
        {
            ListNode *nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        return prev;
    }
    ListNode *findKthNode(ListNode *temp, int K)
    {
        int count = 1;
        while (temp != nullptr)
        {
            if (count == K)
                return temp;
            else
            {
                count++;
                temp = temp->next;
            }
        }
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *temp = head;
        ListNode *prevLast = nullptr;
        while (temp != nullptr)
        {
            ListNode *kthNode = findKthNode(temp, k);
            if (kthNode == nullptr)
            {
                if (prevLast)
                {
                    prevLast->next = temp;
                    break;
                }
            }
            ListNode *nextNode = kthNode->next;
            kthNode->next = nullptr;
            reverseList(temp);
            if (temp == head)
            {
                head = kthNode;
            }
            else
            {
                prevLast->next = kthNode;
            }
            prevLast = temp;
            temp = nextNode;
        }
        return head;
    }
};