#ifndef THMESH_H
#define THMESH_H

#include <Core\THGameObject.h>

namespace THEngine
{
	class Mesh;

	class MeshObject : public GameObject
	{
	private:
		Ptr<Mesh> mesh;

	public:
		MeshObject();
		MeshObject(const MeshObject& mesh);
		virtual ~MeshObject();

		virtual void Update() override;
		virtual void Draw() override;
		virtual void SendToRenderQueue() override;
		virtual Ptr<Object> Clone() const override;
		virtual void DrawGeometry() override;
		virtual void DrawShadowMap() override;

		inline void SetMesh(Ptr<Mesh> mesh) { this->mesh = mesh; }

		friend class MeshRenderer;
		friend class AssimpLoader;
	};
}

#endif