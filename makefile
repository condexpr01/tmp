all:
	gcc -fPIC -shared -I/usr/include/luajit-2.1 src/testlib.c -o lua/testlib.so -lluajit-5.1

clean:
	-rm ./lua/testlib.so
