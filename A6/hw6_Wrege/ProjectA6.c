#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/list.h>



struct student {
	int studentNumber;
	int courseCredit;
	int grade;
	struct list_head list;
};

struct student studentList;


static LIST_HEAD(student_list);


static int __init hello_start(void) {
	printk(KERN_INFO "Loading module...\n");
	printk(KERN_INFO "Hello world\n");
	int i;
	struct student *studentDemo, newStudents;
	INIT_LIST_HEAD(&studentDemo.list);
		struct student *ptr, *next;
for(i=0; i<5; ++i){
	studentDemo = kmalloc(sizeof(*studentDemo), GFP_KERNEL);
	studentDemo->studentNumber = 760120495;
	studentDemo->courseCredit = 3;
	studentDemo->grade = 5+i;
	INIT_LIST_HEAD(&newStudents.list);
	list_add_tail(&(studentDemo->list), &(student_list));
}


	void list_del(struct list_head * element);


	list_for_each_entry(ptr, &student_list, list) {

		printk(KERN_INFO "Student:%d  Course Credit %d Grade %d", studentDemo->studentNumber, studentDemo->courseCredit, studentDemo->grade);

	}






	list for_each_entry_safe(ptr, next, &student_list, list) {

		/* on each iteration ptr points */

		/* to the next student struct */

		list_del(&ptr->list);

		kfree(ptr);

	}



	return 0;
}


//int main()
//{
//struct student *studentDemo;
//studentDemo = kmalloc(sizeof(*studentDemo), GFP_KERNEL);
//studentDemo->studentNumber = 760120495;
//studentDemo->courseCredit = 3;
//studentDemo->grade = 5;
//INIT_LIST_HEAD(&studentDemo->list);
//}




static void __exit hello_end(void)
{
	printk(KERN_INFO "Removing Module\n");
}
module_init(hello_start);
module_exit(hello_end);
MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Simple Module");

MODULE_AUTHOR("SGG");
