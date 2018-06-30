#ifndef TH_COMMON_H
#define TH_COMMON_H

#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>

//Fix VS 2015 link errors
#if _MSC_VER >= 1900
//http://stackoverflow.com/questions/31053670/unresolved-external-symbol-vsnprintf-in-dxerr-lib
#pragma comment(lib,"legacy_stdio_definitions.lib")
#endif

#ifdef WIN32
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "Dbghelp.lib")
#endif

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION   0x0800
#endif

#include "THTemplates.h"
#include "THObject.h"
#include "THPtr.h"
#include "THEngineObject.h"
#include "THDefine.h"
#include "THString.h"
#include "THExceptionManager.h"
#include "THLogger.h"
#include "THList.h"
#include "THMap.h"

namespace THEngine
{
	void THMessageBox(String message);

	inline void THLog(const String& message)
	{
		Logger::GetInstance()->WriteLine(message);
	}
}

#endif