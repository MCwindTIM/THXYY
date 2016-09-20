#ifndef THMESHRENDERER_H
#define THMESHRENDERER_H

#include "../Core/3D/THMesh.h"
#include "THRenderer.h"
#include "../Asset/THShader.h"

namespace THEngine
{
	class MeshRenderer : public Renderer
	{
	protected:
		Shader* meshShader = nullptr;

		IDirect3DVertexBuffer9* vertexBuffer = nullptr;
		IDirect3DIndexBuffer9* indexBuffer = nullptr;

	protected:
		void CalcWorldTransform(Mesh* mesh);

	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Render(RenderObject* object) override;

		static MeshRenderer* Create();
	};
}

#endif