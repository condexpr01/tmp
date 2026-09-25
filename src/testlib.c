#include <lua.h>
#include <lauxlib.h>

static int func_add(lua_State *L){
	double a = luaL_checknumber(L,1);
	double b = luaL_checknumber(L,2);

	lua_pushnumber(L, a+b);

	return 1;
}

struct luaL_Reg reg[] = {
	{"add",func_add},
	{NULL,NULL}
};

int luaopen_testlib(lua_State *L){
	luaL_newlib(L, reg);
	return 1;
}
