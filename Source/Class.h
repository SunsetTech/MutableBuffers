#pragma once
#include "MutableBuffer.h"
#include <lua.h>

int MutableBuffer_Class_AttachMetamethods(lua_State* L);
int MutableBuffer_Class_Destructor(lua_State* L);
