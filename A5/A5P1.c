/*************************************************
 * * Course: CS 4540 – Spring 2016
 * * Assignment 5 - Program 1
 * * Name: Blake Wrege
 * * E-mail: blake.j.wrege@wmich.edu
 * * Submitted: 4/11/2016
 * *************************************************/




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


/* Struct for storing nodes */
struct nodeStruct
{
    int nodeValue;
    int nodeID;
    struct nodeStruct *next;
};

struct nodeStruct *head = NULL;
struct nodeStruct *curr = NULL;

/* Creates the head node for the linked list */
struct nodeStruct* listStart(int nodeID, int nodeValue)
{
    struct nodeStruct *ptr = (struct nodeStruct*)malloc(sizeof(struct nodeStruct));
    ptr->nodeID = nodeID;
    ptr->nodeValue = nodeValue;
    ptr->next = NULL;
    head = curr = ptr;
    return ptr;
}
/* Adds a node to the linked list */
struct nodeStruct* listAdd(int nodeID, int nodeValue, bool onEnd)
{
    if (NULL == head)
    {
        return (listStart(nodeID, nodeValue));
    }

    struct nodeStruct *ptr = (struct nodeStruct*)malloc(sizeof(struct nodeStruct));
    ptr->nodeID = nodeID;
    ptr->nodeValue = nodeValue;
    ptr->next = NULL;

    if (onEnd)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}
/* Searches for node in list to make sure that it exists */
struct nodeStruct* listSearch(int nodeID, struct nodeStruct **prev)
{
    struct nodeStruct *ptr = head;
    struct nodeStruct *tmp = NULL;
    bool found = false;

    while (ptr != NULL)
    {
        if (ptr->nodeID == nodeID)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if (true == found)
    {
        if (prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}
/* Deletes node in list when called on */
int listDel(int nodeID)
{
    struct nodeStruct *prev = NULL;
    struct nodeStruct *del = NULL;
    del = listSearch(nodeID, &prev);
    if (del == NULL)
    {
        return -1;
    }
    else
    {
        if (prev != NULL)
            prev->next = del->next;

        if (del == curr)
        {
            curr = prev;
        }
        else if (del == head)
        {
            head = del->next;
        }
    }
    free(del);
    del = NULL;

    return 0;
}


int main(void)
{
    FILE *fp;
    int k, j, d, loc;
    int i1, i2, totalA, totalD;
    int blockStart = 0;
    int blockEnd = 0;
    int idArray[50];
    int blocksArray[50];
    int allocArray[50];
    int dellocArray[50];
    for (d = 0; d < 50; d++) {
        idArray[d] = 0;
        allocArray[d] = 0;
        blocksArray[d] = 0;
        dellocArray[d] = 0;
    }

    bool fits;
    char line[80];
    char test;
    totalA = 0;
    totalD = 0;
    int i = 0, ret = 0;
    loc = 0;
    struct nodeStruct *ptr = NULL;
    fp = fopen("CS4540-A5-App1.txt", "r");
    while (1) {
        fits = true;
        if (fgets(line, 150, fp) == NULL) break;
        k++;
        test = line[1];

        /* 'l' is for allocating, 'e' is for deallocate, 'i' is for display */
        switch (test) {
        case 'l' :
            if (2 == sscanf(line,
                            "%*[^0123456789]%d%*[^0123456789]%d", &i1, &i2))
            {

                /* Checks for free space and tries to allocate memory to a location */
                if (totalA + i2 > 1024) {
                    for (j = 0; j < i1; j++) {
                        if (dellocArray[j] > i2) {
                            allocArray[j] = i2;
                            idArray[j] = i1;
                            dellocArray[j] = 0;
                            listAdd(j, totalA, true);
                            fits = true;
                            break;

                        } else {
                            fits = false;
                        }
                    }
                } else {
                    totalA = totalA + i2;
                    blocksArray[loc] = totalA;
                    loc++;
                    allocArray[i1] = i2;
                    idArray[i1] = i1;
                    listAdd(i1, totalA, true);
                }
                /* Displays an error if memory can't be allocated */
                if (fits == false) {
                    printf("\n Error: node %d is over 1024 bytes \n", i1 );
                }
                fits = true;
            }
            break;
        case 'e' :
            if (1 == sscanf(line, "%*[^0123456789]%d", &i1))
            {
                dellocArray[i1] = allocArray[i1];
                ptr = listSearch(i1, NULL);
                totalD = totalD + allocArray[i1];
                ret = listDel(i1);
                allocArray[i1] = -1;

            }

            break;
        case 'i' :
            /* Prints out each Node in its location within the 1024 bytes of space */
            for (d = 0; d < 50; d++) {
            }
            printf("\n   -------Printing list Start------- \n");
            printf("| Location | ID | Size | Start | End  |");

            for (d = 0; d < 50; d++) {
                if (allocArray[d] > 0) {
                    /* Comparisons to fix errors around end nodes */
                    if (d == 0) {
                        blockStart = 0;
                    } else {
                        blockStart = blocksArray[d - 1];
                    }
                    if (blockStart == 1023 ) {
                        blockStart = blocksArray[d - 2];
                        blockEnd = blocksArray[d - 1];
                    } else {
                        blockEnd = blocksArray[d];
                    }


                    printf("\n|    %02d    | %02d |  %02d  |  %04d | %04d |", d, idArray[d], allocArray[d], blockStart, blockEnd);
                }
            }
            printf("\n    -------Printing list End------- \n");
            break;
        default :
            printf("invalid line\n" );
        }


    }
    return 0;
}
