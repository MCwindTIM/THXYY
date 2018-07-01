#include <Asset\THShaderStock.h>
#include <Core\THGame.h>
#include <Core\THSprite.h>
#include <Asset\THTexture.h>
#include <Asset\THShader.h>
#include <Graphic\THDevice.h>
#include <Graphic\THBuffers.h>
#include <Graphic\THVertexFormat.h>
#include "THSpriteRenderer.h"

using namespace THEngine;

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

Ptr<SpriteRenderer> SpriteRenderer::Create()
{
	SpriteRenderer* r = (SpriteRenderer*)malloc(sizeof(SpriteRenderer));
	new(r) SpriteRenderer();
	Ptr<SpriteRenderer> renderer = Ptr<SpriteRenderer>::Create_NoRetain(r);
	if (renderer)
	{
		auto device = Device::GetInstance();

		// create vertex buffer
		renderer->vb = device->CreateDynamicVertexBuffer(4 * sizeof(SpriteVertex));
		if (renderer->vb == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建顶点缓存失败。")));
			return nullptr;
		}

		// create instance buffer
		renderer->instanceBuffer = device->CreateDynamicVertexBuffer(MAX_SPRITE * sizeof(SpriteInstance));
		if (renderer->instanceBuffer == nullptr)
		{
			ExceptionManager::GetInstance()->PushException(Ptr<Exception>::New(("创建instance缓存失败。")));
			return nullptr;
		}

		std::vector<VertexFormatItem> vfitems;
		vfitems.push_back(VertexFormatItem(0, DataType::FLOAT3, "POSITION", 0, 0));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 3, DataType::FLOAT2, "TEXCOORD", 0, 0));
		vfitems.push_back(VertexFormatItem(0, DataType::FLOAT4, "COLOR", 0, 1, true));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 4, DataType::FLOAT4, "WORLD", 0, 1, true));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 8, DataType::FLOAT4, "WORLD", 1, 1, true));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 12, DataType::FLOAT4, "WORLD", 2, 1, true));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 16, DataType::FLOAT4, "WORLD", 3, 1, true));
		renderer->format = device->CreateVertexFormat(vfitems, ShaderStock::GetInstance()->GetSpriteShader(), "Sprite", 0);
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

void SpriteRenderer::SetupRenderState(Ptr<Sprite> obj)
{
	Renderer::SetupRenderState(obj.Get());

	auto device = Device::GetInstance();

	BlendMode blendMode;
	if (obj->blendMode == SpriteBlendMode::ADD)
		blendMode.destFactor = BlendFactor::ONE;
	device->SetBlendMode(blendMode);
}

void SpriteRenderer::Render(Ptr<GameObject> obj)
{
	Ptr<Sprite> sp = (Sprite*)obj.Get();
	if (this->spriteBatch.size() == 0 ||
		(this->spriteBatch[0]->texRect == sp->texRect && this->spriteBatch[0]->texture == sp->texture))
	{
		this->spriteBatch.push_back(sp);
	}
	else
	{
		Flush();
		this->spriteBatch.push_back(sp);
	}
}

void SpriteRenderer::Flush()
{
	if (spriteBatch.size() == 0)
		return;

	// draw batch
	auto game = Game::GetInstance();
	auto device = Device::GetInstance();
	auto spriteShader = ShaderStock::GetInstance()->GetSpriteShader();

	Ptr<Sprite> sprite = spriteBatch[0];
	const int texWidth = sprite->texture->GetWidth();
	const int texHeight = sprite->texture->GetHeight();

	float width = sprite->texRect.Width();
	float height = sprite->texRect.Height();

	//Transform to texture coordinates
	double left = sprite->texRect.left * 1.0 / texWidth;
	double top = sprite->texRect.top * 1.0 / texHeight;
	double right = sprite->texRect.right * 1.0 / texWidth;
	double bottom = sprite->texRect.bottom * 1.0 / texHeight;

	if (left == 0 && top == 0 && right == 0 && bottom == 0)
	{
		width = sprite->texture->GetImageWidth();
		height = sprite->texture->GetImageHeight();
		left = top = 0;
		right = width / texWidth;
		bottom = height / texHeight;
	}

	float x = -width * sprite->pivot.x;
	float y = -height * sprite->pivot.y;
	float z = 0.0f;

	// set vertex buffer data
	SpriteVertex* vertices = reinterpret_cast<SpriteVertex*>(vb->Lock());
	auto& color = sprite->GetColor();
	vertices[0] = SpriteVertex(x, y, z, left, bottom);
	vertices[1] = SpriteVertex(x + width, y, z, right, bottom);
	vertices[2] = SpriteVertex(x, y + height, z, left, top);
	vertices[3] = SpriteVertex(x + width, y + height, z, right, top);
	vb->UnLock();

	// set instance data
	SpriteInstance* instances = reinterpret_cast<SpriteInstance*>(instanceBuffer->Lock());
	for (size_t i = 0; i < spriteBatch.size(); i++)
	{
		Ptr<Sprite> sprite2 = spriteBatch[i];

		instances[i].color = Vector4f(sprite2->color.x, sprite2->color.y, sprite2->color.z, sprite2->GetAlpha());
		float worldMat[16];
		sprite2->finalWorldTransform.Dump(worldMat);
		instances[i].world1 = Vector4f(worldMat[0], worldMat[1], worldMat[2], worldMat[3]);
		instances[i].world2 = Vector4f(worldMat[4], worldMat[5], worldMat[6], worldMat[7]);
		instances[i].world3 = Vector4f(worldMat[8], worldMat[9], worldMat[10], worldMat[11]);
		instances[i].world4 = Vector4f(worldMat[12], worldMat[13], worldMat[14], worldMat[15]);
	}
	instanceBuffer->UnLock();

	device->SetVertexFormat(this->format);
	device->SetVertexBuffer(this->vb.Get(), sizeof(SpriteVertex), 0);
	device->SetVertexBuffer(this->instanceBuffer.Get(), sizeof(SpriteInstance), 1);

	auto renderState = device->GetRenderState();
	spriteShader->Use();
	SetupRenderState(sprite);

	spriteShader->SetTexture("tex", sprite->texture);
	spriteShader->SetMatrix("projection", renderState->GetProjectionMatrix());
	spriteShader->SetMatrix("view", renderState->GetViewMatrix());

	spriteShader->CommitChanges();
	spriteShader->UsePass(0);
	device->DrawInstanced(PrimitiveType::TRIANGLE_STRIP, 4, 0, spriteBatch.size(), 0);

	this->spriteBatch.clear();
}