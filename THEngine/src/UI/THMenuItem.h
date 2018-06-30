#ifndef THMENUITEM_H
#define THMENUITEM_H

#include <Core\THSprite.h>

namespace THEngine
{
	class Menu;
	class Tween;

	class MenuItem : public Sprite
	{
	protected:
		Menu* menu = nullptr;
		bool selected = false;
		bool selectable = true;
		bool twinkleEnabled = true;
		bool shineEnabled = true;
		bool vibrateEnabled = true;

		Ptr<Tween> tweenShine = nullptr;
		float shineTime = 15;
		Vector3f shineColor = Vector3f(0.75f, 0.75f, 0.75f);

		Tween* tweenTwinkle = nullptr;
		int twinkleTime = 30;
		int twinkleInterval = 2;

		Ptr<Tween> tweenVibrate = nullptr;
		float vibrateTime = 3;
		float xVibrateRange = 2;
		float yVibrateRange = 2;

		Vector3f colorUnselected = Vector3f(0.6f, 0.6f, 0.6f);
		Vector3f colorUnselectable = Vector3f(0.3f, 0.3f, 0.3f);

		bool isTwinkling = false;
		int twinkleCounter = 0;

	public:
		MenuItem();
		virtual ~MenuItem();

		virtual void Update() override;

		virtual void OnSelect();
		virtual void OnClick();
		virtual void OnDeselect();

		void SetSelectable(bool selectable);

		inline void SetColorUnSelected(const Vector3f& color) { this->colorUnselected = color; }
		inline void SetColorUnSelectable(const Vector3f& color) { this->colorUnselectable = color; }

		friend class Menu;
	};
}

#endif