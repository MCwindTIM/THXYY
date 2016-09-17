#ifndef MATRIX_H
#define MATRIX_H

namespace THEngine
{
	class Vector2f;
	class Vector3f;
	class Vector4f;
	class Matrix;

	class Vector2f
	{
	public:
		float x;
		float y;
	public:
		Vector2f();
		Vector2f(float x, float y);
		float Norm();
		Vector2f Normalize();
		Vector2f operator +(Vector2f a);
		Vector2f operator -(Vector2f a);
		Vector2f operator -();
		bool operator ==(Vector2f a);
		bool operator !=(Vector2f a);
	};

	class Vector3f
	{
	public:
		float x;
		float y;
		float z;
	public:
		Vector3f();
		Vector3f(float a1, float a2, float a3);
		float Norm();
		Vector3f Normalize();
		Vector3f operator +(Vector3f a);
		Vector3f operator -(Vector3f a);
		Vector3f operator -();
		Vector3f operator *(float a);
		bool operator ==(Vector3f a);
		bool operator !=(Vector3f a);

		static Vector3f Cross(Vector3f a, Vector3f b);
		static float Dot(Vector3f a, Vector3f b);
	};

	Vector3f operator*(float a, Vector3f v);

	class Vector4f
	{
	public:
		float _data[4];
	public:
		Vector4f();
		Vector4f(float a1, float a2, float a3, float a4);

		Vector4f operator *(Matrix a);

		float operator[](int index);
	};

	class Matrix
	{
	public:
		float _data[4][4];
	public:
		Matrix();
		Matrix(float **a);
		Matrix operator *(Matrix a);

		static Matrix Identity();
		static Matrix Perspective(float fov, float aspect, float zn, float zf);
		static Matrix LookAt(Vector3f position, Vector3f up, Vector3f lookAt);
		static Matrix Viewport(int x, int y, int width, int height, int MinZ, int MaxZ);
	};

	class Rect
	{
	public:
		float left, right, top, bottom;

	public:
		Rect();
		Rect(float l, float r, float t, float b) :left(l), right(r), top(t), bottom(b) {}
		inline float Width() { return right - left; }
		inline float Height() { return bottom - top; }
	};
}

#endif