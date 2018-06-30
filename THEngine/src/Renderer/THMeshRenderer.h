#ifndef TH_MESH_RENDERER_H
#define TH_MESH_RENDERER_H

#include "THRenderer.h"

namespace THEngine
{
	class FloatTexture;
	class ShadowMap;
	class MeshObject;
	class Light;
	struct Vector4f;
	class RenderQueue;

	class MeshRenderer : public Renderer3D
	{
	protected:
		MeshRenderer();

	public:
		virtual ~MeshRenderer();

		virtual void Render(Ptr<GameObject> object) override;

		static Ptr<MeshRenderer> Create();
	};
}

#endif