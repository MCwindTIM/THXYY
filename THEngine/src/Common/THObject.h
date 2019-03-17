#ifndef THOBJECT_H
#define THOBJECT_H

#include <atomic>

namespace THEngine
{
	class IKeyboardListener;

	template<class T>
	class Ptr;

	class Object
	{
	public:
		virtual Ptr<Object> Clone() const;

		Object& operator=(const Object& obj);
		Object& operator=(Object&& rhs) = default;

		int RefCount() const { return this->refCount_; }

	protected:
		Object() = default;
		Object(const Object& object);
		Object(Object&& rhs) = default;
		virtual ~Object();

		void Retain() { refCount_++; }
		void Release();

	private:
		std::atomic_int refCount_ = 0;
		bool alive = true;

		template<class T>
		friend class Ptr;
	};
}

#endif