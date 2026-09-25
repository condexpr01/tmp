
dylib_out="lua/libnvim-audio.so"
link_option="-lluajit-5.1"
include_option="-I/usr/include/luajit-2.1"
src_code="src/audio-impl.cpp"


all: compile

compile:
	g++ -fPIC -shared ${src_code} ${include_option} -o ${dylib_out} ${link_option}

clean:
	-rm ./lua/testlib.so

.PHONY: all compile clean
