#include "THShadowRenderer.h"
#include "THRenderQueue.h"
#include <Graphic\THDevice.h>
#include <Graphic\THBuffers.h>
#include <Asset\THAssetManager.h>
#include <Asset\THShaderStock.h>
#include <Asset\THFloatTexture.h>
#include <Core\THGame.h>
#include <Core\THCamera.h>
#include <Util\THPicker.h>
#include <limits>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace THEngine
{
	////////////////////////////////////////////////
	ShadowRenderer::ShadowRenderer()
	{
	}

	ShadowRenderer::~ShadowRenderer()
	{
	}

	void ShadowRenderer::Render(Ptr<GameObject> obj)
	{
		obj->DrawShadowMap();
	}

	void ShadowRenderer::Begin()
	{
		auto device = Device::GetInstance();
		auto renderState = device->GetRenderState();

		//store the  matrices
		this->projPrev = renderState->GetProjectionMatrix();
		this->viewPrev = renderState->GetViewMatrix();
		this->renderTargetPrev = renderState->GetRenderTarget();
		this->viewportPrev = renderState->GetViewport();
		this->depthTestEnabledPrev = renderState->IsDepthTestEnabled();
		this->blendModePrev = renderState->GetBlendMode();
		this->depthBufferPrev = renderState->GetDepthBuffer();

		BlendMode blendMode;
		blendMode.srcFactor = BlendFactor::ONE;
		blendMode.destFactor = BlendFactor::ZERO;
		device->SetBlendMode(blendMode);

		device->SetDepthBuffer(depthBuffer);

		ShaderStock::GetInstance()->GetShadowShader()->Use();
	}

	void ShadowRenderer::End()
	{
		auto device = Device::GetInstance();

		device->SetRenderTarget(this->renderTargetPrev);
		device->SetProjectionMatrix(this->projPrev);
		device->SetViewMatrix(this->viewPrev);
		device->SetViewport(this->viewportPrev.x, this->viewportPrev.y, this->viewportPrev.width, this->viewportPrev.height);
		device->SetDepthBuffer(this->depthBufferPrev);
		device->EnableDepthTest(this->depthTestEnabledPrev);
		device->SetBlendMode(this->blendModePrev);

		//device->GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	/////////////////////////////////////////////////
	DirLightShadowRenderer::DirLightShadowRenderer()
	{
	}

	DirLightShadowRenderer::~DirLightShadowRenderer()
	{
	}

	Ptr<DirLightShadowRenderer> DirLightShadowRenderer::Create()
	{
		DirLightShadowRenderer* r = (DirLightShadowRenderer*)malloc(sizeof(DirLightShadowRenderer));
		new(r) DirLightShadowRenderer();
		Ptr<DirLightShadowRenderer> renderer = Ptr<DirLightShadowRenderer>::Create_NoRetain(r);
		auto assetManager = AssetManager::GetInstance();

		for (int i = 0; i < MAX_CASCADED_LEVEL; i++)
		{
			Ptr<ShadowMap> shadowMap = ShadowMap::Create(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
			if (shadowMap == nullptr)
			{
				ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建shadow map失败。")));
				return nullptr;
			}
			renderer->cascadedShadowMaps.Add(shadowMap);
		}

		renderer->depthBuffer = Device::GetInstance()->CreateDepthBuffer(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
		if (renderer->depthBuffer == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建shadow map深度缓存失败。")));
			return nullptr;
		}

		return renderer;
	}

	void DirLightShadowRenderer::RenderShadow(Ptr<RenderQueue> renderQueue)
	{
		auto device = Device::GetInstance();

		Begin();
		SetupLightView();

		for (int i = 0; i < MAX_CASCADED_LEVEL; i++)
		{
			SetupLightProjection(i);
			device->SetRenderTarget(this->cascadedShadowMaps.Get(i)->GetShadowMap().Get());
			device->ClearDepthBuffer();
			device->ClearRenderTarget(Vector4f(1, 1, 0, 1));
			device->EnableDepthTest(true);
			device->SetViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

			auto objects = renderQueue->GetObjects();
			auto iter = objects->GetIterator();
			while (iter->HasNext())
			{
				auto obj = iter->Next();
				Render(obj);
			}
		}
		End();
	}

	void DirLightShadowRenderer::SetupLightView()
	{
		auto device = Device::GetInstance();

		Vector3f up;
		if (light->GetDirection().x == 0 && light->GetDirection().y == 0)
		{
			up.x = 0;
			up.y = 1;
			up.z = 0;
		}
		else
		{
			up.x = -light->GetDirection().y;
			up.y = light->GetDirection().x;
			up.z = 0;
		}
		Matrix::LookAt(&this->lightView, -10000 * light->GetDirection(), Vector3f(0, 0, 0), up);
		device->SetViewMatrix(this->lightView);

		auto iter = this->cascadedShadowMaps.GetIterator();
		while (iter->HasNext())
		{
			iter->Next()->lightView = this->lightView;
		}
	}

	void DirLightShadowRenderer::SetupLightProjection(int cascadedLevel)
	{
		auto device = Device::GetInstance();

		Vector3f frustumVerts[8];
		ComputeFrustum(cascadedLevel, frustumVerts);

		Vector3f center;
		float radius;
		FindBoundingSphere(frustumVerts, 8, center, radius);

		Vector4f center4;
		center4.x = center.x;
		center4.y = center.y;
		center4.z = center.z;
		center4.w = 1;

		//transform to light space
		center4 *= this->lightView;

		center.x = center4.x;
		center.y = center4.y;
		center.z = center4.z;

		BoundingBox bbox;
		FindAABBForSphere(center, radius, bbox);

		//round the projection bound to elimiate shadow flickering
		float clipWidth = std::round(bbox.xmax - bbox.xmin);
		float clipHeight = std::round(bbox.ymax - bbox.ymin);
		if (fabs(clipWidth - clipHeight) > 1e-3)
		{
			int test = 1;
		}
		const float dx = clipWidth * (1.0f / SHADOW_MAP_SIZE);
		const float dy = clipHeight * (1.0f / SHADOW_MAP_SIZE);

		bbox.xmin = floor(bbox.xmin / dx) * dx;
		bbox.xmax = bbox.xmin + clipWidth;
		bbox.ymin = floor(bbox.ymin / dy) * dy;
		bbox.ymax = bbox.ymin + clipHeight;

		auto shadowMap = this->cascadedShadowMaps.Get(cascadedLevel);
		Matrix::Ortho(&shadowMap->lightProjection, bbox.xmin, bbox.xmax, bbox.ymin, bbox.ymax,
			bbox.zmin, bbox.zmax);
		device->SetProjectionMatrix(shadowMap->lightProjection);
	}

	void DirLightShadowRenderer::ComputeFrustum(int cascadedLevel, Vector3f* output)
	{
		auto device = Device::GetInstance();
		auto camera = (Camera3D*)(device->GetRenderState()->GetCamera().Get());
		Picker picker(camera);
		int width = camera->GetViewport().Width();
		int height = camera->GetViewport().Height();

		Vector3f lb = picker.GenerateRay(0, 0);
		Vector3f lt = picker.GenerateRay(0, height);
		Vector3f rb = picker.GenerateRay(width, 0);
		Vector3f rt = picker.GenerateRay(width, height);

		float y = tan(Math::ToRad(camera->GetFov() * 0.5f));
		float x = y * width / height;
		float dist = sqrt(1 + y * y + x * x);
		float distDelta = (camera->GetZFar() - camera->GetZNear()) / MAX_CASCADED_LEVEL * dist;
		float distNear = dist * camera->GetZNear() + cascadedLevel * distDelta;
		float distFar = distNear + distDelta;

		output[0] = lb * distNear + camera->GetPosition();
		output[1] = lb * distFar + camera->GetPosition();
		output[2] = lt * distNear + camera->GetPosition();
		output[3] = lt * distFar + camera->GetPosition();
		output[4] = rb * distNear + camera->GetPosition();
		output[5] = rb * distFar + camera->GetPosition();
		output[6] = rt * distNear + camera->GetPosition();
		output[7] = rt * distFar + camera->GetPosition();
	}

	void DirLightShadowRenderer::FindBoundingSphere(const Vector3f* vertices,
		int size, Vector3f& center, float& radius)
	{
		center = Vector3f(0, 0, 0);
		for (int i = 0; i < size; i++)
			center += vertices[i];
		center /= size;

		radius = 0;
		for (int i = 0; i < size; i++)
		{
			float temp = (center - vertices[i]).Norm();
			if (temp > radius)
				radius = temp;
		}
	}

	void DirLightShadowRenderer::FindAABBForSphere(const Vector3f& center, float radius, BoundingBox& bbox)
	{
		bbox.xmin = center.x - radius;
		bbox.xmax = center.x + radius;
		bbox.ymin = center.y - radius;
		bbox.ymax = center.y + radius;
		bbox.zmin = center.z - radius;
		bbox.zmax = center.z + radius;
	}

	void DirLightShadowRenderer::CreateVerticesFromAABB(const BoundingBox& bbox, Vector4f* output)
	{
		for (int i = 0; i < 8; i++)
		{
			output[i].w = 1.0f;
		}
		output[0].x = bbox.xmin;
		output[0].y = bbox.ymin;
		output[0].z = bbox.zmin;
		output[1].x = bbox.xmin;
		output[1].y = bbox.ymin;
		output[1].z = bbox.zmax;
		output[2].x = bbox.xmin;
		output[2].y = bbox.ymax;
		output[2].z = bbox.zmin;
		output[3].x = bbox.xmin;
		output[3].y = bbox.ymax;
		output[3].z = bbox.zmax;
		output[4].x = bbox.xmax;
		output[4].y = bbox.ymin;
		output[4].z = bbox.zmin;
		output[5].x = bbox.xmax;
		output[5].y = bbox.ymin;
		output[5].z = bbox.zmax;
		output[6].x = bbox.xmax;
		output[6].y = bbox.ymax;
		output[6].z = bbox.zmin;
		output[7].x = bbox.xmax;
		output[7].y = bbox.ymax;
		output[7].z = bbox.zmax;
	}
}