#ifndef THMESH_H
#define THMESH_H

#include "../THRenderObject.h"
#include "../../Asset/THTexture.h"

namespace THEngine
{
	class Material
	{
	public:
		Vector3f ambient = Vector3f(0, 0, 0);
		Vector3f diffuse = Vector3f(0, 0, 0);
		Vector3f specular = Vector3f(0, 0, 0);
		Texture* texture = nullptr;
	};

	struct MeshVertex
	{
		float x, y, z;
		float u, v;
		float nx, ny, nz;
		MeshVertex() {}
		MeshVertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) :
			x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), u(u), v(v) {}
	};

	class Mesh : public RenderObject
	{
	public:
		enum DrawType
		{
			TRIANGLE_LIST,
			TRIANGLE_STRIP 
		};

	protected:
		int vertexCount = 0;

		Material material;
		DrawType drawType = TRIANGLE_LIST;

		ID3DXMesh* mesh = nullptr;
		IDirect3DVertexBuffer9* vertexBuffer = nullptr;
		IDirect3DIndexBuffer9* indexBuffer = nullptr;

	public:
		Mesh();
		virtual ~Mesh();

		virtual void Update() override;
		virtual void Draw() override;
		virtual void SendToRenderQueue() override;

		inline void SetMaterial(Material material) { this->material = material; }

		inline void SetDrawType(DrawType drawType) { this->drawType = drawType; }

		void InitVertexBuffer(int size);

		void SetVertexData(void* data);

		friend class MeshRenderer;
	};
}

#endif