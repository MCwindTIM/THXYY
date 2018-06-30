#ifndef THPARTICLE3DRENDERER_H
#define THPARTICLE3DRENDERER_H

#include "THRenderer.h"

namespace THEngine
{
	class DynamicVertexBuffer;
	class VertexFormat;

	class Particle3DRenderer : public Renderer
	{
	protected:
		Ptr<DynamicVertexBuffer> vb;
		Ptr<VertexFormat> format;

		struct ParticleVertex
		{
			float x, y, z;
			float r, g, b, a;
			float u, v;
			ParticleVertex() {}
			ParticleVertex(float x, float y, float z, float r, float g, float b, float a, float u, float v)
				:x(x), y(y), z(z), r(r), g(g), b(b), a(a), u(u), v(v)
			{
			}
		};

	private:
		Particle3DRenderer();

	public:
		virtual ~Particle3DRenderer();

		virtual void Render(Ptr<GameObject> obj) override;

		static Ptr<Particle3DRenderer> Create();
	};
}

#endif