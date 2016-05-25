#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

int hilo_init(void)
{
	printk(KERN_INFO "Se cargo mi module\n");
	return 0;
}

void hilo_cleanup(void)
{
    printk(KERN_INFO "Se libero mi module\n");
}

module_init(hilo_init);
module_exit(hilo_cleanup);