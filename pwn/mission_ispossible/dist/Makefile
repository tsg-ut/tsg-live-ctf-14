obj-m += misp.o
PWD := $(CURDIR)
SRC := /path/to/linux-6.12.9
all:
	make -C $(SRC) M=$(PWD) modules
clean:
	make -C $(SRC) M=$(PWD) clean
