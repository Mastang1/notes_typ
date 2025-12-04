nclude <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DemoUser");
MODULE_DESCRIPTION("A Simple Hello World Module");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello: Module loaded successfully.\n");
        return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Hello: Module unloaded.\n");
}

module_init(hello_init);
module_exit(hello_exit);
