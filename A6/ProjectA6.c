/*************************************************
 * * Course: CS 4540 – Spring 2016
 * * Assignment 5 - Program 1
 * * Name: Blake Wrege
 * * E-mail: blake.j.wrege@wmich.edu
 * * Submitted: 4/11/2016
 * *************************************************/



#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernal Linked List");
MODULE_AUTHOR("Blake Wrege");

struct Student {
    unsigned int studentNumber;
    unsigned int courseCredit;
    unsigned int grade;
    struct list_head list; /* kernel's list structure */
};

struct Student studentList;

int test_start(void) {
    struct Student *addNewStudent, *aStudent;
    unsigned int i;

    printk(KERN_INFO "Loading Module\n");
    INIT_LIST_HEAD(&studentList.list);

    /* adding elements to mylist */
    for (i = 0; i < 6; ++i) {
        addNewStudent = kmalloc(sizeof(*addNewStudent), GFP_KERNEL);
        addNewStudent->studentNumber = 760120495;
        addNewStudent->courseCredit = 130 * i;
        addNewStudent->grade = 1 + i;
        INIT_LIST_HEAD(&addNewStudent->list);
        /* add the new node to the list */
        list_add_tail(&(addNewStudent->list), &(studentList.list));
    }
    printk(KERN_INFO "traversing the list using list_for_each_entry()n");
    list_for_each_entry(aStudent, &studentList.list, list) {
        //access the member from aStudent
        printk(KERN_INFO "student number: %d; course credit: %d; grade: %d", aStudent->studentNumber, aStudent->courseCredit, aStudent->grade);
    }
    return 0;

}



void test_exit(void)
{
    printk(KERN_INFO "Removing Module\n");
    struct Student *aStudent, *tmp;
    /* freeing nodes from list */
    list_for_each_entry_safe(aStudent, tmp, &studentList.list, list) {
        list_del(&aStudent->list);
        kfree(aStudent);
    }



}

module_init(test_start);
module_exit(test_exit);