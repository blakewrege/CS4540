#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("hello");
MODULE_AUTHOR("Liu Feipeng/roman10");
 
struct student {
    int studentNumber;
    unsigned int courseCredit;
    unsigned int grade;
    struct list_head list; /* kernel's list structure */
};
 
struct student studentList;
 
int init_module() {
    struct student *newStudent, *studentDemo;
    unsigned int i;
 
    printk(KERN_INFO "Loading module...\n");
    INIT_LIST_HEAD(&studentDemo.list);    //or LIST_HEAD(mylist); 
        struct student *ptr, *next;
    /* adding elements to mylist */
    for(i=0; i<5; ++i){
        newStudent = kmalloc(sizeof(*newStudent), GFP_KERNEL);
        studentDemo->studentNumber = 760120495;
        newStudent->courseCredit = 130*i;
        newStudent->grade = 1;
        INIT_LIST_HEAD(&newStudent.list);
        /* add the new node to mylist */
        list_add_tail(&(newStudent->list), &(studentList.list));
    }
    printk(KERN_INFO "traversing the list using list_for_each_entry()n");
    list_for_each_entry(studentDemo, &studentList.list, list) {
        //access the member from studentDemo
        printk(KERN_INFO "Student:%d  Course Credit %d Grade %d", studentDemo->studentNumber, studentDemo->courseCredit, studentDemo->grade);
    }
    printk(KERN_INFO "n");
 
    return 0;
}
 
void cleanup_module() {
    struct student *studentDemo, *tmp;
    printk(KERN_INFO "kernel module unloaded.n");
    printk(KERN_INFO "deleting the list using list_for_each_entry_safe()n");
    list_for_each_entry_safe(studentDemo, tmp, &studentList.list, list){
         printk(KERN_INFO "freeing node %d", studentDemo->studentNumber);
         list_del(&studentDemo->list);
         kfree(studentDemo);
    }
}