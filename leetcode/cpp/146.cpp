#include <bits/stdc++.h>
using namespace std;
class DLLNode
{
public:
    int key;
    int val;
    DLLNode *next;
    DLLNode *prev;
    DLLNode(int _key, int _val) : key(_key), val(_val), next(nullptr), prev(nullptr) {}
};

class LRUCache
{
private:
    DLLNode *head;
    DLLNode *tail;
    std::map<int, DLLNode *> mp;
    int capacity;

public:
    // add a node next to head
    void addNode(DLLNode *newNode)
    {
        DLLNode *temp = head->next;
        newNode->next = temp;
        newNode->prev = head;
        head->next = newNode;
        temp->prev = newNode;

        // std::cout << "Added Node with Key: " << newNode->key << ", Value: " << newNode->val << std::endl;
    }

    // deletes the node from the Doubly Linked List
    void deleteNode(DLLNode *delNode)
    {
        DLLNode *delPrev = delNode->prev;
        DLLNode *delNext = delNode->next;
        delPrev->next = delNext;
        delNext->prev = delPrev;

        // std::cout << "Deleted Node with Key: " << delNode->key << ", Value: " << delNode->val << std::endl;
        delete delNode;
    }

    LRUCache(int _capacity) : capacity(_capacity)
    {
        head = new DLLNode(-1, -1);
        tail = new DLLNode(-1, -1);
        head->next = tail;
        tail->prev = head;

        // std::cout << "LRUCache Initialized with Capacity = " << capacity << std::endl;
    }

    int get(int _key)
    {
        // std::cout << "Attempting to Get Key: " << _key << std::endl;
        //  if no match found return -1
        if (mp.find(_key) == mp.end())
        {
            // std::cout << "Key " << _key << " Not Found!" << std::endl;
            return -1;
        }

        // else a match is found, get the element
        // and make it last recently used
        DLLNode *resultantNode = mp[_key];
        int result = resultantNode->val;
        deleteNode(resultantNode);
        // now make a new node, and insert it after the head
        // as last recently used
        DLLNode *newNode = new DLLNode(_key, result);
        addNode(newNode);
        mp[_key] = newNode;
        // std::cout << "Value for Key " << _key << ": " << result << std::endl;
        return result;
    }

    void put(int _key, int _value)
    {
        // std::cout << "Attempting to Put Key: " << _key << ", Value: " << _value << std::endl;
        // if element already exists in the cache, just update
        if (mp.find(_key) != mp.end())
        {
            // std::cout << "Existing Node Update" << std::endl;
            DLLNode *existingNode = mp[_key];
            // delete this node
            deleteNode(existingNode);
            // update the cache
            DLLNode *newNode = new DLLNode(_key, _value);
            addNode(newNode);
            mp[_key] = newNode;
        }
        else if (mp.size() == capacity)
        {
            // remove the least-recently used from the linked list and hashmap
            // if we are to remove it from hashmap, then we also need to store the
            // key value in the DLL
            DLLNode *delNode = tail->prev;
            int delKey = delNode->key;
            // std::cout << "Cache Full. Removing LRU Node with Key: " << delKey << std::endl;
            mp.erase(delKey);
            deleteNode(delNode);
        }

        // now add the new node in the data structures
        DLLNode *newNode = new DLLNode(_key, _value);
        addNode(newNode);
        mp[_key] = newNode;

        // printing the map
        // std::cout << "Updated Map:\n";
        // for (const auto &it : mp) {
        // std::cout << "Key: " << it.first << ", Value: " << it.second->val << std::endl;
        //}
    }
};
