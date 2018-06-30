#ifndef TH_MATH_UTIL_H
#define TH_MATH_UTIL_H

#include <limits>
#include "THVector.h"

namespace THEngine
{
	class RandomGenerator;

	class Math
	{
	private:
		static RandomGenerator* GetRandomGenerator();

	public:
		static constexpr float PI = 3.1415926f;

		static float ToAngle(float x, float y);
		static float StandardizeAngle(float angle);
		static inline float ToRad(float angle) { return angle * PI / 180.0f; }
		static inline float RadToDegree(float rad) { return rad * 180.0f / PI; }

		static int Random(int a, int b);  //返回[a,b]范围的随机整数

		static Vector2f VecRotate2D(const Vector2f& pos, float angle);
	};
}

#endif
