#include "lua-5.2/lua.hpp"
#include <cstring>

static int hello(lua_State *VM)
{
	int arg_count = lua_gettop(VM);
	if(arg_count==1)
	{
		const char* arg=lua_tostring(VM, 1);
		if(memcmp(arg, "S;G", 4)==0) lua_pushstring(VM, "PhoenixTempleEvilTruth");
		else lua_pushstring(VM, "Oh, you must be CERN's spy...");
	}
	else
	{
		lua_pushstring(VM, "Hello World!");
	}
	return 1;
}

int main()
{
	lua_State *virtual_machine = luaL_newstate();
	luaL_openlibs(virtual_machine);

	lua_register(virtual_machine, "say_hello", hello);

	luaL_dofile(virtual_machine, "okabe.lua");

	lua_close(virtual_machine);
	return 0;
}
