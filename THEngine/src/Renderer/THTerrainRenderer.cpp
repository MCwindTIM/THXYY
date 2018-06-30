#include "THTerrainRenderer.h"
#include <Asset\THAssetManager.h>
#include <Asset\THShader.h>
#include <Asset\THFloatTexture.h>
#include <Asset\THShaderStock.h>
#include <Core\3D\THTerrain.h>
#include <Graphic\THDevice.h>

namespace THEngine
{
	Ptr<TerrainRenderer> TerrainRenderer::Create()
	{
		auto assetManager = AssetManager::GetInstance();
		auto exceptionManager = ExceptionManager::GetInstance();

		Ptr<TerrainRenderer> renderer = Ptr<TerrainRenderer>::New();
		renderer->shader = ShaderStock::GetInstance()->GetTerrainShader();
		return renderer;
	}

	void TerrainRenderer::Render(Ptr<GameObject> obj)
	{
		Ptr<Terrain> terrain = reinterpret_cast<Terrain*>(obj.Get());

		SetupShaderParams(terrain);

		this->shader->Use();
		this->shader->UsePass(0);
		terrain->DrawGeometry();
	}

	void TerrainRenderer::SetupShaderParams(Ptr<Terrain> terrain)
	{
		Renderer3D::SetupShaderParams(terrain.Get());

		this->shader->SetValue("g_material", &terrain->material, sizeof(Material) - sizeof(Ptr<Texture>));
		this->shader->SetFloat("g_zscale", terrain->zScale);
		this->shader->SetTexture("g_heightMap", terrain->heightMap.Get());
		this->shader->SetFloat2("g_cellSize", terrain->cellSize);
		this->shader->SetFloat2("g_dTexCoord", terrain->dTexCoord);
		if (terrain->material.texture != nullptr)
		{
			this->shader->SetBoolean("g_hasTexture", true);
			this->shader->SetTexture("g_texture", terrain->material.texture);
		}
		else
		{
			this->shader->SetBoolean("g_hasTexture", false);
		}
	}
}