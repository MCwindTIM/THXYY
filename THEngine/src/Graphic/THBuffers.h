#ifndef TH_BUFFERS_H
#define TH_BUFFERS_H

#include <Common\THCommon.h>
#include <vector>

namespace THEngine
{
	class DepthBuffer : public Object
	{
	private:
		ID3D11Texture2D * buffer = nullptr;
		ID3D11DepthStencilView* view = nullptr;

	public:
		virtual ~DepthBuffer();

		//bool SaveToFile(const String& path);

		friend class Device;
	};

	class VertexBuffer : public Object
	{
	protected:
		ID3D11Buffer * buffer = nullptr;

	public:
		virtual ~VertexBuffer();

		friend class Device;
	};

	class StaticVertexBuffer : public VertexBuffer
	{
	};

	class DynamicVertexBuffer : public VertexBuffer
	{
	public:
		void* Lock();
		void UnLock();
	};

	class IndexBuffer : public Object
	{
	protected:
		ID3D11Buffer * buffer = nullptr;

	public:
		virtual ~IndexBuffer();

		friend class Device;
	};

	class StaticIndexBuffer : public IndexBuffer
	{
	};

	class DynamicIndexBuffer : public IndexBuffer
	{
	public:
		void* Lock();
		void UnLock();
	};
}

#endif
