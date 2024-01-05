// SPDX-License-Identifier: GPL-2-Clause
#include <hello1.h>

MODULE_AUTHOR("IO-16 Artem");
MODULE_DESCRIPTION("Lab4");
MODULE_LICENSE("GPL");

static uint amount = 1;

module_param(amount, uint, 0);
MODULE_PARM_DESC(amount, "Parameter for lab work 4 execution count\n");

static int __init start_hello_module(void)
{
    pr_info("hello2 module starting\n");
    print_hello(amount);
    return 0;
}

static void __exit end_hello_module(void)
{
    pr_info("hello2 module exiting\n");
}

module_init(start_hello_module);
module_exit(end_hello_module);

