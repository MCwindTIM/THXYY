#ifndef TH_QUATERNION_H
#define TH_QUATERNION_H

#include <Common\THCommon.h>
#include "THVector.h"
#include <DirectXMath.h>

namespace THEngine
{
	class Quaternion
	{
	private:
		DirectX::XMFLOAT4 quaternion;

	public:
		Quaternion();

		static void Identity(Quaternion* quaternion);
		static void RotateAngleAxis(Quaternion* quaternion, const Vector3f& axis, float degree);

		Quaternion operator*(const Quaternion& rhs) const;
		Quaternion& operator *=(const Quaternion& quaternion);

		friend class Matrix;
		friend struct Vector3f;

		friend Vector3f operator*(const Vector3f& v, const Quaternion& q);
	};
}

#endif