/**
 * Copyright (c) 2006-2013 LOVE Development Team
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

#include "common/config.h"

#include "wrap_Keyboard.h"

#include "sdl/Keyboard.h"

namespace love
{
namespace keyboard
{

static Keyboard *instance;

int w_isDown(lua_State *L)
{
	Keyboard::Key k;
	unsigned int num = lua_gettop(L);
	Keyboard::Key *keylist = new Keyboard::Key[num+1];
	unsigned int counter = 0;

	for (unsigned int i = 0; i < num; i++)
	{
		if (Keyboard::getConstant(luaL_checkstring(L, i+1), k))
			keylist[counter++] = k;
	}
	keylist[counter] = Keyboard::KEY_MAX_ENUM;

	luax_pushboolean(L, instance->isDown(keylist));
	delete[] keylist;
	return 1;
}

int w_setKeyRepeat(lua_State *L)
{
	if (lua_gettop(L) == 0)
	{
		// Disables key repeat.
		instance->setKeyRepeat(0, 0);
		return 0;
	}

	int delay = lua_isnumber(L, 1) ? (int)(lua_tonumber(L, 1) * 1000 + 0.5) : Keyboard::DEFAULT;
	int interval = lua_isnumber(L, 2) ? (int)(lua_tonumber(L, 2) * 1000 + 0.5) : Keyboard::DEFAULT;
	instance->setKeyRepeat(delay, interval);
	return 0;
}

int w_getKeyRepeat(lua_State *L)
{
	lua_pushnumber(L, (lua_Number) instance->getKeyRepeatDelay() * 0.001);
	lua_pushnumber(L, (lua_Number) instance->getKeyRepeatInterval() * 0.001);
	return 2;
}

// List of functions to wrap.
static const luaL_Reg functions[] =
{
	{ "isDown", w_isDown },
	{ "setKeyRepeat", w_setKeyRepeat },
	{ "getKeyRepeat", w_getKeyRepeat },
	{ 0, 0 }
};

extern "C" int luaopen_love_keyboard(lua_State *L)
{
	if (instance == 0)
	{
		try
		{
			instance = new love::keyboard::sdl::Keyboard();
		}
		catch(Exception &e)
		{
			return luaL_error(L, e.what());
		}
	}
	else
		instance->retain();

	WrappedModule w;
	w.module = instance;
	w.name = "keyboard";
	w.flags = MODULE_T;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

} // keyboard
} // love
