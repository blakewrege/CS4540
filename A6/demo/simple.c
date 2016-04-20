#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
/* This function is called when the module is loaded. */
int simple_init(void)
{
 printk(KERN INFO "HELLO WORLD\n");
return 0;
}
/* This function is called when the module is removed. */
void simple_exit(void)
{
 printk(KERN INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */
module init(simple_init);
module exit(simple_exit);
