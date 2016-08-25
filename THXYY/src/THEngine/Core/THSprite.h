#ifndef THSPRITE_H
#define THSPRITE_H

#include "THGameObject.h"
#include "../Asset/THTexture.h"
#include "../Renderer/THRenderer.h"

namespace THEngine
{
	class Renderer;

	class Sprite : public GameObject
	{
	public:

	protected:
		Texture* texture;
		Rect texRect;
		Renderer* renderer;

		float alpha;
		Vector3f position;
		Vector3f color;
		Vector2f pivot;

		float rotation;
		float scaleX, scaleY;

		float speed;
		float angle;
		float acSpeed;
		float acAngle;

		float ax, ay, vx, vy;

		bool flipX;
		bool flipY;

	private:
		virtual void SendToRenderQueue() override final;

	public:
		Sprite();
		virtual ~Sprite();

		virtual void Update() override;
		virtual void Draw() override;

		inline void SetTexture(Texture* texture) { 
			this->texture = texture; 
		}
		inline void SetTexRect(Rect rect) { this->texRect = rect; }
		inline Rect GetTexRect() { return texRect; }
		inline Renderer* GetRenderer() { return renderer; }
		inline void SetPivot(Vector2f pivot) { this->pivot = pivot; }

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
		
		inline float GetRotation() { return rotation; }
		inline void SetRotation(float rotation) { this->rotation = rotation; }

		inline void SetSpeed(float speed) { this->speed = speed; }
		inline float GetSpeed() { return speed; }

		inline void SetAngle(float angle) { this->angle = angle; }
		inline float GetAngle() { return angle; }

		friend class SpriteRenderer;

		inline void SetFlipX(bool flipX) { this->flipX = flipX; }
		inline void SetFlipY(bool flipY) { this->flipY = flipY; }
		
		inline void SetScaleX(float x) { this->scaleX = x; }
		inline void SetScaleY(float y) { this->scaleY = y; }
		inline void SetScale(float x, float y) { SetScaleX(x); SetScaleY(y); }
		inline float GetScaleX() { return scaleX; }
		inline float GetScaleY() { return scaleY; }
	};
}

#endif