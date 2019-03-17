#include "LuaEngine.h"
#include <Core\THGame.h>
#include <Core\THScene.h>
#include <iostream>
#include <sstream>

#include "LuaBindDetail.h"

/*static void add_file_and_line(lua_State* L)
{
	lua_Debug d;
	lua_getstack(L, 1, &d);
	lua_getinfo(L, "Sln", &d);
	std::string err = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::stringstream msg;
	msg << d.short_src << ":" << d.currentline;

	if (d.name != 0)
	{
		msg << "(" << d.namewhat << " " << d.name << ")";
	}
	msg << " " << err;
	lua_pushstring(L, msg.str().c_str());
}*/

static void on_error_callback(lua_State* L)
{
	lua_Debug d;
	lua_getstack(L, 1, &d);
	lua_getinfo(L, "Sln", &d);
	std::string err = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::stringstream msg;
	msg << d.short_src << ":" << d.currentline;

	if (d.name != 0)
	{
		msg << "(" << d.namewhat << " " << d.name << ")";
	}
	msg << " " << err;
	lua_pushstring(L, msg.str().c_str());
}

namespace THEngine
{
	/*struct Lua_Game_Wrapper : Game, luabind::wrap_base
	{
		virtual void Update() { call<void>("update"); }
		static void default_update(Game* ptr) { return ptr->Game::Update(); }

		virtual void Draw() { call<void>("Draw"); }
		static void default_draw(Game* ptr) { return ptr->Game::Draw(); }
	};*/

	BEGIN_LUABIND_WRAPPER(Game)
		DECLARE_NO_PARAM_METHOD(Game, update, Update)
		DECLARE_NO_PARAM_METHOD(Game, draw, Draw)
		DECLARE_NO_PARAM_METHOD(Game, onShutdown, OnShutdown)
		DECLARE_NO_PARAM_METHOD(Game, onEnterBackground, OnEnterBackground)
		DECLARE_NO_PARAM_METHOD(Game, onReturnToForeground, OnReturnToForeground)
	END_LUABIND_WRAPPER()

	BEGIN_LUABIND_WRAPPER(Scene)
		DECLARE_NO_PARAM_METHOD(Scene, update, Update)
	END_LUABIND_WRAPPER()

	void LuaEngine::RegisterBuiltIn()
	{
		// set_pcall_callback(add_file_and_line);

		set_error_callback(on_error_callback);

		open(_L);

		module(_L)[
			class_<Game, bases<>, Ptr<Game>, Lua_Game_Wrapper>("Game")
			    .def(constructor<>())
			    .scope[
				    def("getInstance", &Game::GetInstance)
			    ]
				BIND_CALLBACK(Game, update, Update)
				BIND_CALLBACK(Game, draw, Draw)
				BIND_CALLBACK(Game, onShutdown, OnShutdown)
				BIND_CALLBACK(Game, onEnterBackground, OnEnterBackground)
				BIND_CALLBACK(Game, onReturnToForeground, OnReturnToForeground)
			    .def("quit", &Game::Quit)
			    .def("loadScene", &Game::LoadScene),

			class_<Scene, bases<>, Ptr<Scene>, Lua_Scene_Wrapper>("Scene")
				.def(constructor<>())
				BIND_CALLBACK(Scene, update, Update)
		];
	}
}