#ifndef THRENDEROBJECT_H
#define THRENDEROBJECT_H

#include "THGameObject.h"
#include "../Tween/THTweenManager.h"

namespace THEngine
{
	class RenderObject : public GameObject
	{
	protected:
		Vector3f position;
		Vector3f color = Vector3f(1.0f, 1.0f, 1.0f);
		float alpha = 1.0f;

		Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f);

		TweenManager* tweenManager = nullptr;

	public:
		RenderObject();
		virtual ~RenderObject();

		virtual void Update() override;

		void AddTween(Tween* tween);

		inline void KillTween(Tween* tween)
		{
			tweenManager->KillTween(tween);
		}

		inline void SetPosition(Vector3f position)
		{
			this->position = position;
		}

		inline Vector3f GetPosition()
		{
			return position;
		}

		inline void SetColor(Vector3f color)
		{
			this->color = color;
		}

		inline Vector3f GetColor()
		{
			return color;
		}

		inline float GetAlpha() { return alpha; }
		inline void SetAlpha(float alpha) { this->alpha = alpha; }

		inline void SetScale(Vector3f scale) { this->scale = scale; }
		inline Vector3f GetScale() { return scale; }

		friend class MoveTo;
		friend class MoveBy;
		friend class FadeTo;
		friend class FadeOut;
		friend class ColorTo;
		friend class ScaleTo;
	};
}

#endif