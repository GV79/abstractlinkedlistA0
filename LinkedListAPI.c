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
    insertFront(&list, "test");
    printf("%s\n", toString(list));
    //free(list);
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
printf("thingsarehappening\n");
        strcpy((char *)node->data, (char *)data);
        node->previous = NULL;
        node->next = NULL;
        return node;
    }
}


void insertFront(List * list, void * toBeAdded)
{
    //Node * temp = list;
//    if (list == NULL)
//    {
//        return NULL;
//    }
    Node * newNode = initializeNode(toBeAdded);
    if (list->head == NULL)
    {
printf("firstnode\n");
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    else
    {
        if (list->head->next == NULL)
        {
            list->head->previous = newNode;
            newNode->next = list->head;
            newNode->previous = NULL;
            list->tail = list->head;
            list->head = newNode;
            //list
        }
        else
        {
            list->head->previous = newNode;
            newNode->next = list->head;
            newNode->previous = NULL;
            list->head = newNode;
        }
    }
    //list->head
    //newNode->previous = NULL;
    //(List)toBeAdded->next = list;
    //(List)toBeAdded->previous = NULL;
    return;
}



void insertBack(List * list, void * toBeAdded)
{
    //Node * temp = list;
    Node * newNode = initializeNode(toBeAdded);
    list->tail->next = newNode;
    newNode->previous = list->tail;
    newNode->next = NULL;
    list->tail = newNode;
    //temp->next = NULL;
    //temp->previous = list;
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
    int lengthStrings = 0;
    List temp = list;
    while (temp.head != NULL)
    {
        lengthStrings = strlen((char*)list.head->data) + 3 + lengthStrings; // +3 for comma, space, and null terminator.
        temp.head = temp.head->next;
    }

    char * dataAllocated = malloc(sizeof(char) * lengthStrings);
    while (list.head != NULL)
    {
        strcat(dataAllocated, strcat((char*)list.head->data, " "));
        list.head = list.head->next;
    }
    return dataAllocated;
}

/*
ListIterator createIterator(List list)
{

}
*/

/*
void * nextElement(ListIterator * iter)
{

}
*/
