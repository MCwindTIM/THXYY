#include "THSkyBoxRenderer.h"
#include <Core\THLayer.h>
#include <Core\THGame.h>
#include <Core\THCamera.h>
#include <Asset\THShaderStock.h>
#include <Asset\THShader.h>
#include <Graphic\THDevice.h>
#include <Graphic\THVertexFormat.h>
#include <Graphic\THBuffers.h>

namespace THEngine
{
	SkyBoxRenderer::SkyBoxRenderer()
	{
	}

	SkyBoxRenderer::~SkyBoxRenderer()
	{
	}

	Ptr<SkyBoxRenderer> SkyBoxRenderer::Create()
	{
		SkyBoxRenderer* r = (SkyBoxRenderer*)malloc(sizeof(SkyBoxRenderer));
		new(r) SkyBoxRenderer();
		Ptr<SkyBoxRenderer> renderer = Ptr<SkyBoxRenderer>::Create_NoRetain(r);
		if (renderer != nullptr)
		{
			auto device = Device::GetInstance();
			renderer->vb = device->CreateDynamicVertexBuffer(4 * sizeof(SkyBoxVertex));
			if (renderer->vb == nullptr)
			{
				ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建顶点缓存失败。")));
				return nullptr;
			}
			std::vector<VertexFormatItem> vfitems;
			vfitems.push_back(VertexFormatItem(0, DataType::FLOAT3, Semantic::POSITION, 0, 0));
			renderer->format = device->CreateVertexFormat(vfitems, ShaderStock::GetInstance()->GetSkyBoxShader(), "SkyBox", 0);
			if (renderer->format == nullptr)
			{
				auto exceptionManager = ExceptionManager::GetInstance();
				exceptionManager->PushException(Ptr<Exception>::New((String)"创建顶点格式失败。原因是：\n"
					+ exceptionManager->GetException()->GetInfo()));
				return nullptr;
			}
		}
		return renderer;
	}

	void SkyBoxRenderer::RenderSkyBox(Ptr<Camera3D> camera, Ptr<Layer> layer)
	{
		Ptr<CubeMap> skyBox = layer->GetSkyBox();

		auto skyBoxShader = ShaderStock::GetInstance()->GetSkyBoxShader();
		auto device = Device::GetInstance();
		auto renderState = device->GetRenderState();
		auto& viewport = renderState->GetViewport();

		Matrix matrix;
		Matrix::Ortho(&matrix, 0, viewport.width, 0, viewport.height, 0, TH_MAX_Z);
		device->SetProjectionMatrix(matrix);

		Matrix::Identity(&matrix);
		device->SetWorldMatrix(matrix);
		device->SetViewMatrix(matrix);

		SkyBoxVertex* vertices = reinterpret_cast<SkyBoxVertex*>(vb->Lock());
		vertices[0] = SkyBoxVertex(0, 0, 1);
		vertices[1] = SkyBoxVertex(viewport.width, 0, 1);
		vertices[2] = SkyBoxVertex(0, viewport.height, 1);
		vertices[3] = SkyBoxVertex(viewport.width, viewport.height, 1);
		vb->UnLock();

		device->SetVertexFormat(this->format);
		device->SetVertexBuffer(this->vb.Get(), sizeof(SkyBoxVertex), 0);

		skyBoxShader->Use();

		skyBoxShader->SetFloat("fov", camera->GetFov());
		skyBoxShader->SetFloat3("lookAt", camera->final_lookAt - camera->final_position);
		skyBoxShader->SetFloat3("up", camera->final_up);
		skyBoxShader->SetCubeMap("skyBox", skyBox);
		skyBoxShader->SetInt("viewportWidth", viewport.width);
		skyBoxShader->SetInt("viewportHeight", viewport.height);
		skyBoxShader->SetMatrix("world", renderState->GetWorldMatrix());
		skyBoxShader->SetMatrix("projection", renderState->GetProjectionMatrix());
		skyBoxShader->SetMatrix("view", renderState->GetViewMatrix());

		skyBoxShader->UsePass(0);
		device->Draw(PrimitiveType::TRIANGLE_STRIP, 4, 0);
		skyBoxShader->EndPass();

		device->ClearDepthBuffer();
	}
}