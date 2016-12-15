#include "THMesh.h"
#include "../../Core/THGame.h"

namespace THEngine
{
	Mesh::Mesh()
	{

	}

	Mesh::Mesh(const Mesh& mesh) : RenderObject(mesh)
	{
		vertexCount = mesh.vertexCount;
		material = mesh.material;
		primitiveType = mesh.primitiveType;

		if (mesh.mesh)
		{
			this->mesh = (D3DMesh*)mesh.mesh->Clone();
			this->mesh->Retain();
		}

		if (mesh.vertexBuffer)
		{
			InitVertexBuffer(vertexCount);

			void* src;
			mesh.vertexBuffer->Lock(0, 0, &src, D3DLOCK_READONLY | D3DLOCK_NOOVERWRITE);

			SetVertexData(src);

			mesh.vertexBuffer->Unlock();
		}
	}

	Mesh::~Mesh()
	{
		TH_SAFE_RELEASE(mesh);
		TH_SAFE_RELEASE(vertexBuffer);
		TH_SAFE_RELEASE(indexBuffer);
	}

	void Mesh::SendToRenderQueue()
	{
		Game::GetInstance()->SendToRenderQueue(Game::NORMAL, this);
	}

	void Mesh::InitVertexBuffer(int size)
	{
		auto device = Application::GetInstance()->GetDevice();

		device->CreateVertexBuffer(size * sizeof(MeshVertex), 0,
			D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &vertexBuffer, nullptr);

		vertexCount = size;
	}

	void Mesh::SetVertexData(void* data)
	{
		void* lockedBuffer;
		vertexBuffer->Lock(0, vertexCount * sizeof(MeshVertex), &lockedBuffer, D3DLOCK_DISCARD);

		memcpy(lockedBuffer, data, vertexCount * sizeof(MeshVertex));

		vertexBuffer->Unlock();
	}

	void Mesh::Update()
	{
		RenderObject::Update();
	}

	void Mesh::Draw()
	{
		Game::GetInstance()->GetMeshRenderer()->Render(this);
	}

	Mesh* Mesh::CreateMeshFromFile(String filePath)
	{
		auto exceptionManager = ExceptionManager::GetInstance();

		Mesh* mesh = new Mesh();

		String ext = filePath.SubString(filePath.LastIndexOf(TCHAR('.')) + 1, filePath.GetLength());
		if (ext == "x")
		{
			if (mesh->LoadFromX(filePath) == false)
			{
				Exception* exception = new Exception((String)"����ģ���ļ�ʧ�ܣ�" + filePath + "ԭ����:\n" 
					+ exceptionManager->GetException()->GetInfo());
				exceptionManager->PushException(exception);
				delete mesh;
				return nullptr;
			}
		}
		else
		{
			Exception* exception = new Exception("��֧�ֵ��ļ���ʽ��");
			exceptionManager->PushException(exception);
			delete mesh;
			return nullptr;
		}
		return mesh;
	}

	bool Mesh::LoadFromX(String filePath)
	{
		this->mesh = D3DMesh::LoadMesh(filePath);
		if (this->mesh)
		{
			this->mesh->Retain();
			return true;
		}
		return false;
	}

	Object* Mesh::Clone()
	{
		return new Mesh(*this);
	}

	//////////////////////////////////////////////////////////////////////
	Mesh::D3DMesh::D3DMesh()
	{
	
	}

	Mesh::D3DMesh::D3DMesh(const D3DMesh& d3dMesh) : Object(d3dMesh)
	{
		auto device = Application::GetInstance()->GetDevice();

		IDirect3DVertexBuffer9* vb;
		D3DVERTEXBUFFER_DESC vbdesc;
		d3dMesh.mesh->GetVertexBuffer(&vb);
		vb->GetDesc(&vbdesc);
		vb->Release();

		d3dMesh.mesh->CloneMeshFVF(D3DXMESH_MANAGED, vbdesc.FVF, device, &mesh);

		this->numMaterials = d3dMesh.numMaterials;
		this->materialList = d3dMesh.materialList;
		this->isCloned = true;
	}

