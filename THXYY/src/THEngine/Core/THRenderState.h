#ifndef TH_RENDER_STATE_H
#define TH_RENDER_STATE_H

#include <Common\THCommon.h>
#include <Math\THMath.h>
#include <Core\3D\THLight.h>
#include "THEnvironment.h"

namespace THEngine
{
	struct Viewport
	{
		int x;
		int y;
		int width;
		int height;
		int minZ;
		int maxZ;
	};

	enum BlendMode
	{
		ALPHA_BLEND = 1,
		ADD = 2
	};

	class RenderState : public Object
	{
	private:
		Environment* environment; 

		Matrix world;
		Matrix projection;
		Matrix view;

		Viewport viewport;

		Shader* shader = nullptr;

	public:
		RenderState();
		virtual ~RenderState();

		inline bool IsFogEnabled() { return this->environment->fogEnable; }

		inline bool IsLightingEnabled() { return this->environment->lightingEnable; }

		inline const Fog& GetFog() const { return this->environment->fog; }

		inline const Matrix& GetWorldMatrix() { return this->world; }
		inline const Matrix& GetProjectionMatrix() { return this->projection; }
		inline const Matrix& GetViewMatrix() { return this->view; }
		inline const Viewport& GetViewport() const { return this->viewport; }

		inline const Vector4f& GetAmbientLight() const { return environment->ambientLight; }
		inline LinkedList<Light*>* GetLights() const { return &environment->lights; }

		inline Shader* GetCurrentShader() const { return this->shader; }

		void Clear();

		friend class Application;
		friend class Layer;
		friend class Shader;
	};
}

#endif