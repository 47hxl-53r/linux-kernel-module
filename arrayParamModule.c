/*
    I was practicing on LKM programming when i encountered a bug:-

    * When removing a module the goodbye message is not showing in the kernel logs.
    * The "Goodbye linux kernel!" message prints only after re-inserting the module using 'insmod' again.
    * The message becomes visible when i re-insert the module using 'insmod' because, during module
    * insertion, the 'module_init' function is executed first, and then the "Goodbye linux kernel!" message
    * from the previous removal is displayed along with any new messages from the 'module_init' function.


    *** HELP ME FIX THIS ISSUE ***
*/


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

// MODULE METADTA
MODULE_LICENSE("GPL");
MODULE_AUTHOR("P4IN");
MODULE_DESCRIPTION("LKM to get array as param which will display each element to the kernel logs");


// VARIABLE DECLARATIONS
static char *messages[20] = {"defaultMessage"};
module_param_array(messages, charp, NULL, 0);
MODULE_PARM_DESC(messages, "Array seperared by , which will be displayed on kernel logs");


// MODULE INIT FUNCTION
static int init_func(void){
	int i;
	int arraySize = 0;
	for (i = 0; i < ARRAY_SIZE(messages); i++){
		if (messages[i] != NULL){   // COUNTING THE NUMBER OF NON-NULL ELEMENTS IN THE messages ARRAY
			arraySize++;
		}
	}


	for(i = 0; i < arraySize; i++){    // LOGGING OUT EACH ELEMENT FROM THE messages ARRAY
		printk(KERN_INFO "%s\n", messages[i]);
	}
	return 0;
}



// MODULE EXIT - CLEANUP FUNCTION
static void exit_func(void){
	printk(KERN_INFO "Goodbye kernel!");
}


// REGISTERING MODULE INIT AND EXIT FUNCTIONS
module_init(init_func);
module_exit(exit_func);
