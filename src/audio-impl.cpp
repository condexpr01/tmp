#include <lua.h>
#include <lauxlib.h>
#include "sdl-audio.hpp"

//{.format = SDL_AUDIO_F32,.channels=2,.freq=44100},
static core::realtime_audio ra;

std::vector<uint8_t> buf;

extern "C"{

	static int ra_bind(lua_State *L){
		ra.bind();
		return 0;
	}

	static int ra_unbind(lua_State *L){
		ra.unbind();
		return 0;
	}

	static int ra_play(lua_State *L){
		if(buf.empty()){
			buf.reserve(44100);
			core::write_buf_sin_wave<float>((float*)buf.data(), buf.size(), 2, 44100, 440);
		}

		ra.put_audio_stream_data(buf.data(),buf.size());
		return 0;
	}

	struct luaL_Reg reg[] = {
		{"ra_bind",ra_bind},
		{"ra_unbind",ra_unbind},
		{"ra_play",ra_play},
		{NULL,NULL}
	};

	int luaopen_testlib(lua_State *L){
		luaL_newlib(L, reg);
		return 1;
	}

}
