#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kfifo.h>
#include <linux/list.h>
#include <linux/ioctl.h>

#define IOCTL_DISPLAY_LOG _IOR('p', 1, struct data_log *)

struct data_log {
    struct list_head list;
    char type[5]; 
    size_t length;
};

static LIST_HEAD(data_list);

static int pchar_open(struct inode *, struct file *);
static int pchar_close(struct inode *, struct file *);
static ssize_t pchar_read(struct file *, char *, size_t, loff_t *);
static ssize_t pchar_write(struct file *, const char *, size_t, loff_t *);
static long pchar_ioctl(struct file *, unsigned int, unsigned long);

#define MAX 32
static struct kfifo buf;
static int major;
static dev_t devno;
static struct class *pclass;
static struct cdev cdev;
static struct file_operations pchar_fops = {
    .owner = THIS_MODULE,
    .open = pchar_open,
    .unlocked_ioctl = pchar_ioctl,
    .release = pchar_close,
    .read = pchar_read,
    .write = pchar_write
};

static __init int pchar_init(void) {
    int ret, minor;
    struct device *pdevice;
    
    printk(KERN_INFO "%s: pchar_init() called.\n", THIS_MODULE->name);
    ret = kfifo_alloc(&buf, MAX, GFP_KERNEL);
    if(ret != 0) {
        printk(KERN_ERR "%s: kfifo_alloc() failed.\n", THIS_MODULE->name);
        goto kfifo_alloc_failed;
    }
    printk(KERN_INFO "%s: kfifo_alloc() successfully created device.\n", THIS_MODULE->name);

    ret = alloc_chrdev_region(&devno, 0, 1, "pchar");
    if(ret != 0) {
        printk(KERN_ERR "%s: alloc_chrdev_region() failed.\n", THIS_MODULE->name);
        goto alloc_chrdev_region_failed;
    }
    major = MAJOR(devno);
    minor = MINOR(devno);
    printk(KERN_INFO "%s: alloc_chrdev_region() allocated device number %d/%d.\n", THIS_MODULE->name, major, minor);

    pclass = class_create(THIS_MODULE, "pchar_class");
    if(IS_ERR(pclass)) {
        printk(KERN_ERR "%s: class_create() failed.\n", THIS_MODULE->name);
        ret = -1;
        goto class_create_failed;
    }
    printk(KERN_INFO "%s: class_create() created device class.\n", THIS_MODULE->name);

    pdevice = device_create(pclass, NULL, devno, NULL, "pchar%d", 0);
    if(IS_ERR(pdevice)) {
        printk(KERN_ERR "%s: device_create() failed.\n", THIS_MODULE->name);
        ret = -1;
        goto device_create_failed;
    }
    printk(KERN_INFO "%s: device_create() created device file.\n", THIS_MODULE->name);

    cdev_init(&cdev, &pchar_fops);
    ret = cdev_add(&cdev, devno, 1);  
    if(ret != 0) {

        printk(KERN_ERR "%s: cdev_add() failed to add cdev in kernel db.\n", THIS_MODULE->name);
        goto cdev_add_failed;
    }
    
    printk(KERN_INFO "%s: cdev_add() added device in kernel db.\n", THIS_MODULE->name);

    return 0;
cdev_add_failed:
    device_destroy(pclass, devno);
device_create_failed:
    class_destroy(pclass);
class_create_failed:
    unregister_chrdev_region(devno, 1);
alloc_chrdev_region_failed:
    kfifo_free(&buf);
kfifo_alloc_failed:
    return ret;
}

static __exit void pchar_exit(void) {
    struct data_log *entry, *tmp;
    list_for_each_entry_safe(entry, tmp, &data_list, list) 
    {
        list_del(&entry->list);
        kfree(entry);
    }
    printk(KERN_INFO "%s: pchar_exit() called.\n", THIS_MODULE->name);
    cdev_del(&cdev);
    printk(KERN_INFO "%s: cdev_del() removed device from kernel db.\n", THIS_MODULE->name);
    device_destroy(pclass, devno);
    printk(KERN_INFO "%s: device_destroy() destroyed device file.\n", THIS_MODULE->name);
    class_destroy(pclass);
    printk(KERN_INFO "%s: class_destroy() destroyed device class.\n", THIS_MODULE->name);
    unregister_chrdev_region(devno, 1);
    printk(KERN_INFO "%s: unregister_chrdev_region() released device number.\n", THIS_MODULE->name);
    kfifo_free(&buf);
    printk(KERN_INFO "%s: kfifo_free() destroyed device.\n", THIS_MODULE->name);
}


static int pchar_open(struct inode *pinode, struct file *pfile) {
    printk(KERN_INFO "%s: pchar_open() called.\n", THIS_MODULE->name);
    return 0;
}

static int pchar_close(struct inode *pinode, struct file *pfile) {
    printk(KERN_INFO "%s: pchar_close() called.\n", THIS_MODULE->name);
    return 0;
}

static ssize_t pchar_read(struct file *pfile, char *ubuf, size_t len, loff_t *poffset) 
{
    struct data_log *new_log;
    new_log = kmalloc(sizeof(struct data_log), GFP_KERNEL);
    printk(KERN_INFO "%s: pchar_read() called.\n", THIS_MODULE->name);

    strcpy(new_log->type, "read");
    new_log->length = len;
    INIT_LIST_HEAD(&new_log->list);
    list_add_tail(&new_log->list, &data_list);
    
    printk(KERN_INFO "Read operation recorded\n");
    return len;
}

static ssize_t pchar_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poffset) 
{
    struct data_log *new_log;
    printk(KERN_INFO "%s: pchar_write() called.\n", THIS_MODULE->name);
    new_log = kmalloc(sizeof(struct data_log), GFP_KERNEL);

    strcpy(new_log->type, "write");
    new_log->length = size;
    INIT_LIST_HEAD(&new_log->list);
    list_add_tail(&new_log->list, &data_list);
   
    printk(KERN_INFO "Write operation recorded\n");
    return size;
}

static long pchar_ioctl(struct file *file, unsigned int cmd, unsigned long arg) 
{
    struct data_log *entry;
    if (cmd == IOCTL_DISPLAY_LOG) {
        list_for_each_entry(entry, &data_list, list) {
            printk(KERN_INFO "Type: %s, Length: %zu", entry->type, entry->length);
        }
    }
    return 0;
}
module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shashank Ingle <shashank227421@gmail.com>");
MODULE_DESCRIPTION("Simple pchar driver with kfifo as device.");
