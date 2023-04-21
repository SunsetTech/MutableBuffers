#include <lua-compat-5.3/compat-5.3.h>
#include <stdlib.h>
#include "Class.h"
#include "LuaAPI.h"
#include <Lua_StructBind/StructBind.h>
#include <lauxlib.h>

int MutableBuffer_Class_MT_Index(lua_State* L) {
	M_Userdata_Metamethod_Index_GetArgs(aaa)
	if M_IsKey("Read") {
		M_Export_API(MutableBuffer_Read);
		return 1;
	}
	if M_IsKey("Write") {
		M_Export_API(MutableBuffer_Write);
		return 1;
	}
	if M_IsKey("Size") {
		M_Export_API(MutableBuffer_Size);
		return 1;
	}
	if M_IsKey("Capacity") {
		M_Export_API(MutableBuffer_Capacity);
		return 1;
	}
	return 0;
}

int MutableBuffer_Class_AttachMetamethods(lua_State* L) {
	M_SetField(lua_pushcfunction(L,MutableBuffer_Class_MT_Index),"__index");
	return 0;
}

int MutableBuffer_Class_Destructor(lua_State* L) {
	StructBind_Userdata* Userdata = lua_touserdata(L,1);
	MutableBuffer* Buffer = Userdata->Info.Address;
	M_Print("Freeing mutable buffer data");
	free(Buffer->Data);
	if (!Userdata->Info.IsNative) {
		M_Print("Freeing mutable buffer");
		free(Buffer);
	}
	return 0;
}
