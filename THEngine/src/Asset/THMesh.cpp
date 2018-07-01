#include "THMesh.h"
#include "THShaderStock.h"
#include "THShader.h"
#include "THAssetManager.h"
#include <Graphic\THDevice.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <DirectXTK\GeometricPrimitive.h>

using namespace DirectX;

#ifdef _DEBUG
#pragma comment(lib, "assimp/debug/assimp-vc140-mt.lib")
#pragma comment(lib, "assimp/debug/IrrXML.lib")
#else
#pragma comment(lib, "assimp/release/assimp-vc140-mt.lib")
#pragma comment(lib, "assimp/release/IrrXML.lib")
#endif

#undef AI_CONFIG_PP_SBP_REMOVE
#define AI_CONFIG_PP_SBP_REMOVE  aiPrimitiveType_POINTS | aiPrimitiveType_LINES

namespace THEngine
{
	void Mesh::DrawGeometry()
	{
		auto device = Device::GetInstance();
		auto meshShader = ShaderStock::GetInstance()->GetMeshShader();

		if (this->vertices.size() > 0 && this->triangles.size() > 0)
		{
			//TODO : add support for more vertex and material formats
			if (this->changed)
			{
				std::vector<VertexFormatItem> vfitems;
				vfitems.push_back(VertexFormatItem(0, DataType::FLOAT3, "POSITION", 0, 0));
				vfitems.push_back(VertexFormatItem(sizeof(float) * 3, DataType::FLOAT3, "NORMAL", 0, 0));
				vfitems.push_back(VertexFormatItem(sizeof(float) * 6, DataType::FLOAT2, "TEXCOORD", 0, 0));
				this->vertexFormat = device->CreateVertexFormat(vfitems, meshShader, "Mesh", 0);

				std::vector<MeshVertex> data(this->vertices.size());
				for (size_t i = 0; i < this->vertices.size(); i++)
				{
					data[i].x = this->vertices[i].x;
					data[i].y = this->vertices[i].y;
					data[i].z = this->vertices[i].z;
					data[i].nx = this->normals[i].x;
					data[i].ny = this->normals[i].y;
					data[i].nz = this->normals[i].z;
					data[i].u = this->uv[0][i].x;
					data[i].v = this->uv[0][i].y;
				}

				if (this->isDynamic == false)
				{
					this->vertexBuffer = device->CreateStaticVertexBuffer(sizeof(MeshVertex) * data.size(), &data[0]).Get();
					this->indexBuffer = device->CreateStaticIndexBuffer(sizeof(uint32_t) * triangles.size(), &triangles[0]).Get();
				}

				this->changed = false;
			}
			device->SetVertexFormat(this->vertexFormat);
			device->SetVertexBuffer(this->vertexBuffer, sizeof(MeshVertex), 0);
			device->SetIndexBuffer(this->indexBuffer);
			if (this->material.texture)
			{
				meshShader->SetTexture("g_texture", this->material.texture);
				meshShader->SetBoolean("g_hasTexture", true);
			}
			else
			{
				meshShader->SetBoolean("g_hasTexture", false);
			}
			meshShader->SetValue("g_material", &this->material, sizeof(Material) - sizeof(Texture*));
			meshShader->CommitChanges();
			device->DrawIndexed(PrimitiveType::TRIANGLE_LIST, this->triangles.size(), 0, 0);
		}
		for (size_t i = 0; i < this->subMeshes.size(); i++)
			this->subMeshes[i]->DrawGeometry();
	}

	Ptr<Mesh> Mesh::Sphere(float radius)
	{
		Ptr<Mesh> mesh = Ptr<Mesh>::New();

		std::vector<GeometricPrimitive::VertexType> vertices;
		std::vector<uint16_t> indices;
		GeometricPrimitive::CreateSphere(vertices, indices, radius * 2);

		mesh->vertices.reserve(vertices.size());
		mesh->normals.reserve(vertices.size());
		mesh->uv[0].reserve(vertices.size());
		mesh->triangles.reserve(indices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			mesh->vertices.push_back(Vector3f(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z));
			mesh->normals.push_back(Vector3f(vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z));
			mesh->uv[0].push_back(Vector2f(vertices[i].textureCoordinate.x, vertices[i].textureCoordinate.y));
		}
		for (size_t i = 0; i < indices.size(); i++)
		{
			mesh->triangles.push_back(indices[i]);
		}

		return mesh;
	}

