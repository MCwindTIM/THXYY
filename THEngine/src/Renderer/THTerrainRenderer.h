#ifndef TH_TERRAIN_RENDERER_H
#define TH_TERRAIN_RENDERER_H

#include "THRenderer.h"

namespace THEngine
{
	class Shader;
	class Terrain;

	class TerrainRenderer : public Renderer3D
	{
	private:
		Ptr<Shader> terrainShader;

	private:
		void SetupShaderParams(Ptr<Terrain> terrain);

	public:
		static Ptr<TerrainRenderer> Create();

		virtual void Render(Ptr<GameObject> obj) override;
	};
}

#endif
