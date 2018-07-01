#ifndef TH_VERTEX_FORMAT_H
#define TH_VERTEX_FORMAT_H

#include <Common\THCommon.h>

namespace THEngine
{
	enum class DataType
	{
		INT,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4
	};

	struct VertexFormatItem
	{
		size_t offset;
		DataType dataType;
		const char* semantic;
		size_t semanticIndex;
		int stream = 0;
		bool isInstanceData = false;

		VertexFormatItem() = default;
		VertexFormatItem(size_t offset, DataType dataType, const char* semantic, size_t semanticIndex, int stream = 0, bool isInstanceData = false) :
			offset(offset),
			dataType(dataType),
			semantic(semantic),
			semanticIndex(semanticIndex),
			stream(stream),
			isInstanceData(isInstanceData)
		{
		}
	};

	class VertexFormat : public Object
	{
	private:
		ID3D11InputLayout * layout = nullptr;

	public:
		virtual ~VertexFormat() { TH_SAFE_RELEASE(this->layout); }

		friend class Device;
	};
}

#endif