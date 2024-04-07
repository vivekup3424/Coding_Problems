#include <bits/stdc++.h>
using namespace std;
template <typename T>
class ListNode {
public:
    T val;
    ListNode<T>* next;

    ListNode(T x) : val(x), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    ListNode<T>* head;

public:
    LinkedList() : head(nullptr) {}

    // Insertion at the end
    void insert(T val) {
        ListNode<T>* newNode = new ListNode<T>(val);
        if (!head) {
            head = newNode;
            return;
        }
        ListNode<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Deletion by value
    void remove(T val) {
        if (!head) return;
        if (head->val == val) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        ListNode<T>* prev = head;
        ListNode<T>* curr = head->next;
        while (curr) {
            if (curr->val == val) {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // Insertion between two nodes
    void insertBetween(T val, T prevVal, T nextVal) {
        ListNode<T>* newNode = new ListNode<T>(val);
        ListNode<T>* prevNode = nullptr;
        ListNode<T>* nextNode = nullptr;
        ListNode<T>* temp = head;
        while (temp) {
            if (temp->val == prevVal) {
                prevNode = temp;
            } else if (temp->val == nextVal) {
                nextNode = temp;
                break;
            }
            temp = temp->next;
        }
        if (prevNode && nextNode) {
            newNode->next = nextNode;
            prevNode->next = newNode;
        }
    }

    // Deletion between two nodes
    void removeBetween(T prevVal, T nextVal) {
        ListNode<T>* prevNode = nullptr;
        ListNode<T>* nextNode = nullptr;
        ListNode<T>* temp = head;
        while (temp && temp->next) {
            if (temp->next->val == prevVal) {
                prevNode = temp;
            } else if (temp->val == nextVal) {
                nextNode = temp;
                break;
            }
            temp = temp->next;
        }
        if (prevNode && nextNode) {
            ListNode<T>* tempNode = prevNode->next;
            prevNode->next = nextNode;
            delete tempNode;
        }
    }

    // Traversal
    void traverse() {
        ListNode<T>* temp = head;
        while (temp) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Destructor
    ~LinkedList() {
        while (head) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{

}