#include "THAsyncLoader.h"
#include "THAsyncInfo.h"
#include <thread>

namespace THEngine
{
	AsyncInfo* AsyncLoader::Load(EngineObject* object)
	{
		return Load(object, []() {});
	}

	AsyncInfo* AsyncLoader::Load(EngineObject* object, const Callback& onCompleted)
	{
		AsyncInfo* info = new AsyncInfo();
		info->onFinished = onCompleted;

		std::thread threadLoad(&AsyncLoader::ThreadFuncLoad, info, object);
		threadLoad.detach();

		return info;
	}

	void AsyncLoader::ThreadFuncLoad(AsyncInfo* info, EngineObject* object)
	{
		info->Retain();
		object->OnLoad(info);

		info->onFinished();

		TH_SAFE_RELEASE(info);
	}
}