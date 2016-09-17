#ifndef THLAYER_H
#define THLAYER_H

#include "../Common/THCommon.h"
#include "THGameObject.h"
#include "THCamera.h"

namespace THEngine
{
	class Layer : public EngineObject
	{
	protected:
		int width, height;
		int left, top;
		int order;          
		GameObject rootNode;
		Camera* camera = nullptr;

		bool activated = false;

	public:
		Layer();
		Layer(int left, int top, int wdith, int height);
		virtual ~Layer();
		virtual void Update() override;
		virtual void Draw() override;

		virtual void OnActivate();
		virtual void OnDestroy();

		void AddChild(GameObject* obj);

		inline Camera* GetCamera() { return camera; }

		void SetCamera(Camera* camera);

		inline void SetOrder(int order) { this->order = order; }

		void DestroyObjectImmediately(GameObject* obj);

		friend class Scene;
	};
}

#endif