#ifndef TH_RENDERER_H
#define TH_RENDERER_H

#include "THRenderer.h"
#include "THShadowMap.h"
#include <Graphic\THDevice.h>
#include <Core\THGameObject.h>
#include <Core\THEnvironment.h>
#include <Core\THGame.h>
#include <Core\THCamera.h>
#include <Asset\THShader.h>
#include <Asset\THFloatTexture.h>

namespace THEngine
{
	void Renderer::SetupRenderState(Ptr<GameObject> obj)
	{
		auto device = Device::GetInstance();
	}

	void Renderer::SetupWorldTransform(Ptr<GameObject> object)
	{
		Device::GetInstance()->SetWorldMatrix(object->finalWorldTransform);
	}

	////////////////////////////////////////////////////////////////////

	void Renderer3D::SetupShaderParams(Ptr<GameObject> obj)
	{
		auto device = Device::GetInstance();

		SetupWorldTransform(obj);

		Vector4f argb;
		argb.x = obj->GetAlpha();
		argb.y = obj->GetColor().x;
		argb.z = obj->GetColor().y;
		argb.w = obj->GetColor().z;

		auto renderState = device->GetRenderState();

		Matrix mv = renderState->GetWorldMatrix() * renderState->GetViewMatrix();
		Matrix normalMatrix = renderState->GetWorldMatrix();
		normalMatrix.Inverse();
		normalMatrix.Transpose();

		this->shader->Use();

		this->shader->SetFloat4("TH_argb", argb);
		this->shader->SetBoolean("TH_fogEnabled", renderState->IsFogEnabled());
		this->shader->SetValue("TH_fog", (void*)&renderState->GetFog(), sizeof(Fog));
		this->shader->SetMatrix("TH_worldMatrix", renderState->GetWorldMatrix());
		this->shader->SetMatrix("TH_viewMatrix", renderState->GetViewMatrix());
		this->shader->SetMatrix("TH_mvMatrix", mv);
		this->shader->SetMatrix("TH_normalMatrix", normalMatrix);
		this->shader->SetMatrix("TH_projection", renderState->GetProjectionMatrix());

		//setup lights
		auto config = Game::GetInstance()->GetConfig();
		if (config->useLighting && renderState->IsLightingEnabled())
		{
			//setup ambient light
			if (renderState->GetForwardRenderingState().IsRenderingAmbient())
			{
				const Vector4f& ambient = renderState->GetAmbientLight();
				this->shader->SetFloat4("TH_ambientLight", ambient);
				this->shader->SetInt("TH_lightType", Light::AMBIENT);
			}
			else
			{
				auto light = renderState->GetForwardRenderingState().GetCurrentLight();
				switch (light->GetType())
				{
				case Light::DIRECTIONAL:
					SetupDirLight(reinterpret_cast<DirectionalLight*>(light.Get()));
					break;
				default:
					throw std::runtime_error("not implemented");
				}
			}
		}
		else
		{
			this->shader->SetInt("TH_lightType", Light::NONE);
		}
	}

	void Renderer3D::SetupDirLight(Ptr<DirectionalLight> dirLight)
	{
		struct DirectionalLight_For_Render
		{
			Vector4f color;
			Vector3f direction;
		};

		auto device = Device::GetInstance();
		auto renderState = device->GetRenderState();

		DirectionalLight_For_Render lightForRender;
		lightForRender.color.x = dirLight->GetColor().x;
		lightForRender.color.y = dirLight->GetColor().y;
		lightForRender.color.z = dirLight->GetColor().z;
		lightForRender.color.w = 1.0f;
		lightForRender.direction = dirLight->GetDirection();
		lightForRender.direction = lightForRender.direction.Normalize();

		auto config = Game::GetInstance()->GetConfig();

		this->shader->SetInt("TH_lightType", Light::DIRECTIONAL);
		this->shader->SetValue("TH_directionalLight", &lightForRender, sizeof(DirectionalLight_For_Render));
		this->shader->SetBoolean("TH_shadowEnabled", config->useShadow);

		if (config->useShadow)
		{
			auto& forwardRenderingState = renderState->GetForwardRenderingState();
			auto shadowMap = forwardRenderingState.GetShadowMap();
			this->shader->SetMatrix("TH_lightVP", shadowMap->GetLightView() * shadowMap->GetLightProjection());
			this->shader->SetTexture("TH_shadowMap", shadowMap->GetShadowMap().Get());
			this->shader->SetInt("TH_shadowMapWidth", shadowMap->GetShadowMap()->GetWidth());
			this->shader->SetInt("TH_shadowMapHeight", shadowMap->GetShadowMap()->GetHeight());
		}
	}
}

#endif