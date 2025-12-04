# 1. 核心变量：告诉内核构建系统，我们要编译 hello.o 为模块
obj-m += hello.o

# 2. 定义内核源码路径
# 如果是在 PC 上测试，通常是这个路径
# 如果是嵌入式开发，这里需要替换为你解压好的 Linux Kernel 源码路径
KDIR := /lib/modules/$(shell uname -r)/build

# 3. 获取当前目录路径
PWD := $(shell pwd)

# 4. 默认目标
all:
	# 核心指令：
	# -C $(KDIR): 切换到内核源码目录，读取那里的 Makefile
	# M=$(PWD):   告诉内核，要构建的外部模块在哪里
	# modules:    执行构建模块的目标
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# 5. 清理目标
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean