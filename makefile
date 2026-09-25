all:
	gcc -fPIC -shared -I/usr/include/luajit-2.1 testlib.c -o testlib -lluajit-5.1
