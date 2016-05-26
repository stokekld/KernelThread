#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>

struct task_struct *task;

int hilo_function(void *data)
{
	printk(KERN_INFO "Hilo:: Ejecutando hilo\n");
	while(1)
	{
		printk(KERN_INFO "Hilo:: Saludos desde funcion del hilo\n");
		schedule();
	}
	return 0;
}

int hilo_init(void)
{
	int data = 100;
	printk(KERN_INFO "Hilo:: Se cargo el modulo\n");
	task = kthread_run(&hilo_function,(void *) &data,"Hilo");
	return 0;
}

void hilo_cleanup(void)
{
	kthread_stop(task);
    printk(KERN_INFO "Hilo:: Se libero el modulo\n");
}

module_init(hilo_init);
module_exit(hilo_cleanup);