obj-m += ProjectA6.o


ifneq ("$(wildcard $(/lib/modules/4.4.*/build))","")
all:
	make -C /lib/modules/4.4.*/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.4.*/build M=$(PWD) clean
else
all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean

endif



