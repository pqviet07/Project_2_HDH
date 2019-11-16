#include "myrandom.h"
static int    majorNumber;                  
static char   message[256] = {0};          
static short  size_of_message;           
static int    numberOpens = 0;          
static struct class*  myrandomClass  = NULL;
static struct device* myrandomDevice = NULL; 

static int     my_open(struct inode *, struct file *);
static int     my_release(struct inode *, struct file *);
static ssize_t my_read(struct file *, char *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char *, size_t, loff_t *);



static struct file_operations fops =
{
   .open = my_open,
   .read = my_read,
   .write = my_write,
   .release = my_release,
};


static int myrandom_init(void)
{
    
   
   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk("EBBChar failed to register a major number\n");
      return majorNumber;
   }
   printk("EBBChar: registered correctly with major number %d\n", majorNumber);

  
   myrandomClass = class_create(THIS_MODULE, CLASS_NAME);
   
   if (IS_ERR(myrandomClass)){               
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk("Failed to register device class\n");
      return PTR_ERR(myrandomClass);        
   }
   printk("EBBChar: device class registered correctly\n");

   
   myrandomDevice = device_create(myrandomClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(myrandomDevice)){               
      class_destroy(myrandomClass);        
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk("Failed to create the device\n");
      return PTR_ERR(myrandomDevice);
   }
   printk("EBBChar: device driver created correctly\n"); 
   
    int a = myrandom();

    printk("Khoi tao thanh cong %d\n", a);
    return 0;
}

static void myrandom_exit(void)
{
     device_destroy(myrandomClass, MKDEV(majorNumber, 0));     
     class_unregister(myrandomClass);                          
     class_destroy(myrandomClass);                             
     unregister_chrdev(majorNumber, DEVICE_NAME);          
    printk("Ket thuc thanh cong111\n");
}

int myrandom()
{
    int randNumber = get_random_int();
    return randNumber;
}


static int my_open(struct inode *inodep, struct file *filep){
   printk("MYRANDOM: Mo file device thanh cong!\n");
   return 0;
}

static ssize_t my_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;

  
    sprintf(message, "%d", myrandom());

	error_count = copy_to_user(buffer, message, strlen(message));
   if (error_count==0){           
     
      return (size_of_message=0); 
   }
   else {
     
      return -EFAULT;          
   }
}

static ssize_t my_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   return len;
}

static int my_release(struct inode *inodep, struct file *filep){
   printk("MYRANDOM: Thoat khoi Device thanh cong\n");
   return 0;
}

module_init(myrandom_init);
module_exit(myrandom_exit);