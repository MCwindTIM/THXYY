#ifndef THGAMEOBJECT_H
#define THGAMEOBJECT_H

#include <Common\THCommon.h>
#include <Math\THMath.h>
#include "THRenderState.h"

namespace THEngine
{
	class Layer;
	class RenderQueue;
	class TweenManager;
	class Tween;

	class GameObject : public EngineObject
	{
	protected:
		LinkedList<Ptr<GameObject>> children;
		bool needRemove;
		bool activated = false;

		Vector3f position = Vector3f(0.0f, 0.0f, 0.0f);
		Vector3f color = Vector3f(1.0f, 1.0f, 1.0f);
		float alpha = 1.0f;

		Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f);

		Matrix rotation3D;

		Ptr<TweenManager> tweenManager = nullptr;

		Matrix finalWorldTransform;

		bool enableLighting = true;

	private:
		void Visit();
		void PushDataStack();
		void PopDataStack();
		void WriteRenderData();

	protected:
		virtual void SendToRenderQueue();

	public:
		GameObject();
		GameObject(const GameObject& object);
		virtual ~GameObject();

		virtual void Update() override;
		virtual void Draw() override;
		virtual void OnLoad(Ptr<AsyncInfo> info) override;
		virtual Ptr<Object> Clone() const override;

		//virtual functions
		virtual void OnDestroy();
		virtual void OnVisit() {}
		virtual void DrawShadowMap();
		virtual void DrawGeometry();
		virtual void GetWorldMatrix(Matrix* world);

		void AddChild(Ptr<GameObject> obj);

		void RemoveChild(Ptr<GameObject> child);

		void RemoveChildAt(int index);

		void RemoveAllChildren();

		inline void MarkDestroy() { needRemove = true; }

		inline bool NeedRemove() { return needRemove; }

		void AddTween(Ptr<Tween> tween);

		void ClearTweens();

		void KillTween(Ptr<Tween> tween);

		inline void SetPosition(const Vector3f& position)
		{
			this->position = position;
		}

		inline const Vector3f& GetPosition()
		{
			return position;
		}

		inline void SetColor(const Vector3f& color)
		{
			this->color = color;
		}

		inline const Vector3f& GetColor()
		{
			return color;
		}

		inline float GetAlpha() { return alpha; }
		inline void SetAlpha(float alpha) { this->alpha = alpha; }

		inline void SetScale(Vector3f scale) { this->scale = scale; }
		inline Vector3f GetScale() { return scale; }

		void SetRotationByAxis(const Vector3f& axis, float rotation);
		void SetRotationByAxis(const Vector3f& axis, const Vector3f& rotatingCenter, float rotation);

		const Matrix& GetRotationMatrix() const { return this->rotation3D; }

		friend class Layer;
		friend class Renderer;
		friend class SpriteFont;
		friend class MoveTo;
		friend class MoveBy;
		friend class FadeTo;
		friend class FadeOut;
		friend class ColorTo;
		friend class ScaleTo;
	};
}

#endif