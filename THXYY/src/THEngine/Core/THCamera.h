#ifndef THCAMERA_H
#define THCAMERA_H

#include "../Common/THCommon.h"
#include "../Math/MathUtil.h"

namespace THEngine
{
	class Camera : public Object
	{
	protected:
		
	private:

	};

	class Camera2D : public Camera
	{
	protected:
		Rect viewRect;

	public:
		inline void SetViewRect(Rect rect) { this->viewRect = rect; }
		inline Rect GetViewRect() { return viewRect; }
	};
}

#endif