	Mesh::D3DMesh::~D3DMesh()
	{
		auto assetManager = AssetManager::GetInstance();

		if (isCloned == false && materialList)
		{
			for (int i = 0; i < numMaterials; i++)
			{
				assetManager->DestroyTexture(materialList[i].texture);
			}
			delete[] materialList;
		}

		if (mesh)
		{
			mesh->Release();
		}
	}

	Mesh::D3DMesh* Mesh::D3DMesh::LoadMesh(String filePath)
	{
		D3DMesh* d3dMesh = new D3DMesh();

		auto device = Application::GetInstance()->GetDevice();
		auto exceptionManager = ExceptionManager::GetInstance();

		ID3DXBuffer* adjacency = nullptr;
		ID3DXBuffer* materialBuffer = nullptr;
		DWORD numMaterials;

		if (FAILED(D3DXLoadMeshFromX(filePath.GetBuffer(), D3DXMESH_MANAGED, device, &adjacency, &materialBuffer ,
			nullptr, &numMaterials, &d3dMesh->mesh)))
		{
			Exception* exception = new Exception("�޷�����ģ���ļ����ļ��������𻵡�");
			exceptionManager->PushException(exception);
			delete d3dMesh;
			return nullptr;
		}

		//�Ż�����
		if (FAILED(d3dMesh->mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)adjacency->GetBufferPointer(), nullptr, nullptr, nullptr)))
		{
			Exception* exception = new Exception("ģ���Ż�ʧ�ܡ�");
			exceptionManager->PushException(exception);
			delete d3dMesh;
			return nullptr;
		}

		//��������
		auto assetManager = AssetManager::GetInstance();
		d3dMesh->materialList = new Material[numMaterials];
		d3dMesh->numMaterials = numMaterials;

		D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
		String folder = filePath.SubString(0, filePath.LastIndexOf(TCHAR('/')) + 1);
		for (int i = 0; i < d3dMesh->numMaterials; i++)
		{
			if (materials[i].pTextureFilename)
			{
				String path = folder + materials[i].pTextureFilename;
				d3dMesh->materialList[i].texture = assetManager->CreateTextureFromFile(path, true);
				if (d3dMesh->materialList[i].texture == nullptr)
				{
					delete d3dMesh;
					return nullptr;
				}
			}		
			d3dMesh->materialList[i].ambient[0] = materials[i].MatD3D.Diffuse.r;
			d3dMesh->materialList[i].ambient[1] = materials[i].MatD3D.Diffuse.g;
			d3dMesh->materialList[i].ambient[2] = materials[i].MatD3D.Diffuse.b;
			d3dMesh->materialList[i].ambient[3] = materials[i].MatD3D.Diffuse.a;
			d3dMesh->materialList[i].diffuse[0] = materials[i].MatD3D.Diffuse.r;
			d3dMesh->materialList[i].diffuse[1] = materials[i].MatD3D.Diffuse.g;
			d3dMesh->materialList[i].diffuse[2] = materials[i].MatD3D.Diffuse.b;
			d3dMesh->materialList[i].diffuse[3] = materials[i].MatD3D.Diffuse.a;
			d3dMesh->materialList[i].specular[0] = materials[i].MatD3D.Specular.r;
			d3dMesh->materialList[i].specular[1] = materials[i].MatD3D.Specular.g;
			d3dMesh->materialList[i].specular[2] = materials[i].MatD3D.Specular.b;
			d3dMesh->materialList[i].specular[3] = materials[i].MatD3D.Specular.a;
			d3dMesh->materialList[i].emissive[0] = materials[i].MatD3D.Emissive.r;
			d3dMesh->materialList[i].emissive[1] = materials[i].MatD3D.Emissive.g;
			d3dMesh->materialList[i].emissive[2] = materials[i].MatD3D.Emissive.b;
			d3dMesh->materialList[i].emissive[3] = materials[i].MatD3D.Emissive.a;
			d3dMesh->materialList[i].power = materials[i].MatD3D.Power;
		}

		//float* data = new float[100000];
		//d3dMesh->mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&data);

		return d3dMesh;
	}

	Object* Mesh::D3DMesh::Clone()
	{
		return new D3DMesh(*this);
	}
}