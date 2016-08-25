#ifndef THRENDERER_H
#define THRENDERER_H

#include "../Common/THCommon.h"
#include "../Core/THGameObject.h"
#include "THRenderQueue.h"
#include "../Core/THGame.h"
#include "../Core/THSprite.h"
#include "../Asset/THShader.h"


namespace THEngine
{
	class GameObject;
	class Sprite;

	class Renderer : public Object
	{
	protected:
		IDirect3DDevice9* device;

	public:
		virtual void Render(GameObject* obj) = 0;
	};

	class SpriteRenderer : public Renderer
	{
	private:
		Shader* spriteShader;
		IDirect3DVertexBuffer9* vb;

		struct SpriteVertex
		{
			float x, y, z;
			float u, v;
			SpriteVertex() {}
			SpriteVertex(float x, float y, float z, float u, float v) :x(x), y(y), z(z), u(u), v(v) {}
		};

	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		static SpriteRenderer* Create(Application* app);

		virtual void Render(GameObject* obj) override;
		void Render(Sprite* sprite);

		friend class SpriteRenderQueue;
	};
}

#endif