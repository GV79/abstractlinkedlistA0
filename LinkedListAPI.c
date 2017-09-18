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
    insertFront(&list, "upple");
    insertBack(&list, "wrap");
    insertSorted(&list, "test");
    insertSorted(&list, "kangaroo");
    insertSorted(&list, "oompa");
    insertSorted(&list, "zebra");
    deleteDataFromList(&list, "zebra");
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
        //list->tail->next = newNode;
        newNode->previous = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        list->tail->next = NULL;
    }
    return;
}

void clearList(List* list)
{
    Node * temp = list->head;
    while (temp->next != NULL)
    {
        deleteFunc(temp);
        temp = temp->next;
    }
    deleteFunc(list->tail);
    return;
}

void insertSorted(List* list, void* toBeAdded)
{
    Node * newNode = initializeNode(toBeAdded);
    //List temp = *list;
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
            if (list->head == list->tail) // If there is only one node currently... ex. New Node: B, Old Node: A
            {
                list->head->next = newNode;
                newNode->previous = list->head;
                newNode->next = NULL;
                list->tail = newNode;

                while (list->head->previous != NULL)
                {
                    list->head = list->head->previous;
                }
                return;
            }

            if (list->compare(list->head->next->data, toBeAdded) >= 0)
            {
                newNode->next = list->head->next;
                newNode->previous = list->head;
                list->head->next->previous = newNode;
                list->head->next = newNode;
                while (list->head->previous != NULL)
                {
                    list->head = list->head->previous;
                }
                return;
            }
        }
        else
        {
            list->head->previous = newNode;
            newNode->previous = NULL;
            newNode->next = list->head;
            list->head = newNode;
            return;
        }
        //list->tail = list->tail->previous;
//printf("wtf\n");
        list->head = list->head->next;
        //list->tail = list->tail->previous;
    }
    return;
}


void* deleteDataFromList(List* list, void* toBeDeleted)
{
    void *dataDeleted = toBeDeleted;
    //List * temp = list;
    void * temp;

printf("hello1\n");
    if (list == NULL)
    {
        printf("List does not exist.\n");
        return NULL;
    }
    else
    {
printf("hello2\n");
        //List * temp = list;
        while (list->head != NULL)
        {
printf("hello3\n");
            if (compareFunc(list->head->data, toBeDeleted) == 0)
            {
                if (list->head->previous == NULL)
                {
                    list->head->next->previous = NULL;
                    list->head = list->head->next;
                    list->head = list->head->next;
                    deleteFunc(list->head);
                    return dataDeleted;
                }
                else if (list->head->next == NULL)
                {
                    list->head->previous->next = NULL;
                    list->tail = list->head->previous;
                    temp = list->head;
                    while (list->head->previous != NULL)
                    {
                        list->head = list->head->previous;
                    }
                    free(temp2);
                    return dataDeleted;
                }
                else
                {
                    list->head->previous->next = list->head->next;
                    list->head->next->previous = list->head->previous;
                    deleteFunc(list->head);
                    return dataDeleted;
                }
            }
            list->head = list->head->next;
        }
        printf("Unable to find/delete the node\n");
        return NULL;
    }
}


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
    void * storage;
    if (iter->current != NULL)
    {
        storage = iter->current->data;
        iter->current = iter->current->next;
        return storage;
    }
    return NULL;
}
