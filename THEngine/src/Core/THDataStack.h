#ifndef TH_DATA_STACK_H
#define TH_DATA_STACK_H

#include <Common\THCommon.h>
#include <Math\THMatrix.h>
#include <stack>

namespace THEngine
{
	class DataStack : public Object, public Singleton<DataStack>
	{
		friend class Singleton<DataStack>;
	private:
		std::stack<Matrix> worldTransform;

	private:
		DataStack();

		void Reset();

	public:
		virtual ~DataStack();

		friend class Game;
		friend class Layer;
		friend class GameObject;
	};
}

#endif