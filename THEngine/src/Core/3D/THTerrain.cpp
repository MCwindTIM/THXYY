#include "THTerrain.h"
#include <Graphic\THDevice.h>
#include <Asset\THShaderStock.h>
#include <Asset\THShader.h>
#include <Core\THGame.h>
#include <Renderer\THRenderPipeline.h>
#include <Renderer\THTerrainRenderer.h>

namespace THEngine
{
	struct TerrainVertex
	{
		float x, y, z;
		float u, v;
		TerrainVertex() {}
		TerrainVertex(float x, float y, float z, float u, float v) :
			x(x), y(y), z(z), u(u), v(v)
		{
		}
	};

	Terrain::Terrain()
	{
		auto device = Device::GetInstance();
		auto terrainShader = ShaderStock::GetInstance()->GetTerrainShader();

		std::vector<VertexFormatItem> vfitems;
		vfitems.push_back(VertexFormatItem(0, DataType::FLOAT3, "POSITION", 0, 0));
		vfitems.push_back(VertexFormatItem(sizeof(float) * 6, DataType::FLOAT2, "TEXCOORD", 0, 0));
		this->vertexFormat = device->CreateVertexFormat(vfitems, terrainShader, "Terrain", 0);
	}

	void Terrain::GenerateBuffers()
	{
		auto device = Device::GetInstance();
		std::vector<TerrainVertex> vertices(this->xResolution * this->yResolution);
		float left = -this->xWidth / 2;
		float bottom = -this->yWidth / 2;
		float xWidthPerCell = this->xWidth / (this->xResolution - 1);
		float yWidthPerCell = this->yWidth / (this->yResolution - 1);
		float du = 1.0f / (this->xResolution - 1);
		float dv = 1.0f / (this->yResolution - 1);
		for (size_t i = 0; i < this->xResolution; i++)
		{
			for (size_t j = 0; j < this->yResolution; j++)
			{
				size_t index = i * xResolution + j;
				vertices[index].x = left + xWidthPerCell * i;
				vertices[index].y = 0;
				vertices[index].z = bottom + yWidthPerCell * j;
				vertices[index].u = du * i;
				vertices[index].v = dv * j;
			}
		}
		this->vb = device->CreateStaticVertexBuffer(sizeof(TerrainVertex) * vertices.size(), &vertices[0]);

		std::vector<uint32_t> indices;
		for (size_t i = 0; i < this->xResolution - 1; i++)
		{
			for (size_t j = 0; j < this->yResolution - 1; j++)
			{
				size_t a = i * this->xResolution + j;
				size_t b = a + 1;
				size_t c = (i + 1)*this->xResolution + j;
				size_t d = c + 1;
				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(b);
				indices.push_back(d);
				indices.push_back(c);
			}
		}
		this->ib = device->CreateStaticIndexBuffer(sizeof(uint32_t) * indices.size(), &indices[0]);

		this->cellSize.x = xWidthPerCell;
		this->cellSize.y = yWidthPerCell;
		this->dTexCoord.x = du;
		this->dTexCoord.y = dv;
	}

	void Terrain::DrawGeometry()
	{
		auto device = Device::GetInstance();
		if (this->changed)
		{
			GenerateBuffers();

			this->changed = false;
		}

		device->SetVertexFormat(this->vertexFormat);
		device->SetVertexBuffer(this->vb.Get(), sizeof(TerrainVertex), 0);
		device->SetIndexBuffer(this->ib.Get());
		device->GetRenderState()->GetCurrentShader()->CommitChanges();
		device->DrawIndexed(PrimitiveType::TRIANGLE_LIST,
			(this->xResolution - 1) * (this->yResolution - 1) * 6,
			0, 0);
	}

	void Terrain::Draw()
	{
		Game::GetInstance()->GetRenderPipeline()->GetTerrainRenderer()->Render(this);
	}

	void Terrain::SendToRenderQueue()
	{
		Game::GetInstance()->GetRenderPipeline()->SendToRenderQueue(RenderPipeline::NORMAL, this);
	}

	void Terrain::DrawShadowMap()
	{
		auto shader = ShaderStock::GetInstance()->GetTerrainShadowShader();
		auto renderState = Device::GetInstance()->GetRenderState();
		auto shaderPrev = renderState->GetCurrentShader();

		Matrix world;
		GetWorldMatrix(&world);
		Matrix mv = world * renderState->GetViewMatrix();

		shader->Use();
		shader->UsePass(0);
		shader->SetMatrix("g_mvMatrix", mv);
		shader->SetMatrix("g_projection", renderState->GetProjectionMatrix());
		shader->SetFloat("g_zscale", this->zScale);
		shader->SetTexture("g_heightMap", this->heightMap.Get());
		shader->CommitChanges();

		DrawGeometry();

		shaderPrev->Use();
	}
}