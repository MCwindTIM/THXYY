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

		Light* currentLight = nullptr;
		Texture* shadowMap = nullptr;

		bool isRenderingAmbient = false;

	private:
		void SetupRenderState();

		void SetupShaderParams(Mesh* mesh);

		void Shade(Mesh* mesh);

		void ShadeWithAmbient(Mesh* mesh, const Vector4f& ambient);

		void ShadeWithLight(Mesh* mesh, Light* light);

		void DrawShadowMap();

		void DrawMesh(Mesh* mesh);

	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Render(GameObject* object) override;

		inline void SetRenderAmbient(bool renderAmbient) { this->isRenderingAmbient = renderAmbient; }
		inline void SetCurrentLight(Light* light) { this->currentLight = light; }
		inline void SetShadowMap(Texture* shadowMap) { this->shadowMap = shadowMap; }

		static MeshRenderer* Create();
	};
}

#endif