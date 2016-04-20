#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>

typedef struct list_head list;
typedef struct student *ptr;
typedef struct student *studentDemo;
static LIST_HEAD(student_list);
struct student{
 int studentNumber;
 int courseCredit;
 int grade;
 struct list_head list;
};
struct student *studentDemo;
studentDemo = kmalloc(sizeof(*studentDemo), GFP KERNEL);
studentDemo->studentNumber = 760120495;
studentDemo->courseCredit = 3;
studentDemo->grade = 5;
INIT_LIST_HEAD(&studentDemo->list);

list_add_tail(&studentDemo->list, &student_list);


struct student *ptr;
list_for_each_entry(ptr, &student_list, list) {
 /* on each iteration ptr points */
 /* to the next student struct */
}

struct student *ptr, *next
list for_each_entry_safe(ptr, next, &student_list, list) {
 /* on each iteration ptr points */
 /* to the next student struct */
- 5 -
 list_del(&ptr->list);
 kfree(ptr);
} 
