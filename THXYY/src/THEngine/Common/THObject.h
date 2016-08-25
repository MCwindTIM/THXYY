#ifndef THOBJECT_H
#define THOBJECT_H


namespace THEngine
{
	class IKeyboardListener;

	class Object
	{
	private:
		int refCount;

	public:
		Object();
		virtual ~Object();
		
		virtual void Retain() final;
		virtual void Release() final;
	};
}

#endif