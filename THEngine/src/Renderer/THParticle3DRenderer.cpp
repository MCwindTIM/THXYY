#include "THParticle3DRenderer.h"
#include <Core\THParticle3D.h>
#include <Core\THGame.h>
#include <Asset\THShaderStock.h>
#include <Asset\THTexture.h>
#include <Asset\THShader.h>
#include <Graphic\THDevice.h>
#include <Graphic\THBuffers.h>
#include <Graphic\THVertexFormat.h>

using namespace THEngine;

Particle3DRenderer::Particle3DRenderer()
{
}

Particle3DRenderer::~Particle3DRenderer()
{
}

Ptr<Particle3DRenderer> Particle3DRenderer::Create()
{
	Particle3DRenderer* r = (Particle3DRenderer*)malloc(sizeof(Particle3DRenderer));
	new(r) Particle3DRenderer();
	Ptr<Particle3DRenderer> renderer = Ptr<Particle3DRenderer>::Create_NoRetain(r);
	if (renderer)
	{
		auto device = Device::GetInstance();
		renderer->vb = device->CreateDynamicVertexBuffer(4 * sizeof(ParticleVertex));
		if (renderer->vb == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建顶点缓存失败。")));
			return nullptr;
		}

		std::vector<VertexFormatItem> vfitems;
		vfitems.push_back(VertexFormatItem(0, DataType::FLOAT3, Semantic::POSITION, 0, 0));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 3, DataType::FLOAT4, Semantic::COLOR, 0, 0));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 7, DataType::FLOAT2, Semantic::TEXCOORD, 0, 0));
		renderer->format = device->CreateVertexFormat(vfitems, ShaderStock::GetInstance()->GetSpriteShader(), "Sprite", 0);
		if (renderer->format == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建顶点格式失败。")));
			return nullptr;
		}
	}
	return renderer;
}

void Particle3DRenderer::Render(Ptr<GameObject> obj)
{
	Particle3D* particle = (Particle3D*)obj.Get();

	auto spriteShader = ShaderStock::GetInstance()->GetSpriteShader();
	auto device = Device::GetInstance();

	const int texWidth = particle->texture->GetWidth();
	const int texHeight = particle->texture->GetHeight();

	float width = particle->texRect.Width();
	float height = particle->texRect.Height();

	//Transform to texture coordinates
	double left = particle->texRect.left * 1.0 / texWidth;
	double top = particle->texRect.top * 1.0 / texHeight;
	double right = particle->texRect.right * 1.0 / texWidth;
	double bottom = particle->texRect.bottom * 1.0 / texHeight;

	if (left == 0 && top == 0 && right == 0 && bottom == 0)
	{
		width = particle->texture->GetImageWidth();
		height = particle->texture->GetImageHeight();
		left = top = 0;
		right = width / texWidth;
		bottom = height / texHeight;
	}

	float x = -width * particle->pivot.x;
	float y = -height * particle->pivot.y;
	float z = 0;

	ParticleVertex* vertices = reinterpret_cast<ParticleVertex*>(vb->Lock());
	auto& color = particle->GetColor();
	vertices[0] = ParticleVertex(x, y, z, color.x, color.y, color.z, particle->alpha, left, bottom);
	vertices[1] = ParticleVertex(x + width, y, z, color.x, color.y, color.z, particle->alpha, right, bottom);
	vertices[2] = ParticleVertex(x, y + height, z, color.x, color.y, color.z, particle->alpha, left, top);
	vertices[3] = ParticleVertex(x + width, y + height, z, color.x, color.y, color.z, particle->alpha, right, top);
	vb->UnLock();

	device->SetWorldMatrix(particle->finalWorldTransform);

	device->SetVertexFormat(this->format);
	device->SetVertexBuffer(this->vb.Get(), sizeof(ParticleVertex), 0);

	auto renderState = device->GetRenderState();

	spriteShader->Use();

	spriteShader->SetTexture("tex", particle->texture);
	spriteShader->SetMatrix("world", renderState->GetWorldMatrix());
	spriteShader->SetMatrix("projection", renderState->GetProjectionMatrix());
	spriteShader->SetMatrix("view", renderState->GetViewMatrix());

	spriteShader->CommitChanges();
	spriteShader->UsePass(0);
	device->Draw(PrimitiveType::TRIANGLE_STRIP, 4, 0);
}