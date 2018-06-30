#ifndef THSPRITERENDERER_H
#define THSPRITERENDERER_H

#include "THRenderer.h"

namespace THEngine
{
	class Application;
	class Sprite;
	class DynamicVertexBuffer;
	class VertexFormat;

	class SpriteRenderer : public Renderer
	{
	private:
		static const int MAX_SPRITE = 10000;

		struct SpriteVertex
		{
			float x, y, z;
			float r, g, b, a;
			float u, v;
			SpriteVertex() {}
			SpriteVertex(float x, float y, float z, float r, float g, float b, float a, float u, float v)
				:x(x), y(y), z(z), r(r), g(g), b(b), a(a), u(u), v(v)
			{
			}
		};

		/*struct SpriteBatch
		{
			SpriteVertex vertices[MAX_SPRITE][6];
			int spriteCount = 0;
			Texture* texture;
		};*/

		Ptr<DynamicVertexBuffer> vb;
		Ptr<VertexFormat> format;
		//SpriteBatch spriteBatch;

	private:
		/*void PushBatch(Sprite* sprite);
		void CalcWorldTransform(Sprite* sprite, Matrix* transform);
		void SetupVertices(Sprite* sprite, const Matrix& transform);
		void FlushBatch();*/

	private:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void SetupRenderState(Ptr<Sprite> obj);

	public:
		static Ptr<SpriteRenderer> Create();

		virtual void Render(Ptr<GameObject> obj) override;

		friend class SpriteRenderQueue;
	};
}

#endif