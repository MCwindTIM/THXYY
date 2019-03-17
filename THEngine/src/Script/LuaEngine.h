#pragma once

#include <Common/THObject.h>
#include <Common\THPtr.h>
#include <Common\THString.h>

struct lua_State;

namespace THEngine
{
	class LuaEngine : public Object
	{
	public:
		static Ptr<LuaEngine> Create();

		~LuaEngine();

		void Shutdown();
		bool RunCode(const std::string& code, const std::string& codeName = "");
		bool RunScript(const String& filePath);

	private:
		LuaEngine() = default;

		void RegisterBuiltIn();

	private:
		lua_State * _L = nullptr;
	};
}
