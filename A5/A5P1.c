#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct test_struct
{
    int nodeValue;
    int nodeID;
    struct test_struct *next;
};

struct test_struct *head = NULL;
struct test_struct *curr = NULL;

struct test_struct* create_list(int nodeID, int nodeValue)
{
    printf("\n creating list with headnode as [%d]\n", nodeID);
    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if (NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->nodeID = nodeID;
    ptr->nodeValue = nodeValue;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

struct test_struct* add_to_list(int nodeID, int nodeValue, bool add_to_end)
{
    if (NULL == head)
    {
        return (create_list(nodeID, nodeValue));
    }

    if (add_to_end)
        printf("\n Adding node to end of list with value [%d]\n", nodeID);
    else
        printf("\n Adding node to beginning of list with value [%d]\n", nodeID);

    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if (NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
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

struct test_struct* search_in_list(int nodeID, struct test_struct **prev)
{
    struct test_struct *ptr = head;
    struct test_struct *tmp = NULL;
    bool found = false;

    printf("\n Searching the list for node [%d] \n", nodeID);

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

int delete_from_list(int nodeID)
{
    struct test_struct *prev = NULL;
    struct test_struct *del = NULL;

    printf("\n Deleting value [%d] from list\n", nodeID);

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

void print_list(void)
{
    struct test_struct *ptr = head;

    printf("\n -------Printing list Start------- \n");
    while (ptr != NULL)
    {
        printf("\n [%d][%d] \n", ptr->nodeID, ptr->nodeValue);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}

int main(void)
{
    FILE *fp;
    int k;
    int i1, i2, totalA, totalD;
    int allocArray[50];
    char line[80];
    char test;
    totalA = 0;
    totalD = 0;
    int i = 0, ret = 0;
    struct test_struct *ptr = NULL;
    fp = fopen("CS4540-A5-App1.txt", "r");
    while (1) {
        if (fgets(line, 150, fp) == NULL) break;
        k++;
        test = line[1];
//       printf("%3d: %c", i, test);

        /* 'l' is for allocating, 'e' is for deallocate, 'i' is for display */
        switch (test) {
        case 'l' :
            if (2 == sscanf(line,
                            "%*[^0123456789]%d%*[^0123456789]%d", &i1, &i2))
            {
                allocArray[i1] = i2;
//                printf("%d %d\n", i1, allocArray[i1]);
                totalA = totalA + i2;
                add_to_list(i1, i2, true);
            }
            break;
        case 'e' :
            if (1 == sscanf(line, "%*[^0123456789]%d", &i1))
            {
//              printf("%d\n", i1);
                //     ptr = search_in_list(i, NULL);
                //     ptr = search_in_list(i1, NULL);
                //     if (NULL == ptr)
                //     {
                //         printf("\n Search [node value = %d] failed, no such element found\n", i1);
                //     }
                //     else
                //     {
                //         printf("\n Search passed [node value = %d]\n", ptr->nodeValue);
                //     }

                ret = delete_from_list(i1);
                if (ret != 0)
                {
                    printf("\n delete [node value = %d] failed, no such element found\n", i1);
                }
                else
                {
                    printf("\n delete [node value = %d]  passed \n", i1);
                }


            }
            totalD = totalD + i1;





            break;
        case 'i' :
//            printf("You passed\n" );
            break;
        default :
            printf("Invalid grade\n" );
        }


    }
    printf("\n%d %d\n", totalA, totalD);

    print_list();

    // int i = 0, ret = 0;
    // struct test_struct *ptr = NULL;

    // print_list();

    // for(i = 5; i<10; i++)
    //     add_to_list(i,true);

    // print_list();

    // for(i = 4; i>0; i--)
    //     add_to_list(i,false);

    // print_list();

    // for(i = 1; i<10; i += 4)
    // {
    //     ptr = search_in_list(i, NULL);
    //     if(NULL == ptr)
    //     {
    //         printf("\n Search [nodeID = %d] failed, no such element found\n",i);
    //     }
    //     else
    //     {
    //         printf("\n Search passed [nodeID = %d]\n",ptr->nodeID);
    //     }

    //     print_list();

    //     ret = delete_from_list(i);
    //     if(ret != 0)
    //     {
    //         printf("\n delete [nodeID = %d] failed, no such element found\n",i);
    //     }
    //     else
    //     {
    //         printf("\n delete [nodeID = %d]  passed \n",i);
    //     }

    //     print_list();
    // }

    return 0;
}