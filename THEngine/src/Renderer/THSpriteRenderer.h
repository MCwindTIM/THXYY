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
			float u, v;
			SpriteVertex() {}
			SpriteVertex(float x, float y, float z, float u, float v)
				:x(x), y(y), z(z), u(u), v(v)
			{
			}
		};

		struct SpriteInstance
		{
			Vector4f color;
			Vector4f world1;
			Vector4f world2;
			Vector4f world3;
			Vector4f world4;
		};

		std::vector<Ptr<Sprite>> spriteBatch;

		Ptr<DynamicVertexBuffer> vb;
		Ptr<DynamicVertexBuffer> instanceBuffer;
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

		void Flush();

		friend class SpriteRenderQueue;
	};
}

#endif