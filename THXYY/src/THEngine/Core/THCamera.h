#ifndef THCAMERA_H
#define THCAMERA_H

#include "../Common/THCommon.h"
#include "../Math/THMathUtil.h"
#include <Asset\THRenderTexture.h>

namespace THEngine
{
	class Layer;

	class Camera : public EngineObject
	{
	protected:
		Layer* layer = nullptr;

		Vector3f position;
		String name = "";
		RenderTexture* renderTexture = nullptr;
		Rect viewport = Rect(0, 0, 0, 0);

	public:
		Camera();
		Camera(const String& name);
		virtual ~Camera();

		inline void SetPosition(Vector3f position) { this->position = position; }
		inline Vector3f GetPosition() { return position; }

		virtual void Update() override;
		virtual void Draw() override;

		inline void SetName(const String& name) { this->name = name; }

		inline String& GetName() { return name; }

		inline void SetRenderTexture(RenderTexture* renderTexture)
		{
			TH_SET(this->renderTexture, renderTexture);
		}

		inline void SetViewport(const Rect& rect) { this->viewport = rect; }

		virtual bool Is2D() = 0;
	};

	class Camera2D : public Camera
	{
	protected:
		float width, height;

	public:
		Camera2D();
		Camera2D(const String& name);
		virtual ~Camera2D();

		inline void SetWidth(float width) { this->width = width; }
		inline float GetWidth() { return width; }

		inline void SetHeight(float height) { this->height = height; }
		inline float GetHeight() { return height; }

		virtual bool Is2D() override final { return true; }
	};

	class Camera3D : public Camera
	{
	protected:
		Vector3f lookAt;
		Vector3f up;
		
		float fov = 60.0f;

	public:
		Camera3D();
		Camera3D(const String& name);
		virtual ~Camera3D();

		inline void SetLookAt(Vector3f lookAt) { this->lookAt = lookAt; }
		inline Vector3f GetLookAt() { return lookAt; }

		inline void SetUp(Vector3f up) { this->up = up; }
		inline Vector3f GetUp() { return up; }

		inline void SetFov(float fov) { this->fov = fov; }
		inline float GetFov() { return fov; }

		virtual bool Is2D() override final { return false; }

		friend class Layer;
	};
}

#endif