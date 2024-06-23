#include <bits/stdc++.h>
using namespace std;

class DLLNode
{
public:
    int key;
    int val;
    int freq;
    DLLNode *next;
    DLLNode *prev;
    DLLNode(int _key, int _val)
    {
        key = _key;
        val = _val;
        freq = 1;
        next = nullptr;
        prev = nullptr;
    }
};
class DLL
{
public:
    int size;
    DLLNode *head;
    DLLNode *tail;
    DLL()
    {
        size = 0;
        head = new DLLNode(-1, -1);
        tail = new DLLNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    void addNode(DLLNode *newNode)
    {
        // add the node after the head, for Last Recently Used
        DLLNode *temp = head->next;
        head->next = newNode;
        newNode->prev = head;
        newNode->next = temp;
        temp->prev = newNode;
        size++;
    }
    void removeNode(DLLNode *delNode)
    {
        DLLNode *prevNode = delNode->prev;
        DLLNode *nextNode = delNode->next;
        prevNode->next = delNode;
        nextNode->prev = prevNode;
        size--;
        delete delNode;
    }
};
class LFUCache
{
public:
    map<int, DLL *> freqList;
    map<int, DLLNode *> keyNode; // add node to our cache
    int capacity;
    int minFreq;
    int currSize;
    LFUCache(int _capacity)
    {
        capacity = _capacity;
        minFreq = 0;
        currSize = 0;
    }

    int get(int key)
    {
        if (keyNode.find(key) == keyNode.end())
        {
            // if node not in cache
            cout << "Node " << key << " not found\n";
            return -1;
        }
        else
        {
            // node found in cache
            DLLNode *node = keyNode[key];
            int value = tempNode->val;
            updateFreqListMap(node);
            return value;
        }
    }

    void put(int key, int value)
    {
        // if node is cache
        else if (keyNode.find(key) != keyNode.end())
        {
            DLLNode *node = keyNode[key];
            node->value = value;
            updateFreqListMap(node);
        }
        else
        {
            // check if cache is full
            if (currSize == capacity)
            {
                // Least Frequently USED
                DLL *minList = freqList[minFreq];
                // LRU in LFU
                DLLNode *delNode = minList->tail->prev;
                keyNode.erase(delNode->key);
                minList.removeNode(delNode);
                currSize--;
            }
            // now add the new node in the cache
            currSize++ : minFreq = 1; // since a new node is added
            DLL *minList = new DLL();
            // if list exists with freq = 1;
            if (freqList.find(minFreq) != freqList.end())
            {
            }
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */