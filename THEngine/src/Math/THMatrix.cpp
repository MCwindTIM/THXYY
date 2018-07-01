#include "THMatrix.h"
#include "THMathUtil.h"

using namespace DirectX;

namespace THEngine
{
	Matrix::Matrix()
	{
	}

	Matrix::~Matrix()
	{
	}

	void Matrix::Identity(Matrix* matrix)
	{
		matrix->matrix = XMMatrixIdentity();
	}

	void Matrix::Translate(Matrix* matrix, float x, float y, float z)
	{
		matrix->matrix = XMMatrixTranslation(x, y, z);
	}

	void Matrix::Ortho(Matrix* matrix, float left, float right, float bottom, float top, float znear, float zfar)
	{
		matrix->matrix = XMMatrixOrthographicOffCenterLH(left, right, bottom, top, znear, zfar);
	}

	void Matrix::Perspective(Matrix* matrix, int fov, float aspect, float znear, float zfar)
	{
		matrix->matrix = XMMatrixPerspectiveFovLH(Math::ToRad(fov), aspect, znear, zfar);
	}

	void Matrix::LookAt(Matrix* matrix, const Vector3f& eye, const Vector3f& lookAt, const Vector3f& up)
	{
		matrix->matrix = XMMatrixLookAtLH(XMVectorSet(eye.x, eye.y, eye.z, 0),
			XMVectorSet(lookAt.x, lookAt.y, lookAt.z, 0),
			XMVectorSet(up.x, up.y, up.z, 0));
	}

	void Matrix::Scale(Matrix* matrix, float scaleX, float scaleY, float scaleZ)
	{
		matrix->matrix = XMMatrixScaling(scaleX, scaleY, scaleZ);
	}

	void Matrix::RotateX(Matrix* matrix, float degree)
	{
		matrix->matrix = XMMatrixRotationX(Math::ToRad(degree));
	}

	void Matrix::RotateY(Matrix* matrix, float degree)
	{
		matrix->matrix = XMMatrixRotationY(Math::ToRad(degree));
	}

	void Matrix::RotateZ(Matrix* matrix, float degree)
	{
		matrix->matrix = XMMatrixRotationZ(Math::ToRad(degree));
	}

	void Matrix::RotateQuarternion(Matrix* matrix, const Quaternion& quaternion)
	{
		matrix->matrix = XMMatrixRotationQuaternion(XMLoadFloat4(&quaternion.quaternion));
	}

	Matrix& Matrix::Inverse()
	{
		this->matrix = XMMatrixInverse(nullptr, this->matrix);
		return *this;
	}

	Matrix& Matrix::Transpose()
	{
		this->matrix = XMMatrixTranspose(this->matrix);
		return *this;
	}

	void Matrix::Set(int row, int coloum, float value)
	{
		XMFLOAT4X4 float4x4;
		XMStoreFloat4x4(&float4x4, this->matrix);
		float4x4(row, coloum) = value;
		this->matrix = XMLoadFloat4x4(&float4x4);
	}

	float Matrix::Get(int row, int coloum)
	{
		XMFLOAT4X4 float4x4;
		XMStoreFloat4x4(&float4x4, this->matrix);
		return float4x4(row, coloum);
	}

	void Matrix::Dump(float* output)
	{
		XMStoreFloat4x4((XMFLOAT4X4*)output, this->matrix);
	}

	Matrix& Matrix::operator*=(const Matrix& matrix)
	{
		this->matrix *= matrix.matrix;
		return *this;
	}

	Matrix& Matrix::operator*=(const Quaternion& quaternion)
	{
		XMMATRIX mat = XMMatrixRotationQuaternion(XMLoadFloat4(&quaternion.quaternion));
		this->matrix *= mat;
		return *this;
	}

	Matrix Matrix::operator*(const Matrix& matrix) const
	{
		Matrix result;
		result.matrix = this->matrix * matrix.matrix;
		return result;
	}

	Vector4f operator*(const Vector4f& vector, const Matrix& matrix)
	{
		XMVECTOR v = XMVector4Transform(XMVectorSet(vector.x, vector.y, vector.z, vector.w), matrix.matrix);
		XMFLOAT4 float4;
		XMStoreFloat4(&float4, v);
		return Vector4f(float4.x, float4.y, float4.z, float4.w);
	}

	Vector4f& operator*=(Vector4f& vector, const Matrix& matrix)
	{
		XMVECTOR v = XMVector4Transform(XMVectorSet(vector.x, vector.y, vector.z, vector.w), matrix.matrix);
		XMFLOAT4 float4;
		XMStoreFloat4(&float4, v);
		vector.x = float4.x;
		vector.y = float4.y;
		vector.z = float4.z;
		vector.w = float4.w;
		return vector;
	}
}