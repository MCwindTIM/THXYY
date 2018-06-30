#ifndef TH_RENDER_STATE_H
#define TH_RENDER_STATE_H

#include <Common\THCommon.h>
#include <Math\THMath.h>
#include "3D\THLight.h"
#include <Graphic\THForwardRenderingState.h>

namespace THEngine
{
	class RenderTexture;
	class Texture;
	class DepthBuffer;
	class Camera;
	class Environment;
	struct Fog;

	struct Viewport
	{
		int x;
		int y;
		int width;
		int height;
		int minZ;
		int maxZ;
	};

	enum class BlendFactor
	{
		ZERO,
		ONE,
		SRC_COLOR,
		INV_SRC_COLOR,
		SRC_ALPHA,
		INV_SRC_ALPHA,
		DEST_ALPHA,
		INV_DEST_ALPHA,
		DEST_COLOR,
		INV_DEST_COLOR,
		BLEND_FACTOR
	};

	enum class BlendOp
	{
		ADD,
		SUBTRACT,
		REV_SUBTRACT,
		MIN,
		MAX
	};

	struct BlendMode
	{
		BlendFactor srcFactor = BlendFactor::SRC_ALPHA;
		BlendFactor destFactor = BlendFactor::INV_SRC_ALPHA;
		BlendFactor srcAlphaFactor = BlendFactor::ONE;
		BlendFactor destAlphaFactor = BlendFactor::ZERO;
		BlendOp blendOp = BlendOp::ADD;
		BlendOp alphaOp = BlendOp::ADD;
		Vector4f blendFactor;

		bool operator ==(const BlendMode& rhs) const
		{
			return std::memcmp(this, &rhs, sizeof(BlendMode)) == 0;
		}

		bool operator !=(const BlendMode& rhs) const { return !(*this == rhs); }
	};

	enum class CompareOp
	{
		EQUAL,
		NOT_EQUAL,
		LESS,
		LESS_EQUAL,
		GREATER,
		GREATER_EQUAL,
		NEVER,
		ALWAYS
	};

	enum class StencilOp
	{
		KEEP,
		ZERO,
		INC_SAT,
		DEC_SAT,
		REPLACE,
		INVERT,
		INC,
		DEC
	};

	enum class CullMode
	{
		NONE,
		FRONT,
		BACK
	};

	enum class FillMode
	{
		SOLID,
		WIREFRAME
	};

	enum class PrimitiveType
	{
		TRIANGLE_LIST,
		TRIANGLE_STRIP
	};

	enum class RenderingPath
	{
		FORWARD,
		DEFERRED
	};

	class RenderState : public Object
	{
	private:
		Environment * environment;

		Matrix world;
		Matrix projection;
		Matrix view;

		Viewport viewport;

		Ptr<Shader> shader;

		// buffers
		Ptr<RenderTexture> renderTarget;
		Ptr<DepthBuffer> depthBuffer;
		Ptr<RenderTexture> colorBuffer;
		bool isRenderTargetDirty = true;

		Ptr<Camera> camera;
		Ptr<Light> currentLight;

		PrimitiveType primitiveType = PrimitiveType::TRIANGLE_LIST;

		// depth stencil buffer setting
		bool isDepthTestEnabled = true;
		bool isDepthWriteEnabled = true;
		CompareOp depthOp = CompareOp::LESS_EQUAL;
		bool isStencilTestEnabled = false;
		unsigned int stencilRef = 0;
		unsigned char stencilReadMask = 0xff;
		unsigned char stencilWriteMask = 0xff;
		CompareOp stencilOp = CompareOp::ALWAYS;
		StencilOp stencilFail = StencilOp::KEEP;
		StencilOp stencilDepthFail = StencilOp::KEEP;
		StencilOp stencilPass = StencilOp::KEEP;
		bool isDepthStencilDirty = true;

		// rasterizer setting
		CullMode cullMode = CullMode::NONE;
		FillMode fillMode = FillMode::SOLID;
		bool isRasterizerDirty = true;

		// blend setting
		bool isAlphaBlendEnabled = true;
		BlendMode blendMode;
		bool isBlendDirty = true;

		RenderingPath renderingPath = RenderingPath::FORWARD;
		ForwardRenderingState forwardRenderingState;

	public:
		RenderState();
		virtual ~RenderState();

		bool IsFogEnabled() const;
		bool IsLightingEnabled() const;

		const Fog& GetFog() const;

		inline const Matrix& GetWorldMatrix() { return this->world; }
		inline const Matrix& GetProjectionMatrix() { return this->projection; }
		inline const Matrix& GetViewMatrix() { return this->view; }
		inline const Viewport& GetViewport() const { return this->viewport; }

		const Vector4f& GetAmbientLight() const;
		LinkedList<Ptr<Light>>* GetLights() const;

		inline Ptr<Shader> GetCurrentShader() const { return this->shader; }

		inline Ptr<RenderTexture> GetRenderTarget() const { return this->renderTarget; }

		inline Ptr<DepthBuffer> GetDepthBuffer() const { return this->depthBuffer; }
		inline Ptr<RenderTexture> GetColorBuffer() const { return this->colorBuffer; }

		inline Ptr<Camera> GetCamera() const { return this->camera; }

		inline const BlendMode& GetBlendMode() const { return this->blendMode; }

		inline bool IsDepthTestEnabled() const { return this->isDepthTestEnabled; }

		inline RenderingPath GetRenderingPath() const { return this->renderingPath; }
		inline const ForwardRenderingState& GetForwardRenderingState() const { return this->forwardRenderingState; }

		void Clear();

		friend class Device;
		friend class Layer;
		friend class Shader;
		friend class Camera;
		friend class RenderPipeline;
	};
}

#endif