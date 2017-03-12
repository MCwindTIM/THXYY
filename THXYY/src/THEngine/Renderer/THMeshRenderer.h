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

	private:
		void DrawD3DMesh(Mesh::D3DMesh* mesh);

		void SetupRenderState();

		void SetupShaderParams(Mesh* mesh);

		void Shade(Mesh* mesh);

		void ShadeWithAmbient(Mesh* mesh, const Vector4f& ambient);

		void ShadeWithLight(Mesh* mesh, Light* light);

		void DrawMesh(Mesh* mesh);

	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Render(GameObject* object) override;

		static MeshRenderer* Create();
	};
}

#endif