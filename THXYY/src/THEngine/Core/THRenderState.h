#ifndef THRENDERSTATE_H
#define THRENDERSTATE_H

#include "../Common/THCommon.h"
#include "../Math/Matrix.h"

namespace THEngine
{
	struct Fog
	{
		Vector4f fogColor;
		float fogStart;
		float fogEnd;
	};

	class RenderState : public Object
	{
	public:
		bool fogEnable = false;
		Fog fog;

		D3DXMATRIX world, projection, view;

	public:
		RenderState();
		virtual ~RenderState();
		
	};
}

#endif