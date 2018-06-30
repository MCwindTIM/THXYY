#include "THDataStack.h"

namespace THEngine
{
	DataStack::DataStack()
	{
	}

	DataStack::~DataStack()
	{
	}

	void DataStack::Reset()
	{
		this->worldTransform = std::stack<Matrix>();
		Matrix matIdentity;
		Matrix::Identity(&matIdentity);
		this->worldTransform.push(matIdentity);
	}
}