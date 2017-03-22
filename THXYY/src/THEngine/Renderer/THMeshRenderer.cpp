#include "THMeshRenderer.h"
#include "../Platform/THApplication.h"
#include "../Asset/THAssetManager.h"

namespace THEngine
{
	MeshRenderer::MeshRenderer()
	{

	}

	MeshRenderer::~MeshRenderer()
	{

	}

	MeshRenderer* MeshRenderer::Create()
	{
		MeshRenderer* renderer = new MeshRenderer();
		if (renderer)
		{
			auto assetManager = AssetManager::GetInstance();

			renderer->meshShader = assetManager->CreateShaderFromFile("fx/mesh.fx");
			if (renderer->meshShader)
			{
				renderer->meshShader->SetTechnique("Mesh");
			}
			else
			{
				delete renderer;
				return nullptr;
			}

		}
		return renderer;
	}

	void MeshRenderer::SetupRenderState()
	{
		auto app = Application::GetInstance();
		auto device = app->GetDevice();
		auto renderState = app->GetRenderState();

		if (renderState->IsLightingEnabled())
		{
			device->SetRenderState(D3DRS_LIGHTING, true);
		}
		else
		{
			device->SetRenderState(D3DRS_LIGHTING, false);
		}
	}

	void MeshRenderer::SetupShaderParams(Mesh* mesh)
	{
		auto app = Application::GetInstance();

		SetupWorldTransform(mesh);

		Material material = mesh->material;

		float argb[4];
		argb[0] = mesh->alpha;
		argb[1] = mesh->color.x;
		argb[2] = mesh->color.y;
		argb[3] = mesh->color.z;

		auto renderState = app->GetRenderState();

		Matrix mv = renderState->GetWorldMatrix() * renderState->GetViewMatrix();
		Matrix normalMatrix = mv;
		normalMatrix.Inverse();
		normalMatrix.Transpose();

		if (mesh->mesh == nullptr)
		{
			meshShader->SetTexture("tex", material.texture);
			meshShader->SetBoolean("hasTexture", true);
		}

		meshShader->Use();

		meshShader->SetFloatArray("argb", argb, 4);
		meshShader->SetBoolean("fogEnable", renderState->IsFogEnabled());
		meshShader->SetValue("fog", (void*)&renderState->GetFog(), sizeof(Fog));
		meshShader->SetMatrix("mvMatrix", mv);
		meshShader->SetMatrix("normalMatrix", normalMatrix);
		meshShader->SetMatrix("projection", renderState->GetProjectionMatrix());
	}

	void MeshRenderer::DrawMesh(Mesh* mesh)
	{
		meshShader->UsePass(0);
		mesh->DrawGeometry();
		meshShader->EndPass();
	}

	void MeshRenderer::ShadeWithAmbient(Mesh* mesh, const Vector4f& ambient)
	{	
		meshShader->SetTechnique("Ambient");
		meshShader->SetFloat4("ambientLight", ambient);
		DrawMesh(mesh);
	}

	void MeshRenderer::ShadeWithLight(Mesh* mesh, Light* light)
	{
		struct DirectionalLight_For_Render
		{
			Vector4f color;
			Vector3f direction;
		};

		auto app = Application::GetInstance();
		auto renderState = app->GetRenderState();

		switch (light->GetType())
		{
		case Light::DIRECTIONAL:
		{
			DirectionalLight_For_Render lightForRender;
			lightForRender.color.x = light->GetColor().x;
			lightForRender.color.y = light->GetColor().y;
			lightForRender.color.z = light->GetColor().z;
			lightForRender.color.w = 1.0f;

			DirectionalLight* dirLight = (DirectionalLight*)light;
			Vector4f lightDirInView;
			lightDirInView.x = dirLight->GetDirection().x;
			lightDirInView.y = dirLight->GetDirection().y;
			lightDirInView.z = dirLight->GetDirection().z;
			lightDirInView.w = 0;
			lightDirInView *= renderState->GetViewMatrix();
			lightForRender.direction.x = lightDirInView.x;
			lightForRender.direction.y = lightDirInView.y;
			lightForRender.direction.z = lightDirInView.z;

			meshShader->SetTechnique("Directional");
			meshShader->SetValue("directionalLight", &lightForRender, sizeof(DirectionalLight_For_Render));
			break;
		}
		default:
			throw std::runtime_error("not implemented.");
			break;
		}

		DrawMesh(mesh);
	}

	void MeshRenderer::Shade(Mesh* mesh)
	{
		auto app = Application::GetInstance();
		auto renderState = app->GetRenderState();

		if (renderState->IsLightingEnabled())
		{
			if (isRenderingAmbient)
			{
				ShadeWithAmbient(mesh, renderState->GetAmbientLight());
			}
			else
			{
				ShadeWithLight(mesh, this->currentLight);
			}
		}

		else
		{
			DrawMesh(mesh);
		}
	}

	void MeshRenderer::Render(GameObject* object)
	{
		Mesh* mesh = (Mesh*)object;
		auto app = Application::GetInstance();

		SetupShaderParams(mesh);

		Shade(mesh);
	}
}