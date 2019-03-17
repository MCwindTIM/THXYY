#include "LuaEngine.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <Common\THCommon.h>
#include <Common\THException.h>
#include <Common\THExceptionManager.h>
#include <iostream>
#include "LuaBinder.h"

#include "LuaBindDetail.h"

namespace THEngine
{
	Ptr<LuaEngine> LuaEngine::Create()
	{
		LuaEngine* ptr = (LuaEngine*)std::malloc(sizeof(LuaEngine));
		new (ptr) LuaEngine();
		Ptr<LuaEngine> luaEngine = Ptr<LuaEngine>::Create_NoRetain(ptr);

		luaEngine->_L = luaL_newstate();
		luaL_openlibs(luaEngine->_L);

		luaEngine->RegisterBuiltIn();

		return luaEngine;
	}

	LuaEngine::~LuaEngine()
	{
	}

	void LuaEngine::Shutdown()
	{
		lua_close(_L);
	}

	bool LuaEngine::RunCode(const std::string& code, const std::string& codeName)
	{
		int error;
		if (error = luaL_loadbuffer(_L, code.c_str(), code.size(), codeName.c_str())
			|| lua_pcall(_L, 0, 0, 0))
		{
			// get error file and line number
			lua_Debug ar;
			lua_getstack(_L, 1, &ar);
			lua_getinfo(_L, "nSl", &ar);

			String error = (String)"[SCRIPT ERROR] In file " + ar.source + ":\n" + lua_tostring(_L, -1);
			lua_pop(_L, 1);
			THLog(error);
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(error));
			return false;
		}

		return true;
	}

	bool LuaEngine::RunScript(const String& filePath)
	{
		/*sol::state_view lua(_L);

		std::string path = filePath.ToStdString();
		sol::protected_function_result lr = lua.script_file(path);
		if (!lr.valid())
		{
			sol::error err = lr;
			std::string what = err.what();
			String error = (String)"************SCRIPT ERROR*************" + "\n" + what.c_str();
			THLog(error);
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(error));
			return false;
		}
		return true;*/

		if (luaL_dofile(_L, filePath.ToStdString().c_str()))
		{
			String error = (String)"************SCRIPT ERROR*************" + "\n" + lua_tostring(_L, -1);
			lua_pop(_L, 1);
			THLog(error);
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(error));
			return false;
		}

		return true;
	}
}