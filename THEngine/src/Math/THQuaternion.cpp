#include "THQuaternion.h"
#include "THMathUtil.h"

using namespace DirectX;

namespace THEngine
{
	Quaternion::Quaternion()
	{
		XMStoreFloat4(&this->quaternion, XMQuaternionIdentity());
	}

	void Quaternion::Identity(Quaternion* quaternion)
	{
		XMStoreFloat4(&quaternion->quaternion, XMQuaternionIdentity());
	}

	void Quaternion::RotateAngleAxis(Quaternion* quaternion, const Vector3f& axis, float degree)
	{
		XMStoreFloat4(&quaternion->quaternion, XMQuaternionRotationAxis(XMVectorSet(axis.x, axis.y, axis.z, 0), Math::ToRad(degree)));
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		Quaternion result;
		XMVECTOR v1 = XMLoadFloat4(&this->quaternion);
		XMVECTOR v2 = XMLoadFloat4(&rhs.quaternion);
		XMStoreFloat4(&result.quaternion, XMQuaternionMultiply(v1, v2));
		return result;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& quaternion)
	{
		XMVECTOR v1 = XMLoadFloat4(&this->quaternion);
		XMVECTOR v2 = XMLoadFloat4(&quaternion.quaternion);
		XMStoreFloat4(&this->quaternion, XMQuaternionMultiply(v1, v2));
		return *this;
	}
}