#include <linux/errno.h>
#include <linux/init_task.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cred.h>
#include <linux/lsm_hooks.h>
#include <linux/sysctl.h>
#include <linux/lsm_hooks.h>
static unsigned long long count = 0;

int demo_task_create(unsigned long clone_flags)
{
    printk("[+geek] call task_create(). count=%llu\n", ++count);    
    return 0;
}

int demo_file_open(struct file *file, const struct cred *cred)
{
	printk(" call file_open(),uid =%d gid =%d \n",cred->uid,cred->gid);

	return 0;
}

static struct security_hook_list demo_hooks[] = {
    LSM_HOOK_INIT(task_create,demo_task_create),
    LSM_HOOK_INIT(file_open,demo_file_open),
};
void __init demo_add_hooks(void)
{
    pr_info("Demo: becoming mindful.\n");        //打印相关信息，可以通过dmesg |  grep Yama:查看
    security_add_hooks(demo_hooks, ARRAY_SIZE(demo_hooks),"task_create_lsm");   //添加安全模块函数
}

static __init int demo_init(void){
    demo_add_hooks();
    return 0;
}

security_initcall(demo_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sqhxhg@sbs.com.cn");
MODULE_DESCRIPTION("watch the task struct");
