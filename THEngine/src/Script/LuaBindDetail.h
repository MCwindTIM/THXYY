#pragma once

extern "C" {
	#include <External\LuaJIT\lua.h>
	#include <External\LuaJIT\lauxlib.h>
	#include <External\LuaJIT\lualib.h>
}

#pragma comment(lib, "LuaJIT/lua51.lib")
#pragma comment(lib, "LuaJIT/luajit.lib")

#define LUABIND_NO_EXCEPTIONS

#include <luabind\luabind.hpp>
#ifdef _DEBUG
#pragma comment(lib, "luabind/luabind-debug.lib")
#else
#pragma comment(lib, "luabind/luabind-release.lib")
#endif

using namespace luabind;

#define BEGIN_LUABIND_WRAPPER(classname) struct Lua_##classname##_Wrapper : classname, luabind::wrap_base {
#define DECLARE_NO_PARAM_METHOD(classname, luaMethodName, cppMethodName) \
    virtual void cppMethodName() { \
        luabind::wrap_base::call<void>(#luaMethodName);   \
    }  \
    static void default_##luaMethodName(classname* ptr) { \
		return ptr->classname::cppMethodName();   \
	}
#define END_LUABIND_WRAPPER()   };

#define BIND_CALLBACK(classname, luaMethodName, cppMethodName) \
    .def(#luaMethodName, &classname::cppMethodName, &Lua_##classname##_Wrapper::default_##luaMethodName)

struct LuaRef
{
	lua_State* L;
	int ref;

	LuaRef(lua_State* L, int ref) : L(L), ref(ref) {}
	~LuaRef() { luaL_unref(L, LUA_REGISTRYINDEX, ref); }
};

template<class R, class... Args>
struct LuaFunc
{
	std::shared_ptr<LuaRef> _ref;
	lua_State* _L;

	LuaFunc(lua_State* L, std::shared_ptr<LuaRef> ref) :_L(L), _ref(ref) {}

	R operator() (Args... args)
	{
		lua_rawgeti(_L, LUA_REGISTRYINDEX, _ref->ref);
		lua_pcall(_L, 0, 0, 0);
	}
};

// smart pointer
namespace THEngine
{
	template<class T>
	T* get_pointer(Ptr<T>& p) { return p.Get(); }

	template<class T>
	T* get_pointer(const Ptr<T>& p) { return p.Get(); }
}

namespace luabind
{
	using namespace THEngine;

	namespace detail
	{
		template<typename T>
		struct pointer_traits<Ptr<T>>
		{
			enum { is_pointer = true };
			using value_type = T;
		};
	}

	template <class R, class... Args>
	struct default_converter<std::function<R(Args...)> >
		: native_converter_base<std::function<R(Args...)>>
	{
		typedef std::function<R(Args...)> Func;

		static int compute_score(lua_State* L, int index)
		{
			auto t = lua_type(L, index);
			return lua_type(L, index) == LUA_TFUNCTION ? 0 : -1;
		}

		Func from(lua_State* L, int index)
		{
			lua_pushvalue(L, index);
			int ref = luaL_ref(L, LUA_REGISTRYINDEX);
			return LuaFunc<R, Args...>(L, std::shared_ptr<LuaRef>(new LuaRef(L, ref)));
		}

		void to(lua_State* L, std::function<R(Args...)> const& x)
		{
			int test = 1;
		}
	};

	template <class R, class... Args>
	struct default_converter<std::function<R(Args...)> const&>
		: default_converter<std::function<R(Args...)>>
	{
	};
}