	Ptr<Mesh> Mesh::Cube(float size)
	{
		Ptr<Mesh> mesh = Ptr<Mesh>::New();

		std::vector<GeometricPrimitive::VertexType> vertices;
		std::vector<uint16_t> indices;
		GeometricPrimitive::CreateCube(vertices, indices, size);

		mesh->vertices.reserve(vertices.size());
		mesh->normals.reserve(vertices.size());
		mesh->uv[0].reserve(vertices.size());
		mesh->triangles.reserve(indices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			mesh->vertices.push_back(Vector3f(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z));
			mesh->normals.push_back(Vector3f(vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z));
			mesh->uv[0].push_back(Vector2f(vertices[i].textureCoordinate.x, vertices[i].textureCoordinate.y));
		}
		for (size_t i = 0; i < indices.size(); i++)
		{
			mesh->triangles.push_back(indices[i]);
		}

		return mesh;
	}

	Ptr<Mesh> Mesh::Box(float xWidth, float yWidth, float zWidth)
	{
		Ptr<Mesh> mesh = Ptr<Mesh>::New();

		std::vector<GeometricPrimitive::VertexType> vertices;
		std::vector<uint16_t> indices;
		GeometricPrimitive::CreateBox(vertices, indices, XMFLOAT3(xWidth, yWidth, zWidth));

		mesh->vertices.reserve(vertices.size());
		mesh->normals.reserve(vertices.size());
		mesh->uv[0].reserve(vertices.size());
		mesh->triangles.reserve(indices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			mesh->vertices.push_back(Vector3f(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z));
			mesh->normals.push_back(Vector3f(vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z));
			mesh->uv[0].push_back(Vector2f(vertices[i].textureCoordinate.x, vertices[i].textureCoordinate.y));
		}
		for (size_t i = 0; i < indices.size(); i++)
		{
			mesh->triangles.push_back(indices[i]);
		}

		return mesh;
	}

	Ptr<Mesh> Mesh::Cone(float radius, float height)
	{
		Ptr<Mesh> mesh = Ptr<Mesh>::New();

		std::vector<GeometricPrimitive::VertexType> vertices;
		std::vector<uint16_t> indices;
		GeometricPrimitive::CreateCone(vertices, indices, 2 * radius, height);

		mesh->vertices.reserve(vertices.size());
		mesh->normals.reserve(vertices.size());
		mesh->uv[0].reserve(vertices.size());
		mesh->triangles.reserve(indices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			mesh->vertices.push_back(Vector3f(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z));
			mesh->normals.push_back(Vector3f(vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z));
			mesh->uv[0].push_back(Vector2f(vertices[i].textureCoordinate.x, vertices[i].textureCoordinate.y));
		}
		for (size_t i = 0; i < indices.size(); i++)
		{
			mesh->triangles.push_back(indices[i]);
		}

		return mesh;
	}

	/////////////////////////////////////////////////

