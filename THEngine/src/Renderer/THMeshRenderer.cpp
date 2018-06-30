#include "THMeshRenderer.h"
#include "THShadowMap.h"
#include "THRenderQueue.h"
#include <Graphic\THDevice.h>
#include <Asset\THAssetManager.h>
#include <Asset\THShaderStock.h>
#include <Asset\THFloatTexture.h>
#include <Asset\THMesh.h>
#include <Core\THCamera.h>
#include <Core\THEnvironment.h>
#include <Core\3D\THMeshObject.h>
#include <Core\THGame.h>
#include <Core\THConfig.h>

namespace THEngine
{
	MeshRenderer::MeshRenderer()
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	Ptr<MeshRenderer> MeshRenderer::Create()
	{
		MeshRenderer* r = (MeshRenderer*)malloc(sizeof(MeshRenderer));
		new(r) MeshRenderer();
		Ptr<MeshRenderer> renderer = Ptr<MeshRenderer>::Create_NoRetain(r);

		renderer->shader = ShaderStock::GetInstance()->GetMeshShader();
		return renderer;
	}

	void MeshRenderer::Render(Ptr<GameObject> object)
	{
		MeshObject* mesh = (MeshObject*)object.Get();

		SetupShaderParams(mesh);

		this->shader->SetValue("g_material", &mesh->mesh->material, sizeof(Material) - sizeof(Ptr<Texture>));
		if (mesh->mesh->material.texture != nullptr)
		{
			this->shader->SetBoolean("g_hasTexture", true);
			this->shader->SetTexture("g_texture", mesh->mesh->material.texture);
		}
		else
		{
			this->shader->SetBoolean("g_hasTexture", false);
		}

		this->shader->Use();
		this->shader->UsePass(0);
		mesh->DrawGeometry();
	}
}