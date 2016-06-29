#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/timer.h>

// task struct para el hilo de kernel
struct task_struct *task;

// timer
struct timer_list timer_example;

// variable auxiliar para realizar funcion timer
int done = 0;

//funcion del timer
void timer_function(unsigned long data)
{
	printk(KERN_INFO "Hilo:: Ejecutando Temporizador %lu\n", jiffies);
	done = 1;
}

// Funcion que ejecutara el hilo
int hilo_function(void *data)
{
	printk(KERN_INFO "Hilo:: Ejecutando hilo\n");

	// configurando timer para 10 segundos
	timer_example.function = timer_function;
	timer_example.expires  = jiffies + 10 * HZ;
	timer_example.data     = (unsigned long) 100;
	add_timer(&timer_example);

	while(!kthread_should_stop())
	{
		// si no se ha hecho la funcion
		// no modifica el timer
		if (done)
		{
			mod_timer(&timer_example, jiffies + 10 * HZ);
			done = 0;
		}

		schedule();
	}
	return 0;
}

// Inicio del modulo
int hilo_init(void)
{

	int data = 100;
	printk(KERN_INFO "Hilo:: Se cargo el modulo\n");

	// iniciando el timer
	init_timer(&timer_example);

	// Inicio de hilo de kernel
	task = kthread_run(&hilo_function,(void *) &data,"Hilo");
	return 0;
}

// Salida del modulo
void hilo_cleanup(void)
{
	// terminando el modulo

	kthread_stop(task);
	
	// eliminando el timer
	del_timer(&timer_example);


    printk(KERN_INFO "Hilo:: Se libero el modulo\n");
}

// Especificando las funciones de inicio y fin del modulo
module_init(hilo_init);
module_exit(hilo_cleanup);