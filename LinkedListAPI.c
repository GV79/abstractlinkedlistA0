/*****
CIS2750
Assignment 0
Gia Vinh Lam
0925571
An abstract linked list with an iterator
CIS2520 (Fangju Wang)
- Looked at my linked list code to refresh my knowledge
*****/

#include "LinkedListAPI.h"

int main()
{
//    List * list;
//    list = initializeList(&printFunction, &deleteFunction, &compareFunction);
    return 0;
}

List initializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second))
{
    List list;
    list.head = NULL;
    list.tail = NULL;
    list.deleteData = deleteFunction;
    list.compare = compareFunction;
    list.printData = printFunction;
    return list;
}

Node * initializeNode(void * data)
{
    Node * node = malloc(sizeof(Node));
    node->data = malloc(sizeof(data));

    if (node == NULL || data == NULL)
    {
        return NULL;
    }
    else
    {
        strcpy((char *)node->data, (char *)data);
        node->previous = NULL;
        node->next = NULL;
        return node;
    }
}


void insertFront(List* list, void* toBeAdded)
{
    Node * temp;
    temp = (Node *)toBeAdded;
    list->head->previous = temp;
    temp->next = list->head;
    temp->previous = NULL;
    //(List)toBeAdded->next = list;
    //(List)toBeAdded->previous = NULL;
    return;
}



void insertBack(List* list, void* toBeAdded)
{
    Node * temp;
    temp = (Node *)toBeAdded;
    list->tail->next = temp;
    temp->previous = list->tail;
    temp->next = NULL;
    list->tail = temp;
    //temp->next = NULL;
    //temp->previous = list;
    return;
}


void clearList(List* list)
{
    Node * temp = list->head;
    while (temp->next != NULL)
    {
        free(list->head->data);
        temp = temp->next;
    }
    free(list->tail);
    return;
}


void insertSorted(List* list, void* toBeAdded)
{
    Node * temp = list->head;
    if (list->compare(list->head->data, toBeAdded) >= 0)
    {

    }
    return;
}


/*
void* deleteDataFromList(List* list, void* toBeDeleted)
{
    return;
}

void* getFromFront(List list)
{
    return;
}

void* getFromBack(List list)
{
    return;
 }
*/

