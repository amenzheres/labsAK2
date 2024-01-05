#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

struct time_measurement {
    struct list_head list;
    ktime_t start;
    ktime_t end;
};

MODULE_AUTHOR("IO-16 Artem");
MODULE_DESCRIPTION("Lab5");
MODULE_LICENSE("GPL");

static LIST_HEAD(time_list);

static uint amount = 1;
module_param(amount, uint, 0444);
MODULE_PARM_DESC(amount, "An amount parameter");

static int __init my_hello_init(void);
static void __exit my_hello_exit(void);

static int __init my_hello_init(void) {
    uint i = 0;
    struct time_measurement *current_record;

    pr_info("Amount: %d\n", amount);

    BUG_ON(amount > 5);
    
    for (i = 0; i < amount; i++) {
        current_record = kmalloc(sizeof(*current_record), GFP_KERNEL);

        if (!current_record)
            goto error_handle;

        current_record->start = ktime_get();
        pr_info("Hello, Maria!\n");
        current_record->end = ktime_get();

        list_add_tail(&current_record->list, &time_list);
    }

    return 0;

error_handle:
    pr_err("No memory!\n");
    my_hello_exit(); 
    return -ENOMEM;
}

static void __exit my_hello_exit(void) {
    struct time_measurement *temp_record, *safe_record;

    list_for_each_entry_safe(temp_record, safe_record, &time_list, list) {
        pr_info("Execution Time: %lld ns",
        ktime_to_ns(temp_record->end - temp_record->start));

        list_del(&temp_record->list);
        kfree(temp_record);
    }

    BUG_ON(!list_empty(&time_list));
}

module_init(my_hello_init);
module_exit(my_hello_exit);

