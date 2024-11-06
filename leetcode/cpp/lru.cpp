#include <bits/stdc++.h>
using namespace std;

class DLLNode{
public:
    int data;
    DLLNode *next;
    DLLNode *prev;
};
class LRUCache{
    private:
    map<int,DLLNode*> values;
    int capacity;
    DLLNode *head;
    DLLNode *tail;
    LRUCache(int n){
        capacity = n;
        head=nullptr;
        tail=nullptr;
    }
}
