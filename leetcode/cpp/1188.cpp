#include <bits/stdc++.h>
using namespace std;

/*
The problem is about creating a data structure which is a bounded blocking queue with thread-safety in mind. A bounded blocking queue is a queue with a fixed maximum size, and it has the capability to block or wait when operations like enqueue (adding to the queue) and dequeue (removing from the queue) cannot be performed because the queue is full or empty, respectively. The queue supports three main operations:

    enqueue(int element): This method adds an element to the end of the queue. If the queue has reached its capacity, the method should block the calling thread until there is space available to add the new element.
    dequeue(): This removes and returns the element at the front of the queue. If the queue is empty, this operation should block until there is an element available to dequeue.
    size(): This returns the current number of elements in the queue.

It is especially noted that the implementation will be tested in a multithreaded environment, where multiple threads could be calling these methods simultaneously. Therefore, it is crucial that the implementation ensures that all operations on the bounded blocking queue are thread-safe (i.e., function correctly when accessed from multiple threads).
*/