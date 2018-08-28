#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define IGH_EC_PROC_DIR "ethercat"
#define IGH_EC_PROC_NAME "igh_ec_performance_log"

static int igh_ec_proc_show(struct seq_file *m, void *v);
static int igh_ec_proc_open(struct inode *inode, struct file *file);
static ssize_t igh_ec_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos);
static ssize_t igh_ec_proc_read(struct file *file, char __user *buf, size_t size, loff_t *ppos);
static int igh_ec_proc_init(void);
static void igh_ec_proc_exit(void);

static int igh_ec_proc_show(struct seq_file *m, void *v)
{
	return 0;
}

static int igh_ec_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, igh_ec_proc_show, NULL);
}

u8 data[100];

ssize_t igh_ec_proc_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    int len_copy, ret;
    char data[32] = "1\t2.1\t3.4";

// fl->f_pos表示当前文件描述符对文件的偏移, len表示用户进程想要读的大小

    if ((file->f_pos + len) > strlen(data)) //如果剩下没读的数据长度少于len,则只复制出剩下没读部分
            len_copy = strlen(data) - file->f_pos;
    else
            len_copy = len; //如果剩下的数据长度超出len,则本次复制len字节

    if (len_copy == 0)
        return 0;

    ret = copy_to_user(buf, data+file->f_pos, len_copy);

    //内容复制后，需要改变文件描述符的位置偏移
    *off += len_copy - ret;  //在read/write函数里必须通过off来改变
    printk("================================\n");
    return len_copy - ret;
}

static ssize_t igh_ec_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
    char *tmp = kzalloc((count+1), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;
 
	if (copy_from_user(tmp,buffer,count)) {
		kfree(tmp);
		return -EFAULT;
	}
    printk("%s Get user str :%s\n", __func__, tmp);
	kfree(tmp);
	return count;
}

static struct file_operations igh_ec_proc_fops = {
	.owner	= THIS_MODULE,
	.open	= igh_ec_proc_open,
	.release = single_release,
	.read	= igh_ec_proc_read,
	.llseek	= seq_lseek,
};
struct proc_dir_entry *igh_ec_proc_dir = NULL;
  
static int igh_ec_proc_init(void)
{
	struct proc_dir_entry* file;
    igh_ec_proc_dir = proc_mkdir(IGH_EC_PROC_DIR, NULL);
    if (igh_ec_proc_dir == NULL) {
        printk("%s proc create %s failed\n", __func__, IGH_EC_PROC_DIR);
        return -EINVAL;
    }
	file = proc_create(IGH_EC_PROC_NAME, 0777, igh_ec_proc_dir, &igh_ec_proc_fops);
	if (!file) {
        printk("%s proc_create failed!\n", __func__);
	    return -ENOMEM;
    }

	return 0;
}

static void igh_ec_proc_exit(void)
{
	remove_proc_entry(IGH_EC_PROC_NAME, igh_ec_proc_dir);
	remove_proc_entry(IGH_EC_PROC_DIR, NULL);
}

static int __init my_init(void)
{
    snprintf(data, sizeof(data), "%s", "123456789\t98764321");
    igh_ec_proc_init();

	return 0;
}

static void __exit my_exit(void)
{
    igh_ec_proc_exit();
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("WXY");
MODULE_LICENSE("GPL");

