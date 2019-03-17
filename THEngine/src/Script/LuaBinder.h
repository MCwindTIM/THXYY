#pragma once

extern "C" {
#include <External\LuaJIT\lua.h>
#include <External\LuaJIT\lauxlib.h>
#include <External\LuaJIT\lualib.h>
}

namespace THEngine
{
	template<int Index, class T, class... RemArgs>
	struct GetArgType
	{
		using value = typename GetArgType<Index - 1, RemArgs...>::value;
	};

	template<class T, class... RemArgs>
	struct GetArgType<0, T, RemArgs...>
	{
		using value = T;
	};

	template<class R, class... Args>
	struct FunctionProxy
	{
		static inline int Call(lua_State* L)
		{
			typedef R(*Func)(Args...);
			Func func = (Func)lua_touserdata(L, lua_upvalueindex(1));

			std::tuple<Args...> args;
			ReadParam<sizeof...(Args)-1, Args...>::Call(L, args);

			R result = CallFunc(func, args, std::index_sequence_for<Args...>());
			Cpp2Lua(L, result);
			return 1;
		}
	};

	template<class... Args>
	struct FunctionProxy<void, Args...>
	{
		static inline int Call(lua_State* L)
		{
			typedef void(*Func)(Args...);
			Func func = (Func)lua_touserdata(L, lua_upvalueindex(1));

			std::tuple<Args...> args;
			ReadParam<sizeof...(Args)-1, Args...>::Call(L, args);

			CallFunc(func, args, std::index_sequence_for<Args...>());
			return 0;
		}
	};

	template<class R, class... Args, std::size_t... Is>
	inline R CallFunc(R(*func)(Args...), const std::tuple<Args...>& args, std::index_sequence<Is...>)
	{
		return (*func)(std::get<Is>(args)...);
	}

	template< int ParamIndex, class... Args>
	struct ReadParam
	{
		inline static void Call(lua_State* L, std::tuple<Args...>& args)
		{
			using Type = GetArgType<ParamIndex, Args...>::value;
			Type param = Lua2Cpp<Type>(L, ParamIndex + 1);
			std::get<ParamIndex>(args) = param;
			ReadParam<ParamIndex - 1, Args...>::Call(L, args);
		}
	};

	template<class... Args>
	struct ReadParam<-1, Args...>
	{
		inline static void Call(lua_State* L, std::tuple<Args...>& args) {}
	};

	/****************Lua2Cpp******************************/
	template<class T>
	inline T Lua2Cpp(lua_State* L, int index);

	// integers
	template<> inline int Lua2Cpp<int>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline unsigned int Lua2Cpp<unsigned int>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline char Lua2Cpp<char>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline unsigned char Lua2Cpp<unsigned char>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline long Lua2Cpp<long>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline unsigned long Lua2Cpp<unsigned long>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline short Lua2Cpp<short>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline unsigned short Lua2Cpp<unsigned short>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline long long Lua2Cpp<long long>(lua_State* L, int index) { return luaL_checkinteger(L, index); }
	template<> inline unsigned long long Lua2Cpp<unsigned long long>(lua_State* L, int index) { return luaL_checkinteger(L, index); }

	// floats
	template<> inline float Lua2Cpp<float>(lua_State* L, int index) { return luaL_checknumber(L, index); }
	template<> inline double Lua2Cpp<double>(lua_State* L, int index) { return luaL_checknumber(L, index); }

	// string
	template<> inline const char* Lua2Cpp<const char*>(lua_State* L, int index) { return luaL_checkstring(L, index); }

	/*************Cpp2Lua*************************/
	template<class T>
	inline void Cpp2Lua(lua_State* L, T value);

	//integers
	template<> inline void Cpp2Lua<int>(lua_State* L, int value) { lua_pushinteger(L, value); }

	class LuaBinder
	{
	private:
		lua_State * _L = nullptr;

	public:
		LuaBinder(lua_State* L) : _L(L) {}

		template<class R, class... Args>
		void RegisterFunction(const char* name, R(*func)(Args...))
		{
			lua_pushlightuserdata(_L, func);
			lua_pushcclosure(_L, FunctionProxy<R, Args...>::Call, 1);
			lua_setglobal(_L, name);
		}
	};
}
