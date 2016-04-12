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
struct test_struct
{
    int nodeValue;
    int nodeID;
    struct test_struct *next;
};

struct test_struct *head = NULL;
struct test_struct *curr = NULL;

/* Creates the head node for the linked list */
struct test_struct* list_start(int nodeID, int nodeValue)
{
    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    ptr->nodeID = nodeID;
    ptr->nodeValue = nodeValue;
    ptr->next = NULL;
    head = curr = ptr;
    return ptr;
}
/* Adds a node to the linked list */
struct test_struct* add_to_list(int nodeID, int nodeValue, bool add_to_end)
{
    if (NULL == head)
    {
        return (list_start(nodeID, nodeValue));
    }

    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    ptr->nodeID = nodeID;
    ptr->nodeValue = nodeValue;
    ptr->next = NULL;

    if (add_to_end)
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
struct test_struct* search_in_list(int nodeID, struct test_struct **prev)
{
    struct test_struct *ptr = head;
    struct test_struct *tmp = NULL;
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
int delete_from_list(int nodeID)
{
    struct test_struct *prev = NULL;
    struct test_struct *del = NULL;
    del = search_in_list(nodeID, &prev);
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
    struct test_struct *ptr = NULL;
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


                if (totalA + i2 > 1024) {
                    for (j = 0; j < i1; j++) {
                        if (dellocArray[j] > i2) {
                            allocArray[j] = i2;
                            idArray[j] = i1;
                            dellocArray[j] = 0;
                            add_to_list(j, totalA, true);
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
                    add_to_list(i1, totalA, true);
                }
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
                ptr = search_in_list(i1, NULL);
                totalD = totalD + allocArray[i1];
                ret = delete_from_list(i1);
                allocArray[i1] = -1;

            }

            break;
        case 'i' :
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
            printf("invalid\n" );
        }


    }
    return 0;
}
