/****************************************************************************
CIS2750
Assignment 0
Gia Vinh Lam
0925571
An abstract linked list with an iterator
CIS2520 (Fangju Wang)- Looked at my linked list code to refresh my knowledge
****************************************************************************/

#include "LinkedListAPI.h"

char* printFunc(void *toBePrinted){
	return (char*)toBePrinted;
}

//Comparing strings is done by strcmp
int compareFunc(const void *first, const void *second){
	return strcmp((char*)first, (char*)second);
}

//Freeing a string is also straightforward
void deleteFunc(void *toBeDeleted){
	free(toBeDeleted);
}

int main()
{
    List list = initializeList(&printFunc, &deleteFunc, &compareFunc);
    insertBack(&list, "test3");
    insertFront(&list, "test");
    //insertFront(&list, "testbefore");
    //insertFront(&list, "testbeforetestbefore");
    //insertFront(&list, "testbeforetestbeforetestbefore");
    insertBack(&list, "test2");
    //insertBack(&list, "testafter2");
    //insertBack(&list, "testaftertestafter2");
    //insertFront(&list, "INTRO");
    //printf("%s\n", toString(list));
    //printf("head %s and tail %s\n", (char*)getFromFront(list), (char*)getFromBack(list));
    //clearList(&list);
    printf("%s\n", toString(list));
    ListIterator iter = createIterator(list);
    printf("next element %s\n", (char*)nextElement(&iter));
    printf("next element %s\n", (char*)nextElement(&iter));
    printf("next element %s\n", (char*)nextElement(&iter)); 
    //clearList(&list);
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
    //node->data = malloc(sizeof(data));
    if (node == NULL)
    {
        printf("Memory allocation has failed in function initializeNode. Program exiting.\n");
        exit(0);
    }

    if (node == NULL || data == NULL)
    {
        printf("Data is null.\n");
        return NULL;
    }
    else
    {
        node->data = data;
        //strcpy((char*)node->data, (char*)data);
        //printf("data %s and node data %s\n", (char*)data, (char*)node->data);
        node->previous = NULL;
        node->next = NULL;
        return node;
    }
}


void insertFront(List * list, void * toBeAdded)
{
    Node * newNode = initializeNode(toBeAdded);
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    else
    {
        list->head->previous = newNode;
        newNode->next = list->head;
        newNode->previous = NULL;
        list->head = newNode;
    }
    return;
}



void insertBack(List * list, void * toBeAdded)
{
    Node * newNode = initializeNode(toBeAdded);
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    else
    {
        list->tail->next = newNode;
        newNode->previous = list->tail;
        newNode->next = NULL;
        list->tail = newNode;
    }
    return;
}


void clearList(List* list)
{
    Node * temp = list->head;
    while (temp->next != NULL)
    {
        free(temp->data);
        temp = temp->next;
    }
    free(list->tail);
    return;
}

/*
void insertSorted(List* list, void* toBeAdded)
{
    Node * temp = list->head;
    Node * tempPrevious = NULL;
    Node * newNode = initializeNode(toBeAdded);
    while (temp->next != NULL)
    {
        if (list->compare(list->head->data, toBeAdded) <= 0)
        {
            //
        }
        else
        {

        }
    }
    return;
}
*/

/*
void* deleteDataFromList(List* list, void* toBeDeleted)
{
    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        return;
    }
}
*/

void * getFromFront(List list)
{
    if (list.head == NULL)
    {
        return NULL;
    }
    return list.head->data;
}


void * getFromBack(List list)
{
    if (list.tail == NULL)
    {
        return NULL;
    }
    return list.tail->data;
}

char * toString(List list)
{
    List temp = list;
    char * listData;
    int amount = 0;

    while (temp.head != NULL)
    {
        amount = amount + strlen(printFunc(temp.head->data))+3;
        temp.head = temp.head->next;
    }

    listData = malloc(sizeof(char*) * amount);
    while (list.head != NULL)
    {
        listData = strcat(listData, printFunc(list.head->data));
        listData = strcat(listData, " ");
        list.head = list.head->next;
    }
    return listData;
}

ListIterator createIterator(List list)
{
    ListIterator iter;

    if (list.head != NULL)
    {
        iter.current = list.head;
    }
    return iter;
}


void * nextElement(ListIterator * iter)
{
    void * element;
    Node * temp;
    if (iter != NULL)
    {
//printf("lit\n");
        temp = iter->current;
printf("string %s\n", (char*)iter->current);
        element = temp;
        iter->current = iter->current->next;
printf("string %s check\n", (char*)element);
    }
    return element;
}
