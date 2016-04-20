obj-m += ProjectA6.o

all:
	make -C /lib/modules/4.2.0-35-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.2.0-35-generic/build M=$(PWD) clean
