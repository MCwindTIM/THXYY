#include "THMesh.h"
#include "../../Core/THGame.h"

namespace THEngine
{
	Mesh::Mesh()
	{

	}

	Mesh::~Mesh()
	{
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
}