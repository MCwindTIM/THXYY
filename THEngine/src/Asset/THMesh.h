#ifndef TH_MESH_ASSET_H
#define TH_MESH_ASSET_H

#include "THBaseAsset.h"
#include <Math\THMath.h>

struct aiScene;
struct aiNode;
struct aiMesh;

namespace THEngine
{
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class VertexFormat;

	class Material
	{
	public:
		Vector4f ambient = Vector4f(1, 1, 1, 1);
		Vector4f diffuse = Vector4f(1, 1, 1, 1);
		Vector4f specular = Vector4f(0, 0, 0, 1);
		Vector4f emissive = Vector4f(0, 0, 0, 0);
		float shininess = 0.0f;
		Ptr<Texture> texture = nullptr;
	};

	struct MeshVertex
	{
		float x, y, z;
		float nx, ny, nz;
		float u, v;
		MeshVertex() {}
		MeshVertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) :
			x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), u(u), v(v)
		{
		}
	};

	enum MeshVertexAttribute
	{
		POSITION = 0x00000001,
		NORMAL = 0x00000002,
		COLOR = 0x00000004,
		TANGENT = 0x00000008,
		UV = 0x00000010,
		UV2 = 0x00000020,
		UV3 = 0x00000040,
		UV4 = 0x00000080
	};

	class Mesh : public BaseAsset
	{
	private:
		class AssimpLoader
		{
		private:
			const String * path = nullptr;
			String dir;

		private:
			Ptr<Mesh> LoadAssimpNode(const aiNode* node, const aiScene* scene);
			bool LoadAssimpMesh(Ptr<Mesh> subMesh, const aiMesh* mesh, const aiScene* scene);

		public:
			Ptr<Mesh> Load(const String& path);
		};

	protected:
		uint32_t vertexAttributes = MeshVertexAttribute::POSITION | MeshVertexAttribute::NORMAL | MeshVertexAttribute::UV;
		String filePath;
		Material material;

		Ptr<VertexBuffer> vertexBuffer;
		Ptr<IndexBuffer> indexBuffer;
		Ptr<VertexFormat> vertexFormat;

		std::vector<Vector3f> vertices;
		std::vector<Vector3f> normals;
		std::vector<Vector3f> vertexColors;
		std::vector<Vector3f> tangents;
		std::vector<Vector2f> uv[4];
		std::vector<uint32_t> triangles;

		std::vector<Ptr<Mesh>> subMeshes;

		bool changed = true;
		bool isDynamic = false;

	public:
		Mesh(bool dynamic = false);
		virtual ~Mesh() = default;

		static Ptr<Mesh> CreateMeshFromFile(const String& filePath);

		virtual void OnLostDevice() override {}
		virtual void OnResetDevice() override {}

		inline void SetVertexAttributes(uint32_t attributes) { this->vertexAttributes = attributes; }

		inline void SetMaterial(const Material& material) { this->material = material; }

		inline std::vector<Vector3f>& GetVertices() { return this->vertices; }
		inline const std::vector<Vector3f>& GetVertices() const { return this->vertices; }

		inline std::vector<Vector3f>& GetNormals() { return this->normals; }
		inline const std::vector<Vector3f>& GetNormals() const { return this->normals; }

		inline std::vector<Vector3f>& GetVetexColors() { return this->vertexColors; }
		inline const std::vector<Vector3f>& GetVertexColors() const { return this->vertexColors; }

		inline std::vector<Vector3f>& GetTangents() { return this->tangents; }
		inline const std::vector<Vector3f>& GetTangents() const { return this->tangents; }

		inline std::vector<Vector2f>& GetUV() { return this->uv[0]; }
		inline const std::vector<Vector2f>& GetUV() const { return this->uv[0]; }

		inline std::vector<Vector2f>& GetUV2() { return this->uv[1]; }
		inline const std::vector<Vector2f>& GetUV2() const { return this->uv[1]; }

		inline std::vector<Vector2f>& GetUV3() { return this->uv[2]; }
		inline const std::vector<Vector2f>& GetUV3() const { return this->uv[2]; }

		inline std::vector<Vector2f>& GetUV4() { return this->uv[3]; }
		inline const std::vector<Vector2f>& GetUV4() const { return this->uv[3]; }

		inline std::vector<size_t>& GetTriangles() { return this->triangles; }
		inline const std::vector<size_t>& GetTriangles() const { return this->triangles; }

		void DrawGeometry();

		static Ptr<Mesh> Sphere(float radius);
		static Ptr<Mesh> Cube(float size);
		static Ptr<Mesh> Box(float xWidth, float yWidth, float zWidth);
		static Ptr<Mesh> Cone(float radius, float height);

		friend class MeshRenderer;
	};
}

#endif
