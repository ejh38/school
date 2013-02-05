/*****************************
 *	Zach Sadler - zps6
 *	Project 4
 *	Tu/Th 11AM section
 *****************************/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>

#include <asm/uaccess.h>

#include "e.h"								// so we can get the digits of e


static char *digits;					// where we'll store what we get from e.h
static int digits_len = 0;		// keeps track of how many digits we have

static ssize_t e_driver_read(struct file *file, char *buf, 
			  size_t count, loff_t *ppos)
{
	int last_digit = count + *ppos;		// the last digit we'll need
	int i; 	// for loops
	int j;	// for loops
	char e_driver_str[count];					// where we'll store the output

	printk(KERN_DEBUG "I'm asked to make %d and I have %d\n", last_digit, digits_len);

	if (count < 0) {		// this should be stopped by e_digits
		printk(KERN_DEBUG "This text should never be seen.\n");
		return -EINVAL;
	}

	if (last_digit > digits_len) {		// if we need to generate more digits
		printk(KERN_DEBUG "So I need more digits\n");
		if (digits_len != 0) {		// check if digits already has been MALLOC'd
			printk(KERN_DEBUG "Have to free the old one\n");
			FREE(digits);						// if so then FREE it
		}
		digits = MALLOC(last_digit);		// and then re-MALLOC for more space
		digits_len = last_digit;				// and set digits_len to the new length
	
		e(digits, last_digit);					// get the 0-last_digit digits of e
		printk(KERN_DEBUG "Now we have enough space\n");
	}

	if (last_digit <= digits_len) {
		printk(KERN_DEBUG "We already have enough digits to handle their request.\n");
	}

	// now we need to do the actual seperating and giving them their substring
	for (i = *ppos, j = 0; i <= last_digit; i++, j++) {
		e_driver_str[j] = digits[i];	// copy the correct digits to the beginning
	}
	printk(KERN_DEBUG "Finished copying the substring\n");


	if (copy_to_user(buf, e_driver_str, count)) {
		printk(KERN_DEBUG "The copy_to_user was false\n");
		return -EINVAL;
	}

	// shift the cursor to the last_digit we have
	*ppos = last_digit;

	return count;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations e_driver_fops = {
	.owner	= THIS_MODULE,
	.read		= e_driver_read,
};

static struct miscdevice e_driver_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/e_driver.
	 */
	"e_driver",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&e_driver_fops
};

static int __init
e_driver_init(void)
{
	int ret;

	/*
	 * Create the "e_driver" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/e_driver device using
	 * the default rules.
	 */
	ret = misc_register(&e_driver_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"e_driver!\" misc device\n");

	return ret;
}

module_init(e_driver_init);

static void __exit
e_driver_exit(void)
{
	misc_deregister(&e_driver_dev);
}

module_exit(e_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zach Sadler - zps6@pitt.edu");
MODULE_DESCRIPTION("\"e_driver!\" minimal module");
MODULE_VERSION("dev");
