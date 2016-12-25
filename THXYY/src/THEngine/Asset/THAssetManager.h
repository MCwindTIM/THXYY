#ifndef THASSETMANAGER
#define THASSETMANAGER

#include "../Common/THCommon.h"
#include "THShader.h"
#include "THTexture.h"
#include "THRenderTexture.h"

namespace THEngine
{
	class AssetManager : public Object
	{
	private:
		IDirect3DDevice9* device;

		ArrayList<Shader*> shaderList;
		ArrayList<Texture*> textureList;
	
	private:
		AssetManager();
		
	public:
		static AssetManager* instance;

		static AssetManager* Create(Application* app);

		static AssetManager* GetInstance();

		Shader* CreateShaderFromFile(String filePath);
		void DestroyShader(Shader* shader);

		Texture* CreateTextureFromFile(String filePath);
		RenderTexture* CreateRenderTexture(int width, int height);
		void DestroyTexture(Texture* texture);

		void OnLostDevice();
		void OnResetDevice();
	};
}

#endif