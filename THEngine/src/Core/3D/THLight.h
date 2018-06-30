#ifndef THLIGHT_H
#define THLIGHT_H

#include <Common\THCommon.h>
#include <Math\THMatrix.h>

namespace THEngine
{
	class Light : public Object
	{
	public:
		enum Type
		{
			NONE = 0,
			AMBIENT = 1,
			DIRECTIONAL = 2,
			POINT = 3,
			SPOTLIGHT = 4
		};

		Type type;

	protected:
		Vector3f color = Vector3f(1.0f, 1.0f, 1.0f);

	public:
		Light();
		Light(const Vector3f& color);
		virtual ~Light();

		inline Type GetType() const { return type; }

		inline const Vector3f& GetColor() const { return color; }
	};

	class AmbientLight : public Light
	{
	public:
		AmbientLight() { type = Light::AMBIENT; }
		AmbientLight(const Vector3f& color) : Light(color) { type = Light::AMBIENT; }
	};

	class DirectionalLight : public Light
	{
	private:
		Vector3f direction;

	public:
		DirectionalLight();
		DirectionalLight(const Vector3f& color, const Vector3f& direction);
		virtual ~DirectionalLight();

		inline const Vector3f& GetDirection() const { return direction; }
		inline void SetDirection(const Vector3f& direction) { this->direction = direction; }
	};
}

#endif