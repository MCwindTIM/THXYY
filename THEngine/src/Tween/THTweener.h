#ifndef THTWEENER_H
#define THTWEENER_H

#include <Common\THCommon.h>

namespace THEngine
{
	class Tweener : public Object
	{
	public:
		enum Type
		{
			SIMPLE,
			EASE_IN,
			EASE_OUT,
			EASE_INOUT
		};

	protected:
		int duration;
		int elapsed = 0;
		Type type = SIMPLE;

	private:
		//����һ����0,1������Ĳ���t�����ݲ�ͬ��type�����ز�ͬ�ģ�0,1�������ֵ
		float Tween(float t, Type type);

	protected:
		//�����ֵ���
		float CalcInterpolation(float initialValue, float finalValue, int duration, int elapsed, Type type);

	public:
		Tweener();
		virtual ~Tweener();

		virtual void Update();

		inline void SetDuration(int duration) { this->duration = duration; }
		inline int GetDuration() { return duration; }

		inline void SetType(Type type) { this->type = type; }

		friend class TweenUnit;
	};
}

#endif