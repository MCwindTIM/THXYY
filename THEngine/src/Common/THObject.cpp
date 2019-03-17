#include "THObject.h"
#include "THDefine.h"
#include "THPtr.h"

namespace THEngine
{
	Object::Object(const Object& object)
	{
		refCount_ = 0;
	}

	Object::~Object()
	{
	}

	Object& Object::operator=(const Object& object)
	{
		this->refCount_ = 0;
		return *this;
	}

	Ptr<Object> Object::Clone() const
	{
		throw std::runtime_error("trying to clone a non clonable object!");
	}

	void Object::Release()
	{
		ASSERT(refCount_ > 0 && alive);
		refCount_--;
		if (refCount_ == 0)
		{
			alive = false;
			delete this;
		}
	}
}