obj-m := test_proc.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules #注意前面必须为tab
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
