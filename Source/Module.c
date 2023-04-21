#include <lua-compat-5.3/compat-5.3.h>
#include "LuaAPI.h"
#include <LuaMacros/Macros.h>
#include <Lua_StructBind/StructBind.h>

int luaopen_MutableBuffer(lua_State* L) {
	StructBind_Init(L);
	lua_newtable(L);
		M_SetField(M_Export_API(MutableBuffer_New),"New");
		M_SetField(M_Export_API(MutableBuffer_Read),"Read");
		M_SetField(M_Export_API(MutableBuffer_Write),"Write");
		M_SetField(M_Export_API(MutableBuffer_Size),"Size");
		M_SetField(M_Export_API(MutableBuffer_Capacity),"Capacity");
	return 1;
}

