#include <lua.h>
#define M_SetField(P_ValueExpression,P_Key)\
	P_ValueExpression;\
	lua_setfield(L,-2,P_Key);

#define M_GetField(P_Key)\
	lua_getfield(L,-1,Key);

#define M_SetTable(P_KeyExpression,P_ValueExpression) \
	P_KeyExpression; \
	P_ValueExpression;\
	lua_settable(L,-3);

#define M_GetTable(P_KeyExpression) \
	P_KeyExpression; \
	lua_gettable(L,-2);

#define M_Def_Lua(P_Name) int P_Name(lua_State* L)
#define M_Export_Lua(P_Name) lua_pushcfunction(L,P_Name)
#define M_Def_API(P_Name) M_Def_Lua(Lua_API_##P_Name)
#define M_Export_API(P_Name) M_Export_Lua(Lua_API_##P_Name)
