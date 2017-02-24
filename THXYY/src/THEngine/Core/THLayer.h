#ifndef THLAYER_H
#define THLAYER_H

#include "../Common/THCommon.h"
#include "THGameObject.h"
#include "THCamera.h"
#include <Asset\THCubeMap.h>
#include "../Platform/THApplication.h"
#include "3D\THLight.h"

namespace THEngine
{
	class Layer : public EngineObject
	{
	protected:
		int width, height;
		int left, top;
		int order;          
		GameObject rootNode;
		
		LinkedList<Camera*> cameraList;

		bool fogEnable = false;
		Fog fog;

		CubeMap* skyBox = nullptr;

		LinkedList<Light*> lights;

		bool lightingEnable = false;

	protected:
		void SetupRenderState();

	public:
		Layer();
		Layer(int left, int top, int wdith, int height);
		virtual ~Layer();
		virtual void Update() override;
		virtual void Draw() override;

		virtual void OnDestroy();

		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }
		inline int GetLeft() const { return left; }
		inline int GetTop() const { return top; }

		void AddChild(GameObject* obj);

		void Clear();

		inline void AddLight(Light* light) { lights.Add(light); }

		inline void RemoveLight(Light* light) { lights.Remove(light); }

		inline LinkedList<Camera*>* GetCameraList() { return &cameraList; }

		Camera* GetCameraByName(const String& name);
		Camera* GetCameraByIndex(int index);
		Camera* GetFirstCamera();

		inline void AddCamera(Camera* camera) { cameraList.Add(camera); }

		void SetCameraByName(Camera* camera, const String& name);
		void SetCameraByIndex(Camera* camera, int index);
		void SetFirstCamera(Camera* camera);

		inline void SetOrder(int order) { this->order = order; }

		inline void EnableFog(bool fogEnable) { this->fogEnable = fogEnable; }

		inline void EnableLighting(bool lightingEnable) { this->lightingEnable = lightingEnable; }
		
		inline void SetFog(Fog fog) { this->fog = fog; }

		inline void SetSkyBox(CubeMap* skyBox) { TH_SET(this->skyBox, skyBox); }

		void DestroyObjectImmediately(GameObject* obj);

		friend class Scene;
	};
}

#endif