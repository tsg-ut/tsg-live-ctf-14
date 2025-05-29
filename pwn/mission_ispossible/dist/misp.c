#include <linux/timekeeping.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("caphosra");

#define MISP_REGISTER 0x100
#define MISP_READ 0x101

#define MISP_MAX_MSG 0x40
#define MISP_MSG_SIZE 0x20

struct misp_msg {
    char msg[MISP_MSG_SIZE];
};

struct misp_msg_req {
    char msg[MISP_MSG_SIZE];
    unsigned char idx;
};

static struct misp_msg* msg_data[MISP_MAX_MSG];
static u64 time_limits[MISP_MAX_MSG];

static long misp_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    struct misp_msg_req req;
    u64 current_time = ktime_get_ns();

    pr_info("MISSION: IS POSSIBLE");

    if (copy_from_user(&req, (void __user *)arg, sizeof(req)))
        return -EFAULT;

    if (req.idx < 0 || req.idx >= MISP_MAX_MSG)
        return -EINVAL;

    switch (cmd) {
        case MISP_REGISTER:
            if (msg_data[req.idx] == NULL) {
                msg_data[req.idx] = kmalloc(sizeof(struct misp_msg), GFP_KERNEL);
                if (msg_data[req.idx] == NULL)
                    return -ENOMEM;
            }
            if (time_limits[req.idx] != 0) {
                if (current_time > time_limits[req.idx]) {
                    pr_info("Cannot rewrite the outdated message.");
                    return -EINVAL;
                }
            }

            memcpy(msg_data[req.idx]->msg, req.msg, MISP_MSG_SIZE);
            time_limits[req.idx] = 0;

            return 0;
        case MISP_READ:
            if (msg_data[req.idx] == NULL)
                return -EINVAL;

            if (time_limits[req.idx] == 0) {
                pr_info("This message will self-destruct in 5 seconds!");
                time_limits[req.idx] = current_time + 5000000000;
            }

            char* msg;
            if (current_time > time_limits[req.idx])
                msg = "Boom!";
            else
                msg = msg_data[req.idx]->msg;

            if (copy_to_user((void __user *)arg, msg, MISP_MSG_SIZE))
                return -EFAULT;
            kfree(msg_data[req.idx]);

            if (current_time > time_limits[req.idx]) {
                pr_info("Boom! The message has been deleted permanently.");
                msg_data[req.idx] = NULL;
                time_limits[req.idx] = 0;
            }

            return 0;
        default:
            return -EINVAL;
    }
}

static const struct file_operations misp_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = misp_ioctl,
    .compat_ioctl = misp_ioctl,
};

static struct miscdevice misp_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "misp",
    .fops = &misp_fops,
};

static int __init misp_init(void){
    if (misc_register(&misp_device) < 0)
        return -1;

    for (int i = 0; i < MISP_MAX_MSG; i++) {
        msg_data[i] = NULL;
        time_limits[i] = 0;
    }

    return 0;
}

static void __exit misp_exit(void){
    misc_deregister(&misp_device);
}

module_init(misp_init);
module_exit(misp_exit);
