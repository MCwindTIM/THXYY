#ifndef TH_RENDER_STATE_H
#define TH_RENDER_STATE_H

#include <Common\THCommon.h>
#include <Math\THMath.h>
#include <Core\3D\THLight.h>

namespace THEngine
{
	struct Fog
	{
		Vector4f fogColor;
		float fogStart;
		float fogEnd;
	};

	struct Viewport
	{
		int x;
		int y;
		int width;
		int height;
		int minZ;
		int maxZ;
	};

	class RenderState : public Object
	{
	private:
		bool fogEnable = false;
		Fog fog;

		bool lightingEnable = false;

		Matrix world;
		Matrix projection;
		Matrix view;

		Viewport viewport;

		ArrayList<DirectionalLight*> directionalLights;

		Shader* shader = nullptr;

	public:
		RenderState();
		virtual ~RenderState();

		inline bool IsFogEnabled() { return this->fogEnable; }

		inline bool IsLightingEnabled() { return this->lightingEnable; }

		inline const Fog& GetFog() const { return this->fog; }

		inline const Matrix& GetWorldMatrix() { return this->world; }
		inline const Matrix& GetProjectionMatrix() { return this->projection; }
		inline const Matrix& GetViewMatrix() { return this->view; }
		inline const Viewport& GetViewport() const { return this->viewport; }

		void Clear();

		friend class Application;
		friend class Layer;
		friend class Shader;
	};
}

#endif