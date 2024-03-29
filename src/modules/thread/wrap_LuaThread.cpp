/**
 * Copyright (c) 2006-2010 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#include "wrap_LuaThread.h"

namespace love
{
namespace thread
{

LuaThread *luax_checkthread(lua_State *L, int idx)
{
	return luax_checktype<LuaThread>(L, idx, "Thread", THREAD_THREAD_T);
}

int w_Thread_start(lua_State *L)
{
	LuaThread *t = luax_checkthread(L, 1);
	luax_pushboolean(L, t->start());
	return 1;
}

int w_Thread_wait(lua_State *L)
{
	LuaThread *t = luax_checkthread(L, 1);
	t->wait();
	return 0;
}

int w_Thread_getError(lua_State *L)
{
	LuaThread *t = luax_checkthread(L, 1);
	std::string err = t->getError();
	if (err.length() == 0)
		lua_pushnil(L);
	else
		luax_pushstring(L, err);
	return 1;
}

static const luaL_Reg type_functions[] = {
	{ "start", w_Thread_start },
	{ "wait", w_Thread_wait },
	{ "getError", w_Thread_getError },
	{ 0, 0 }
};

extern "C" int luaopen_thread(lua_State *L)
{
	return luax_register_type(L, "Thread", type_functions);
}

} // thread
} // love
