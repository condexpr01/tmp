#include "sdl-audio.hpp"
#include <unordered_map>

//{.format = SDL_AUDIO_F32,.channels=2,.freq=44100},
static core::realtime_audio ra;

//audios data, template type args: alias, data
static std::unordered_map<const char*, std::vector<Uint8>> audios;

extern "C"{
	#include <lua.h>
	#include <lauxlib.h>

	//add wav data into audios and set alias
	//2: alias exists
	//1(true): add success
	//0(false): err
	static int load_wav(lua_State *L){
		const char *alias_name = luaL_checkstring(L,1);
		const char *wav_path = luaL_checkstring(L,2);

		auto find = audios.find(alias_name);
		if(find != audios.end()){
			lua_pushinteger(L, true);
			return 1;
		}

		std::vector<Uint8> buf;
		int value = core::load_wav_from_path_and_convert(wav_path, ra.get_dst_spec(), buf);

		if(value == true)audios.emplace(alias_name, buf);
		lua_pushinteger(L, value);
		return 1;
	}

	static int ra_bind(lua_State *L){
		ra.bind();

		lua_pushinteger(L,ra.is_ok());
		lua_pushstring(L,ra.what());
		return 2;
	}

	static int ra_unbind(lua_State *L){
		ra.unbind();

		lua_pushinteger(L,ra.is_ok());
		lua_pushstring(L,ra.what());
		return 2;
	}

	static int ra_play(lua_State *L){

		const char *alias_name = luaL_checkstring(L,1);

		auto find = audios.find(alias_name);
		if(find == audios.end()){
			lua_pushinteger(L,false);
			lua_pushstring(L,"invalid: alias name");
			return 2;
		}

		ra.put_audio_stream_data((*find).second.data(),(*find).second.size());
		lua_pushinteger(L,ra.is_ok());
		lua_pushstring(L,ra.what());
		return 2;
	}

	static int ra_pause(lua_State *L){
		ra.pause();
		return 0;
	}

	static int ra_resume(lua_State *L){
		ra.resume();
		return 0;
	}

	static int ra_reset_status(lua_State *L){
		ra.reset_status();
		return 0;
	}

	static int ra_clear(lua_State *L){
		ra.clear();
		return 0;
	}

	static int ra_get_volume(lua_State *L){
		float v = ra.get_volume();

		lua_pushnumber(L,v);
		return 1;
	}

	static int ra_volume(lua_State *L){
		float gain = luaL_checknumber(L,1);
		ra.volume(gain);
		return 0;
	}

	static int ra_audio_device_name(lua_State *L){
		lua_pushstring(L, ra.audio_device_name());
		return 1;
	}

	struct luaL_Reg reg[] = {
		{"load_wav",load_wav},
		{"ra_bind",ra_bind},
		{"ra_unbind",ra_unbind},
		{"ra_play",ra_play},

		{"ra_reset_status",ra_reset_status},
		{"ra_pause",ra_pause},
		{"ra_resume",ra_resume},
		{"ra_clear",ra_clear},
		{"ra_get_volume",ra_get_volume},
		{"ra_volume",ra_volume},
		{"ra_audio_device_name", ra_audio_device_name},
		{NULL,NULL}
	};

	int luaopen_nvim_audio(lua_State *L){
		luaL_newlib(L, reg);
		return 1;
	}

}

