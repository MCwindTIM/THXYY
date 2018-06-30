#include "THMeshObject.h"
#include <Core\THGame.h>
#include <Graphic\THDevice.h>
#include <Asset\THMesh.h>
#include <Asset\THShader.h>
#include <Asset\THShaderStock.h>
#include <Renderer\THRenderPipeline.h>
#include <Renderer\THMeshRenderer.h>

namespace THEngine
{
	MeshObject::MeshObject()
	{
	}

	MeshObject::MeshObject(const MeshObject& mesh) : GameObject(mesh)
	{
		// TODO
		this->mesh = mesh.mesh;
	}

	MeshObject::~MeshObject()
	{
	}

	void MeshObject::SendToRenderQueue()
	{
		Game::GetInstance()->GetRenderPipeline()->SendToRenderQueue(RenderPipeline::NORMAL, this);
	}

	void MeshObject::Update()
	{
		GameObject::Update();
	}

	void MeshObject::Draw()
	{
		Game::GetInstance()->GetRenderPipeline()->GetMeshRenderer()->Render(this);
	}

	void MeshObject::DrawShadowMap()
	{
		auto shader = ShaderStock::GetInstance()->GetShadowShader();
		auto renderState = Device::GetInstance()->GetRenderState();

		Matrix mvMatrix = this->finalWorldTransform * renderState->GetViewMatrix();

		shader->Use();
		shader->UsePass(0);
		shader->SetMatrix("mvMatrix", mvMatrix);
		shader->SetMatrix("projection", renderState->GetProjectionMatrix());
		shader->CommitChanges();

		DrawGeometry();
	}

	void MeshObject::DrawGeometry()
	{
		this->mesh->DrawGeometry();
	}

	Ptr<Object> MeshObject::Clone() const
	{
		return Ptr<MeshObject>::New(*this).Get();
	}
}