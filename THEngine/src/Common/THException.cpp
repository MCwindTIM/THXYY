#include "THException.h"

namespace THEngine
{
	Exception::Exception()
	{
	}

	Exception::Exception(const String& info)
	{
		this->info = info;
	}

	Exception::~Exception()
	{
	}
}