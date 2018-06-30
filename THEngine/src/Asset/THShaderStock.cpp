#include "THShaderStock.h"
#include "THAssetManager.h"
#include <Core\THGame.h>

namespace THEngine
{
	ShaderStock::~ShaderStock()
	{
	}

	bool ShaderStock::Init()
	{
		auto assetManager = AssetManager::GetInstance();
		auto exceptionManager = ExceptionManager::GetInstance();

		shadowShader = assetManager->CreateShaderFromFile("fx/shadow.fx");
		if (shadowShader != nullptr)
		{
			shadowShader->SetTechnique("Shadow");
		}
		else
		{
			exceptionManager->PushException(Ptr<Exception>::New("����shadow shaderʧ�ܡ�"));
			return false;
		}

		skyBoxShader = Game::GetInstance()->GetAssetManager()->CreateShaderFromFile("fx/skybox.fx");
		if (skyBoxShader != nullptr)
		{
			skyBoxShader->SetTechnique("SkyBox");
		}
		else
		{
			exceptionManager->PushException(Ptr<Exception>::New("����skybox shaderʧ�ܡ�"));
			return false;
		}

		meshShader = assetManager->CreateShaderFromFile("fx/mesh.fx");
		if (meshShader != nullptr)
		{
			meshShader->SetTechnique("Mesh");
		}
		else
		{
			exceptionManager->PushException(Ptr<Exception>::New("����mesh shaderʧ�ܡ�"));
			return false;
		}

		spriteShader = Game::GetInstance()->GetAssetManager()->CreateShaderFromFile("fx/sprite.fx");
		if (spriteShader != nullptr)
		{
			spriteShader->SetTechnique("Sprite");
		}
		else
		{
			exceptionManager->PushException(Ptr<Exception>::New("����sprite shaderʧ�ܡ�"));
			return false;
		}

		terrainShader = Game::GetInstance()->GetAssetManager()->CreateShaderFromFile("fx/terrain.fx");
		if (terrainShader != nullptr)
		{
			terrainShader->SetTechnique("Terrain");
		}
		else
		{
			exceptionManager->PushException(Ptr<Exception>::New("����terrain shaderʧ�ܡ�"));
			return false;
		}

		terrainShadowShader = Game::GetInstance()->GetAssetManager()->CreateShaderFromFile("fx/terrainShadow.fx");
		if (terrainShadowShader != nullptr)
		{
			terrainShadowShader->SetTechnique("Shadow");
		}
		else
		{
			exceptionManager->PushException(Ptr<Exception>::New("����terrain shadow shaderʧ�ܡ�"));
			return false;
		}

		return true;
	}
}