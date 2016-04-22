obj-m += ProjectA6.o

all:
	make -C /lib/modules/4.4.*/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.4.*/build M=$(PWD) clean
