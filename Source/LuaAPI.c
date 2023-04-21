#include <lua-compat-5.3/compat-5.3.h>
#include "LuaAPI.h"
#include "MutableBuffer.h"
#include "Class.h"
#include <Lua_StructBind/StructBind.h>
#include <lauxlib.h>

M_Def_API(MutableBuffer_New) {
	size_t InitialCapacity = 32;
	if (!lua_isnoneornil(L,1)) {
		InitialCapacity = luaL_checkinteger(L,1);
	}
	
	StructBind_Userdata_Settings Settings;
		Settings.IsOwnable = false;
		Settings.IsReferenceable = true;
		Settings.IsConst = false;
		Settings.Copy = NULL;
		Settings.Modify = NULL;
		Settings.Destroy = MutableBuffer_Class_Destructor;
	
	StructBind_Userdata* Userdata = StructBind_Wrap_Allocate(
		L,sizeof(MutableBuffer),
		StructBind_Allocator_FromUserdata,
		MutableBuffer_Class_AttachMetamethods,
		Settings
	);
	MutableBuffer_Init(Userdata->Info.Address,InitialCapacity);

	return 1;
}

M_Def_API(MutableBuffer_Read) {
	StructBind_Userdata* Userdata = lua_touserdata(L,1);
	MutableBuffer* Buffer = Userdata->Info.Address;
	
	size_t From = 0;
	if (!lua_isnoneornil(L,2)) {
		From = luaL_checkinteger(L,2) - 1;
	}

	size_t To = Buffer->Size - 1;
	if (!lua_isnoneornil(L,3)) {
		To = luaL_checkinteger(L,3) - 1;
	}
	
	const char* ReadBuffer = MutableBuffer_Read(Buffer,&From,&To,false);
	size_t Length = (To-From)+1;
	lua_pushlstring(L,ReadBuffer,Length);
	
	return 1;
}

M_Def_API(MutableBuffer_Write) {
	StructBind_Userdata* Userdata = lua_touserdata(L,1);
	MutableBuffer* Buffer = Userdata->Info.Address;
	
	size_t Length;
	const char* WriteBuffer = luaL_checklstring(L,2,&Length);
	
	size_t Position = Buffer->Size;
	if (!lua_isnoneornil(L,3)) {
		Position = luaL_checkinteger(L,3) - 1;
	}

	bool Success = MutableBuffer_Write(Buffer,&Position,WriteBuffer,Length);
	lua_pushboolean(L,Success);
	lua_pushinteger(L,Position);
	
	return 2;
}

M_Def_API(MutableBuffer_Size) {
	StructBind_Userdata* Userdata = lua_touserdata(L,1);
	MutableBuffer* Buffer = Userdata->Info.Address;
	lua_pushinteger(L,Buffer->Size);
	return 1;
}

M_Def_API(MutableBuffer_Capacity) {
	StructBind_Userdata* Userdata = lua_touserdata(L,1);
	MutableBuffer* Buffer = Userdata->Info.Address;
	lua_pushinteger(L,Buffer->Capacity);
	return 1;
}
