/*****************************************************************************
CIS2750
Assignment 0
Gia Vinh Lam
0925571
An abstract linked list with an iterator (function details in LinkedListAPI.h)
CIS2520 (Fangju Wang) - Looked at my linked list code to refresh my knowledge
*****************************************************************************/

//need to test functions when list isnt initialized or no node in there

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
    insertFront(&list, "apple");
    insertBack(&list, "wrap");
    insertSorted(&list, "test");
    //insertBack(&list, "test3");
    //insertFront(&list, "test");
    //insertBack(&list, "test2");

    printf("%s\n", toString(list));
//    ListIterator iter = createIterator(list);
//    printf("next element %s\n", (char*)nextElement(&iter));
//    printf("next element %s\n", (char*)nextElement(&iter));
//    printf("next element %s\n", (char*)nextElement(&iter));
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


//a w
void insertSorted(List* list, void* toBeAdded)
{
    Node * tempPrevious = NULL;
    Node * newNode = initializeNode(toBeAdded);

    if (newNode == NULL)
    {
        printf("Data is null. Unable to insert element.\n");
        return;
    }

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    while (list->head != NULL)
    {
        if (list->compare(list->head->data, toBeAdded) <= 0) //indicates str1 is less than or equal to str2. In the ASCII table, B and a is less than A
        {
            if (list->head->next == NULL) // If there is only one node currently... ex. New Node: B, Old Node: A
            {
                list->head->next = newNode;
                newNode->previous = list->head;
                newNode->next = NULL;
                list->tail = newNode;
                return;
            }
            list->head->next->previous = newNode;
            newNode->next = list->head->next->previous;
            list->head->next = newNode;
            newNode->previous = list->head->next;
printf("wat2\n");
            return;
        }
        else
        { // (D, C) A
            if (list->head->next == NULL)
            {
                list->head->previous = newNode;
                newNode->previous = NULL;
                newNode->next = list->head;
                list->head = newNode;
                return;
            }
printf("wat3\n");
            list->head = list->head->next;
            //tempPrevious->next = newNode;
            //list->head
        }
        //tempPrevious = list->head;
        //list->head = list->head->next;
    }
    return;
}

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
        temp = iter->current;
        element = temp->data;
        iter->current = iter->current->next;
    }
    return element;
}
