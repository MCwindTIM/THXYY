#ifndef TH_TERRAIN_H
#define TH_TERRAIN_H

#include <Core\THGameObject.h>
#include <Asset\THMesh.h>

namespace THEngine
{
	class Texture;
	class StaticVertexBuffer;
	class StaticIndexBuffer;

	class Terrain : public GameObject
	{
	private:
		Ptr<Texture> heightMap;
		Material material;
		uint32_t vertexAttributes = MeshVertexAttribute::POSITION | MeshVertexAttribute::NORMAL
			| MeshVertexAttribute::UV;

		bool changed = true;
		float xWidth = 100;
		float yWidth = 100;
		float zScale = 1;
		size_t xResolution = 100;
		size_t yResolution = 100;
		Vector2f cellSize;
		Vector2f dTexCoord;

		Ptr<StaticVertexBuffer> vb;
		Ptr<StaticIndexBuffer> ib;

		Ptr<VertexFormat> vertexFormat;

	private:
		void GenerateBuffers();

	public:
		Terrain();

		void SetHeightMap(Ptr<Texture> heightMap) { this->heightMap = heightMap; }
		void SetMaterial(const Material& mat) { this->material = mat; }

		void SetXWidth(float xWidth) { this->xWidth = xWidth; }
		void SetYWidth(float yWidth) { this->yWidth = yWidth; }
		void SetXResolution(size_t xResolution) { this->xResolution = xResolution; }
		void SetYResolution(size_t yResolution) { this->yResolution = yResolution; }
		void SetZScale(float zScale) { this->zScale = zScale; }

		virtual void Draw() override;
		virtual void SendToRenderQueue() override;

		virtual void DrawGeometry() override;
		virtual void DrawShadowMap() override;

		friend class TerrainRenderer;
	};
}

#endif