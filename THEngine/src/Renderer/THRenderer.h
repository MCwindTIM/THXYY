#ifndef THRENDERER_H
#define THRENDERER_H

#include <Common\THCommon.h>

namespace THEngine
{
	class GameObject;
	class Shader;
	class Light;
	class DirectionalLight;

	class Renderer : public Object
	{
	protected:
		void SetupRenderState(Ptr<GameObject> object);
		void SetupWorldTransform(Ptr<GameObject> object);

	public:
		virtual void Render(Ptr<GameObject> obj) = 0;
	};

	class Renderer3D : public Renderer
	{
	protected:
		Ptr<Shader> shader;
		Ptr<Light> light;

	protected:
		void SetupShaderParams(Ptr<GameObject> obj);

		void SetupDirLight(Ptr<DirectionalLight> dirLight);

	public:
		void SetLight(Ptr<Light> light) { this->light = light; }
	};
}

#endif