	Ptr<Mesh> Mesh::AssimpLoader::LoadAssimpNode(const aiNode* node, const aiScene* scene)
	{
		Ptr<Mesh> mesh = Ptr<Mesh>::New();
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
			if (LoadAssimpMesh(mesh, aimesh, scene) == false)
				return nullptr;
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			Ptr<Mesh> child = LoadAssimpNode(node->mChildren[i], scene);
			if (child == nullptr)
				return nullptr;
			mesh->subMeshes.push_back(child);
		}
		return mesh;
	}

	bool Mesh::AssimpLoader::LoadAssimpMesh(Ptr<Mesh> mesh, const aiMesh* aimesh, const aiScene* scene)
	{
		auto assetManager = AssetManager::GetInstance();

		for (size_t i = 0; i < aimesh->mNumVertices; i++)
		{
			mesh->vertices.push_back(Vector3f(aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z));
			mesh->normals.push_back(Vector3f(aimesh->mNormals[i].x, aimesh->mNormals[i].y, aimesh->mNormals[i].z));
			mesh->tangents.push_back(Vector3f(aimesh->mTangents[i].x, aimesh->mTangents[i].y, aimesh->mTangents[i].z));

			for (size_t j = 0; j < aimesh->GetNumUVChannels() && j < 4; j++)
			{
				mesh->uv[j].push_back(Vector2f(aimesh->mTextureCoords[j][i].x, aimesh->mTextureCoords[j][i].y));
			}
		}

		for (size_t i = 0; i < aimesh->mNumFaces; i++)
		{
			for (size_t j = 0; j < aimesh->mFaces[i].mNumIndices; j++)
				mesh->triangles.push_back(aimesh->mFaces[i].mIndices[j]);
		}

		// TODO : 支持更多材质样式
		if (aimesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

			aiColor4D diffuse, specular, ambient, emissive;
			ai_real shininess;
			unsigned int max = 1;
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
				mesh->material.diffuse = Vector4f(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular))
				mesh->material.specular = Vector4f(specular.r, specular.g, specular.b, specular.a);
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient))
				mesh->material.ambient = Vector4f(ambient.r, ambient.g, ambient.b, ambient.a);
			if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emissive))
				mesh->material.emissive = Vector4f(emissive.r, emissive.g, emissive.b, emissive.a);
			if (AI_SUCCESS == aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max))
				mesh->material.shininess = shininess;

			for (size_t i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
			{
				aiString path;
				material->GetTexture(aiTextureType_DIFFUSE, i, &path);
				String fullPath = this->dir + "/" + path.data;
				Ptr<Texture> tex = assetManager->CreateTextureFromFile(fullPath);
				if (tex == nullptr)
					return false;

				mesh->material.texture = tex;

				break;  // 目前只支持一张diffuse texture
			}
		}

		return true;
	}

	Ptr<Mesh> Mesh::AssimpLoader::Load(const String& path)
	{
		auto exceptionManager = ExceptionManager::GetInstance();
		this->path = &path;
		this->dir = path.SubString(0, path.LastIndexOf(TEXT('/')));

		Assimp::Importer importer;
		const aiScene* aiscene = importer.ReadFile(path.ToStdString(),
			aiProcess_MakeLeftHanded | aiProcess_Triangulate | aiProcess_CalcTangentSpace
			| aiProcess_GenNormals | aiProcess_ValidateDataStructure | aiProcess_ImproveCacheLocality
			| aiProcess_RemoveRedundantMaterials | aiProcess_FindDegenerates | aiProcess_SortByPType
			| aiProcess_FindInvalidData | aiProcess_GenUVCoords | aiProcess_TransformUVCoords
			| aiProcess_OptimizeMeshes | aiProcess_FixInfacingNormals
			| aiProcess_JoinIdenticalVertices | aiProcess_PreTransformVertices);
		if (aiscene == nullptr)
		{
			exceptionManager->PushException(Ptr<Exception>::New(aiGetErrorString()));
			return nullptr;
		}

		Ptr<Mesh> mesh = this->LoadAssimpNode(aiscene->mRootNode, aiscene);
		if (mesh == nullptr)
			return nullptr;
		mesh->filePath = path;
		return mesh;
	}

	Mesh::Mesh(bool dynamic)
	{
		this->isDynamic = dynamic;
	}

	Ptr<Mesh> Mesh::CreateMeshFromFile(const String& filePath)
	{
		auto exceptionManager = ExceptionManager::GetInstance();

		AssimpLoader loader;
		Ptr<Mesh> mesh = loader.Load(filePath);
		if (mesh == nullptr)
		{
			Ptr<Exception> exception = Ptr<Exception>::New((String)"加载模型文件" + filePath + "失败。原因是:\n"
				+ exceptionManager->GetException()->GetInfo());
			exceptionManager->PushException(exception);
			return nullptr;
		}
		return mesh;
	}
}