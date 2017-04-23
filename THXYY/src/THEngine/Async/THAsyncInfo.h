#ifndef TH_ASYNC_INFO_H
#define TH_ASYNC_INFO_H

#include <Common\THCommon.h>

namespace THEngine
{
	class AsyncInfo : public Object
	{
	private:
		using Callback = std::function<void()>;

	private:
		int progress = 0;
		int maxProgress = 100;
		bool finished = false;
		Callback onFinished;

	public:
		AsyncInfo() = default;
		virtual ~AsyncInfo() = default;

		friend class AsyncLoader;
	};
}

#endif
