/**
 * Given a stack s, delete the middle element of the stack without 
 * using any additional data structure.
 * 
 * Middle element:- floor((size_of_stack+1)/2) (1-based indexing) 
 * from the bottom of the stack.
 * Note: The output shown by the compiler is the stack from top to 
 * bottom.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

Node* createNode(int data){
    Node* newNode = (Node* )(malloc(sizeof(Node)));
    if(newNode==NULL){
        printf("Memory Allocation Failed\n");
        return NULL;
    }
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
}
DoublyLinkedList* createDoublyLinkedList(){
    DoublyLinkedList* newDLL = (DoublyLinkedList*)(malloc(sizeof(DoublyLinkedList*)));
    if(newDLL==NULL){
        printf("[DLL]: Memory Allocation Failed\n");
        return NULL;
    }
    initList(newDLL);
    return newDLL;
}
void initList(DoublyLinkedList* DLL){
    DLL->head = NULL;
    DLL->tail = NULL;
    DLL->size = 0;
}

void insertAtBeginning(DoublyLinkedList* DLL, int data){
    Node* newNode = createNode(data);
    if(newNode==NULL){
        return;
    }
    
    if(DLL->head==NULL){
        DLL->head = newNode;
        DLL->tail = newNode;
        DLL->size=1;
    }else{
        newNode->right = DLL->head;
        DLL->head->left = newNode;
        DLL->head = newNode;
        DLL->size++;
    }
}

void insertAtEnd(DoublyLinkedList* DLL, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    if (DLL->tail == NULL) {
        // Empty list
        DLL->head = newNode;
        DLL->tail = newNode;
        DLL->size=1;
    } else {
        newNode->left = DLL->tail;
        DLL->tail->right = newNode;
        DLL->tail = newNode;
        DLL->size++;
    }
}