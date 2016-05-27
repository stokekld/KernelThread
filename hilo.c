#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>

// task struct para el hilo de kernel
struct task_struct *task;

// Funcion que ejecutara el hilo
int hilo_function(void *data)
{
	printk(KERN_INFO "Hilo:: Ejecutando hilo\n");
	while(!kthread_should_stop())
	{
		schedule();
	}
	return 0;
}

// Inicio del modulo
int hilo_init(void)
{

	int data = 100;
	printk(KERN_INFO "Hilo:: Se cargo el modulo\n");

	// Inicio de hilo de kernel
	task = kthread_run(&hilo_function,(void *) &data,"Hilo");
	return 0;
}

// Salida del modulo
void hilo_cleanup(void)
{
	// tarminando el modulo
	kthread_stop(task);
    printk(KERN_INFO "Hilo:: Se libero el modulo\n");
}

// Especificando las funciones de inicio y fin del modulo
module_init(hilo_init);
module_exit(hilo_cleanup);