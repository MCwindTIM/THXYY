#ifndef THCONCRETETWEEN_H
#define THCONCRETETWEEN_H

#include "THTween.h"

namespace THEngine
{
	class MoveTo : public TweenUnit
	{
	protected:
		Vector3f position;
		int duration;
		Tweener::Type type;

	public:
		MoveTo(Vector3f position, int duration, Tweener::Type type);
		virtual ~MoveTo();

		virtual void OnStart() override;
	};

	////////////////////////////////////////////////////
	class MoveBy : public TweenUnit
	{
	protected:
		Vector3f position;
		int duration;
		Tweener::Type type;

	public:
		MoveBy(Vector3f position, int duration, Tweener::Type type);
		virtual ~MoveBy();

		virtual void OnStart() override;
	};

	////////////////////////////////////////////////////
	class FadeTo : public TweenUnit
	{
	protected:
		float alpha;
		int duration;
		Tweener::Type type;

	public:
		FadeTo(float alpha, int duration, Tweener::Type type);
		virtual ~FadeTo();

		virtual void OnStart() override;
	};

	////////////////////////////////////////////////////
	class FadeOut : public TweenUnit
	{
	protected:
		int duration;
		Tweener::Type type;

	public:
		FadeOut(int duration, Tweener::Type type);
		virtual ~FadeOut();

		virtual void OnStart() override;
		virtual void OnFinish() override;
	};

	/////////////////////////////////////////////////////
	class ColorTo : public TweenUnit
	{
	protected:
		Vector3f color;
		int duration;
		Tweener::Type type;

	public:
		ColorTo(Vector3f color, int duration, Tweener::Type type);
		virtual ~ColorTo();

		virtual void OnStart() override;
	};
}

#endif