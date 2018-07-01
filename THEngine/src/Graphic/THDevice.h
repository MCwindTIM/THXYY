#ifndef TH_DEVICE_H
#define TH_DEVICE_H

#include <Common\THCommon.h>
#include <Core\THConfig.h>
#include <Core\THRenderState.h>
#include <Asset\THRenderTexture.h>
#include "THBuffers.h"
#include "THVertexFormat.h"
#include "THGraphicDefines.h"

namespace THEngine
{
	class Device : public Object, public Singleton<Device>
	{
		friend class Singleton<Device>;

	private:
		const Config* config = nullptr;

		//DirectX device
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		DXGI_SWAP_CHAIN_DESC chainDesc;

		Ptr<RenderState> renderState = Ptr<RenderState>::New();
	private:
		Device();

		void GetDeviceInfo(D3D_DRIVER_TYPE* deviceType, int* vertexProcessingType);
		void GetMultiSampleType(UINT* sampleCount, UINT* qualityLevel);
		bool InitDevice(HWND hWnd);
		bool CreateDevice();
		void InitRenderState();
		bool CreateDeviceContext();
		void SetupRenderState();

	public:
		virtual ~Device();

		bool Init(const Config* config);

		void SetOrtho(float left, float bottom, float width, float height, float znear, float zfar);
		void SetViewport(int left, int top, int width, int height);

		bool IsDeviceLost();
		bool NeedResetDevice();
		void OnLostDevice();
		void OnResetDevice();

		inline ID3D11Device* GetD3DDevice() { return device; }
		inline ID3D11DeviceContext* GetD3D11Context() { return context; }

		inline Ptr<RenderState> GetRenderState() { return renderState; }

		inline void ClearBuffer()
		{
			ClearColorBuffer(Vector4f(0, 0, 0, 1));
			ClearDepthBuffer();
		}

		inline void ClearRenderTarget(const Vector4f& color)
		{
			this->context->ClearRenderTargetView(this->renderState->renderTarget->renderTargetView, color._data);
		}

		inline void ClearColorBuffer(const Vector4f& color)
		{
			this->context->ClearRenderTargetView(GetColorBuffer()->renderTargetView, color._data);
		}

		inline void ClearDepthBuffer()
		{
			this->context->ClearDepthStencilView(GetDepthBuffer()->view, D3D11_CLEAR_DEPTH, 1, 0);
		}

		void SetRenderTarget(Ptr<RenderTexture> texture);

		void SetDepthBuffer(Ptr<DepthBuffer> depthBuffer);
		inline Ptr<DepthBuffer> GetDepthBuffer() const { return this->renderState->GetDepthBuffer(); }

		inline Ptr<RenderTexture> GetColorBuffer() const { return this->renderState->GetColorBuffer(); }

		Ptr<DepthBuffer> CreateDepthBuffer(int width, int height, bool forTexture = true);

		void SetBlendMode(const BlendMode& blendMode);

		inline bool SwapBuffers()
		{
			if (config->useVSync)
				return (!FAILED(this->swapChain->Present(1, 0)));
			return (!FAILED(this->swapChain->Present(0, 0)));
		}

		inline void BeginRender()
		{
			;
		}

		void EndRender();

		inline void SetWorldMatrix(const Matrix& world)
		{
			renderState->world = world;
		}

		inline void SetProjectionMatrix(const Matrix& projection)
		{
			renderState->projection = projection;
		}

		inline void SetViewMatrix(const Matrix& view)
		{
			renderState->view = view;
		}

		void EnableDepthTest(bool value);

		Ptr<StaticVertexBuffer> CreateStaticVertexBuffer(size_t maxBytes, const void* data);
		Ptr<DynamicVertexBuffer> CreateDynamicVertexBuffer(size_t maxBytes);

		Ptr<StaticIndexBuffer> CreateStaticIndexBuffer(size_t maxBytes, const void* data);
		Ptr<DynamicIndexBuffer> CreateDynamicIndexBuffer(size_t maxBytes);

		void SetVertexBuffer(Ptr<VertexBuffer> vb, size_t stride, int stream = 0);
		void SetIndexBuffer(Ptr<IndexBuffer> vb);

		Ptr<VertexFormat> CreateVertexFormat(const std::vector<VertexFormatItem>& items,
			Ptr<Shader> shader, const char* tech, int pass);
		void SetVertexFormat(Ptr<VertexFormat> format);

		void Draw(PrimitiveType primitiveType, size_t verticesCount, size_t startVertex);
		void DrawIndexed(PrimitiveType primitiveType, size_t indicesCount, size_t startIndex, size_t startVertex);
		void DrawInstanced(PrimitiveType primitiveType, size_t verticesCount, size_t startVertex, size_t instanceCount, size_t startInstance);

		friend class AssetManager;
		friend class Shader;
	};
}

#endif
