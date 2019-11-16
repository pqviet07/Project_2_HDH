#ifndef _MY_RANDOM_H
#define _MY_RANDOM_H
#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function
#include <linux/random.h>
#define  DEVICE_NAME "myrandom"    ///< The device will appear at /dev/ebbchar using this value
#define  CLASS_NAME  "myrandom"        ///< The device class -- this is a character device driver

MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Tham khao nguon cua tac gia _ Derek Molloy");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("Project 2 HDH");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            ///< A version number to inform users


int myrandom(void); //My random
#endif