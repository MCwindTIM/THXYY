#include "THDevice.h"
#include "THBuffers.h"
#include <Platform\THApplication.h>
#include <Core\THConfig.h>
#include <Common\THMap.h>
#include <Asset\THAssetManager.h>
#include <Asset\THShader.h>
#include <Asset\THTexture.h>
#include <Asset\THRenderTexture.h>

namespace THEngine
{
	static Map<BlendOp, D3D11_BLEND_OP> __device_blend_op_map;
	static Map<BlendFactor, D3D11_BLEND> __deivce_blend_factor_map;
	static Map<CullMode, D3D11_CULL_MODE> __device_cull_mode_map;
	static Map<FillMode, D3D11_FILL_MODE> __device_fill_mode_map;
	static Map<CompareOp, D3D11_COMPARISON_FUNC> __device_compare_op_map;
	static Map<StencilOp, D3D11_STENCIL_OP> __device_stencil_op_map;

	static Map<Semantic, char*> __device_semantic_map;
	static Map<DataType, DXGI_FORMAT> __device_data_format_map;

	static Map<PrimitiveType, D3D11_PRIMITIVE_TOPOLOGY> __device_primitive_type_map;

	Device::Device()
	{
		__device_blend_op_map.Put(BlendOp::ADD, D3D11_BLEND_OP_ADD);
		__device_blend_op_map.Put(BlendOp::SUBTRACT, D3D11_BLEND_OP_SUBTRACT);
		__device_blend_op_map.Put(BlendOp::REV_SUBTRACT, D3D11_BLEND_OP_REV_SUBTRACT);
		__device_blend_op_map.Put(BlendOp::MIN, D3D11_BLEND_OP_MAX);
		__device_blend_op_map.Put(BlendOp::MAX, D3D11_BLEND_OP_MAX);

		__deivce_blend_factor_map.Put(BlendFactor::ONE, D3D11_BLEND_ONE);
		__deivce_blend_factor_map.Put(BlendFactor::ZERO, D3D11_BLEND_ZERO);
		__deivce_blend_factor_map.Put(BlendFactor::SRC_ALPHA, D3D11_BLEND_SRC_ALPHA);
		__deivce_blend_factor_map.Put(BlendFactor::INV_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA);
		__deivce_blend_factor_map.Put(BlendFactor::DEST_ALPHA, D3D11_BLEND_DEST_ALPHA);
		__deivce_blend_factor_map.Put(BlendFactor::INV_DEST_ALPHA, D3D11_BLEND_INV_DEST_ALPHA);
		__deivce_blend_factor_map.Put(BlendFactor::SRC_COLOR, D3D11_BLEND_SRC_COLOR);
		__deivce_blend_factor_map.Put(BlendFactor::INV_SRC_COLOR, D3D11_BLEND_INV_SRC_COLOR);
		__deivce_blend_factor_map.Put(BlendFactor::DEST_COLOR, D3D11_BLEND_DEST_COLOR);
		__deivce_blend_factor_map.Put(BlendFactor::INV_DEST_COLOR, D3D11_BLEND_INV_DEST_COLOR);
		__deivce_blend_factor_map.Put(BlendFactor::BLEND_FACTOR, D3D11_BLEND_BLEND_FACTOR);

		__device_cull_mode_map.Put(CullMode::FRONT, D3D11_CULL_FRONT);
		__device_cull_mode_map.Put(CullMode::BACK, D3D11_CULL_BACK);
		__device_cull_mode_map.Put(CullMode::NONE, D3D11_CULL_NONE);

		__device_fill_mode_map.Put(FillMode::SOLID, D3D11_FILL_SOLID);
		__device_fill_mode_map.Put(FillMode::WIREFRAME, D3D11_FILL_WIREFRAME);

		__device_compare_op_map.Put(CompareOp::EQUAL, D3D11_COMPARISON_EQUAL);
		__device_compare_op_map.Put(CompareOp::NOT_EQUAL, D3D11_COMPARISON_NOT_EQUAL);
		__device_compare_op_map.Put(CompareOp::GREATER, D3D11_COMPARISON_GREATER);
		__device_compare_op_map.Put(CompareOp::GREATER_EQUAL, D3D11_COMPARISON_GREATER_EQUAL);
		__device_compare_op_map.Put(CompareOp::LESS, D3D11_COMPARISON_LESS);
		__device_compare_op_map.Put(CompareOp::LESS_EQUAL, D3D11_COMPARISON_LESS_EQUAL);
		__device_compare_op_map.Put(CompareOp::NEVER, D3D11_COMPARISON_NEVER);
		__device_compare_op_map.Put(CompareOp::ALWAYS, D3D11_COMPARISON_ALWAYS);

		__device_stencil_op_map.Put(StencilOp::KEEP, D3D11_STENCIL_OP_KEEP);
		__device_stencil_op_map.Put(StencilOp::ZERO, D3D11_STENCIL_OP_ZERO);
		__device_stencil_op_map.Put(StencilOp::REPLACE, D3D11_STENCIL_OP_REPLACE);
		__device_stencil_op_map.Put(StencilOp::INVERT, D3D11_STENCIL_OP_INVERT);
		__device_stencil_op_map.Put(StencilOp::INC, D3D11_STENCIL_OP_INCR);
		__device_stencil_op_map.Put(StencilOp::DEC, D3D11_STENCIL_OP_DECR);
		__device_stencil_op_map.Put(StencilOp::INC_SAT, D3D11_STENCIL_OP_INCR_SAT);
		__device_stencil_op_map.Put(StencilOp::DEC_SAT, D3D11_STENCIL_OP_DECR_SAT);

		__device_semantic_map.Put(Semantic::POSITION, "POSITION");
		__device_semantic_map.Put(Semantic::NORMAL, "NORMAL");
		__device_semantic_map.Put(Semantic::COLOR, "COLOR");
		__device_semantic_map.Put(Semantic::TEXCOORD, "TEXCOORD");

		__device_data_format_map.Put(DataType::INT, DXGI_FORMAT_R32_SINT);
		__device_data_format_map.Put(DataType::FLOAT, DXGI_FORMAT_R32_FLOAT);
		__device_data_format_map.Put(DataType::FLOAT2, DXGI_FORMAT_R32G32_FLOAT);
		__device_data_format_map.Put(DataType::FLOAT3, DXGI_FORMAT_R32G32B32_FLOAT);
		__device_data_format_map.Put(DataType::FLOAT4, DXGI_FORMAT_R32G32B32A32_FLOAT);

		__device_primitive_type_map.Put(PrimitiveType::TRIANGLE_LIST, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		__device_primitive_type_map.Put(PrimitiveType::TRIANGLE_STRIP, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	Device::~Device()
	{
		TH_SAFE_RELEASE(swapChain);
		TH_SAFE_RELEASE(context);
		TH_SAFE_RELEASE(device);
	}

	bool Device::Init(const Config* config)
	{
		auto app = Application::GetInstance();
		this->config = config;
		if (InitDevice(app->GetHwnd()) == false)
		{
			return false;
		}
		SetupRenderState();
		return true;
	}

	bool Device::InitDevice(HWND hwnd)
	{
		if (CreateDevice() == false)
			return false;

		//get multisample parameters
		UINT sampleCount, qualityLevel;
		GetMultiSampleType(&sampleCount, &qualityLevel);

		//create swap chain
		ZeroMemory(&this->chainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		this->chainDesc.BufferDesc.Width = config->width;
		this->chainDesc.BufferDesc.Height = config->height;
		this->chainDesc.BufferDesc.RefreshRate.Numerator = 60;
		this->chainDesc.BufferDesc.RefreshRate.Denominator = 1;
		this->chainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		this->chainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		this->chainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		this->chainDesc.SampleDesc.Count = sampleCount;
		this->chainDesc.SampleDesc.Quality = qualityLevel;
		this->chainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		this->chainDesc.BufferCount = 1;
		this->chainDesc.OutputWindow = hwnd;
		this->chainDesc.Windowed = !config->fullScreen;
		this->chainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		this->chainDesc.Flags = 0;

		if (CreateDeviceContext() == false)
			return false;

		InitRenderState();

		SetRenderTarget(GetColorBuffer());
		SetDepthBuffer(GetDepthBuffer());

		return true;
	}

	/*bool Device::CreateDevice()
	{
		HRESULT hr;

		D3D11CreateDevice(nullptr, )

		//设置帧率
		int refresh = D3DPRESENT_RATE_DEFAULT;

		D3DDEVTYPE deviceType;
		int vertexProcessingType;

		//获取设备描述
		GetDeviceInfo(&deviceType, &vertexProcessingType);

		//获取多重采样参数
		D3DMULTISAMPLE_TYPE multiSampleType;
		DWORD qualityLevel;

		GetMultiSampleType(deviceType, &multiSampleType, &qualityLevel);

		//检查设备能力
		if (CheckDeviceCaps(deviceType) == false)
		{
			return false;
		}

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = config->width;
		d3dpp.BackBufferHeight = config->height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = multiSampleType;
		d3dpp.MultiSampleQuality = qualityLevel;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.Windowed = !config->fullScreen;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		if (config->useVSync)
		{
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		}
		else
		{
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		}

		hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, deviceType,
			hWnd, vertexProcessingType | D3DCREATE_MULTITHREADED, &d3dpp, &device);

		InitRenderState();

		if (FAILED(hr))
		{
			return false;
		}

		THLog("Direct3D成功初始化。");
		return true;
	}*/

	bool Device::CreateDevice()
	{
		auto exceptionManager = ExceptionManager::GetInstance();
		HRESULT hr;

		D3D_DRIVER_TYPE driverTypes[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_REFERENCE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_NULL,
			D3D_DRIVER_TYPE_UNKNOWN
		};

		String deviceTypeLogInfo[] = {
			"使用硬件渲染模式（HAL）。",
			"使用软件渲染模式（REF）。",
			"使用软件渲染模式（WARP）。",
			"使用软件渲染模式（NULL）。",
			"使用未知渲染模式。"
		};

#ifdef _DEBUG
		UINT flags = D3D11_CREATE_DEVICE_DEBUG;
#else
		UINT flags = 0;
#endif
		int driverTypeCount = sizeof(driverTypes) / sizeof(D3D_DRIVER_TYPE);
		for (int i = 0; i < driverTypeCount; i++)
		{
			D3D_FEATURE_LEVEL featureLevel;
			if (FAILED(hr = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, flags, nullptr,
				0, D3D11_SDK_VERSION, &this->device, &featureLevel, &this->context)))
			{
				if (i < driverTypeCount - 1)
					continue;
				// create device failed
				exceptionManager->PushException(Ptr<Exception>::New((String)"错误代码" + hr));
				return false;
			}
			else
			{
				THLog(deviceTypeLogInfo[i]);
				switch (featureLevel)
				{
				case D3D_FEATURE_LEVEL_11_0:
					THLog("使用d3d11.0 feature level。");
					break;
				case D3D_FEATURE_LEVEL_10_1:
					THLog("使用d3d10.1 feature level。");
					break;
				case D3D_FEATURE_LEVEL_10_0:
					THLog("使用d3d10.0 feature level。");
					break;
				case D3D_FEATURE_LEVEL_9_3:
					THLog("使用d3d9.3 feature level。");
					break;
				case D3D_FEATURE_LEVEL_9_2:
					THLog("使用d3d9.2 feature level。");
					break;
				case D3D_FEATURE_LEVEL_9_1:
					THLog("使用d3d9.1 feature level。");
					break;
				}
				break;
			}
		}
		return true;
	}

	void Device::GetMultiSampleType(UINT* sampleCount, UINT* qualityLevel)
	{
		if (config->useMultiSample == false)
			*sampleCount = 1;
		else
			*sampleCount = 16;

		UINT qualityLevels;
		for (int i = *sampleCount; i > 0; i--)
		{
			*sampleCount = i;
			if (FAILED(this->device->CheckMultisampleQualityLevels(
				DXGI_FORMAT_R8G8B8A8_UNORM, i, &qualityLevels)))
				continue;
			if (qualityLevels > 0)
				break;
		}
		if (*sampleCount == 0)
		{
			*qualityLevel = 0;
			THLog("不使用多重采样。");
		}
		else
		{
			*qualityLevel = qualityLevels - 1;
			THLog((String)"使用多重采样。采样数为" + *sampleCount + "，质量等级" + *qualityLevel + "。");
		}
	}

	bool Device::CreateDeviceContext()
	{
		//get the IDXGIFactory instance
		IDXGIDevice* dxgiDevice = nullptr;
		if (FAILED(this->device->QueryInterface<IDXGIDevice>(&dxgiDevice)))
			return false;

		IDXGIAdapter* dxgiAdapter = nullptr;
		if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter)))
		{
			TH_SAFE_RELEASE(dxgiDevice);
			return false;
		}

		IDXGIFactory* dxgiFactory = nullptr;
		if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
		{
			TH_SAFE_RELEASE(dxgiAdapter);
			TH_SAFE_RELEASE(dxgiDevice);
			return false;
		}

		if (FAILED(dxgiFactory->CreateSwapChain(this->device, &this->chainDesc, &this->swapChain)))
		{
			TH_SAFE_RELEASE(dxgiFactory);
			TH_SAFE_RELEASE(dxgiAdapter);
			TH_SAFE_RELEASE(dxgiDevice);
			return false;
		}

		TH_SAFE_RELEASE(dxgiFactory);
		TH_SAFE_RELEASE(dxgiAdapter);
		TH_SAFE_RELEASE(dxgiDevice);
		return true;
	}

	/*void Device::GetDeviceInfo(D3D_DRIVER_TYPE* deviceType, int* vertexProcessingType)
	{
		HRESULT hr;
		hr = d3d->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_UNKNOWN, D3DFMT_UNKNOWN, !config->fullScreen);
		if (FAILED(hr))
		{
			*deviceType = D3DDEVTYPE_HAL;
			THLog("使用硬件渲染模式（HAL）。");
		}
		else
		{
			*deviceType = D3DDEVTYPE_REF;
			THLog("使用软件渲染模式（REF）。");
		}

		D3DCAPS9 d3dcaps;
		ZeroMemory(&d3dcaps, sizeof(d3dcaps));
		d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, *deviceType, &d3dcaps);

		if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			*vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
			THLog("使用硬件处理顶点。");
		}
		else
		{
			*vertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			THLog("使用软件处理顶点。");
		}
	}

	bool Device::CheckDeviceCaps(D3DDEVTYPE deviceType)
	{
		auto exceptionManager = ExceptionManager::GetInstance();

		D3DCAPS9 d3dcaps;
		ZeroMemory(&d3dcaps, sizeof(d3dcaps));
		d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &d3dcaps);

		//检查shader版本
		int mainVSVersion = (d3dcaps.VertexShaderVersion & 0x0000ff00) >> 8;
		int subVSVersion = d3dcaps.VertexShaderVersion & 0x000000ff;
		int mainPSVersion = (d3dcaps.PixelShaderVersion & 0x0000ff00) >> 8;
		int subPSVersion = d3dcaps.PixelShaderVersion & 0x000000ff;

		if (mainVSVersion < 2)
		{
			exceptionManager->PushException(Ptr<Exception>::New((String)"当前显卡支持的顶点着色器版本过低。\n"
				"当前支持版本：" + mainVSVersion + "." + subVSVersion
				+ "   最低需要版本：2.0"));
			return false;
		}

		if (mainPSVersion < 2)
		{
			exceptionManager->PushException(Ptr<Exception>::New((String)"当前显卡支持的像素着色器版本过低。\n"
				"当前支持版本：" + mainPSVersion + "." + subPSVersion
				+ "   最低需要版本：2.0"));
			return false;
		}

		//检查纹理格式支持
		D3DDISPLAYMODE mode;
		d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
		if (FAILED(d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, deviceType, mode.Format, D3DUSAGE_RENDERTARGET,
			D3DRTYPE_TEXTURE, D3DFMT_R32F)))
		{
			exceptionManager->PushException(Ptr<Exception>::New("您的显卡不支持32位浮点纹理。"));
			return false;
		}

		THLog("**********************设备信息**********************");
		THLog((String)"顶点着色器版本：" + mainVSVersion + "." + subVSVersion);
		THLog((String)"像素着色器版本：" + mainPSVersion + "." + subPSVersion);
		THLog("****************************************************");

		return true;
	}

	void Device::GetMultiSampleType(D3DDEVTYPE deviceType,
		D3DMULTISAMPLE_TYPE* multiSampleType,
		DWORD* qualityLevel)
	{
		HRESULT hr;

		const D3DMULTISAMPLE_TYPE multiSampleTypes[] = {
			D3DMULTISAMPLE_NONMASKABLE,
			D3DMULTISAMPLE_NONE,
			D3DMULTISAMPLE_2_SAMPLES,
			D3DMULTISAMPLE_3_SAMPLES,
			D3DMULTISAMPLE_4_SAMPLES,
			D3DMULTISAMPLE_5_SAMPLES,
			D3DMULTISAMPLE_6_SAMPLES,
			D3DMULTISAMPLE_7_SAMPLES,
			D3DMULTISAMPLE_8_SAMPLES,
			D3DMULTISAMPLE_9_SAMPLES,
			D3DMULTISAMPLE_10_SAMPLES,
			D3DMULTISAMPLE_11_SAMPLES,
			D3DMULTISAMPLE_12_SAMPLES,
			D3DMULTISAMPLE_13_SAMPLES,
			D3DMULTISAMPLE_14_SAMPLES,
			D3DMULTISAMPLE_15_SAMPLES,
			D3DMULTISAMPLE_16_SAMPLES
		};

		DWORD qualityLevels;
		if (config->useMultiSample)
		{
			*multiSampleType = D3DMULTISAMPLE_16_SAMPLES;
		}
		else
		{
			*multiSampleType = D3DMULTISAMPLE_NONE;
			*qualityLevel = 0;
		}

		for (int i = *multiSampleType; i > 0; i--)
		{
			hr = d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, deviceType, D3DFMT_A8R8G8B8,
				!config->fullScreen, multiSampleTypes[i], &qualityLevels);
			if (!FAILED(hr))
			{
				*multiSampleType = multiSampleTypes[i];
				if (*multiSampleType == D3DMULTISAMPLE_NONE)
				{
					*qualityLevel = 0;
				}
				else
				{
					if (qualityLevels == NULL)
					{
						*qualityLevel = 0;
					}
					else
					{
						*qualityLevel = qualityLevels - 1;
					}
				}
				break;
			}
		}
		if (*multiSampleType == D3DMULTISAMPLE_NONE)
		{
			THLog("不使用多重采样。");
		}
		else
		{
			THLog((String)"使用多重采样。采样数为" + *multiSampleType + "，质量等级" + *qualityLevel + "。");
		}
	}*/

	void Device::InitRenderState()
	{
		this->renderState->colorBuffer = Ptr<RenderTexture>::New();
		this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(&this->renderState->colorBuffer->texture));
		this->device->CreateRenderTargetView(this->renderState->colorBuffer->texture, nullptr,
			&this->renderState->colorBuffer->renderTargetView);
		this->device->CreateShaderResourceView(this->renderState->colorBuffer->texture, nullptr,
			&this->renderState->colorBuffer->shaderResourceView);

		this->renderState->depthBuffer = CreateDepthBuffer(this->config->width, this->config->height, false);
	}

	void Device::SetupRenderState()
	{
		if (this->renderState->isBlendDirty)
		{
			const BlendMode& blendMode = this->renderState->blendMode;
			D3D11_BLEND_DESC desc;
			desc.AlphaToCoverageEnable = false;
			desc.IndependentBlendEnable = false;
			desc.RenderTarget[0].BlendEnable = this->renderState->isAlphaBlendEnabled;
			desc.RenderTarget[0].BlendOp = __device_blend_op_map.Get(blendMode.blendOp);
			desc.RenderTarget[0].BlendOpAlpha = __device_blend_op_map.Get(blendMode.alphaOp);
			desc.RenderTarget[0].SrcBlend = __deivce_blend_factor_map.Get(blendMode.srcFactor);
			desc.RenderTarget[0].DestBlend = __deivce_blend_factor_map.Get(blendMode.destFactor);
			desc.RenderTarget[0].SrcBlendAlpha = __deivce_blend_factor_map.Get(blendMode.srcAlphaFactor);
			desc.RenderTarget[0].DestBlendAlpha = __deivce_blend_factor_map.Get(blendMode.destAlphaFactor);
			desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			ID3D11BlendState* blendState = nullptr;
			this->device->CreateBlendState(&desc, &blendState);
			this->context->OMSetBlendState(blendState, blendMode.blendFactor._data, 0xffffffff);
			blendState->Release();

			this->renderState->isBlendDirty = false;
		}

		if (this->renderState->isRasterizerDirty)
		{
			D3D11_RASTERIZER_DESC desc;
			desc.CullMode = __device_cull_mode_map.Get(this->renderState->cullMode);
			desc.FillMode = __device_fill_mode_map.Get(this->renderState->fillMode);
			desc.FrontCounterClockwise = false;
			desc.AntialiasedLineEnable = false;
			desc.DepthBias = 0.0f;
			desc.DepthBiasClamp = 0.0f;
			desc.DepthClipEnable = true;
			desc.MultisampleEnable = false;
			desc.ScissorEnable = false;
			desc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* state = nullptr;
			this->device->CreateRasterizerState(&desc, &state);
			this->context->RSSetState(state);
			state->Release();

			this->renderState->isRasterizerDirty = false;
		}

		if (this->renderState->isDepthStencilDirty)
		{
			D3D11_DEPTH_STENCIL_DESC desc;
			desc.DepthEnable = this->renderState->isDepthTestEnabled;
			desc.DepthFunc = __device_compare_op_map.Get(this->renderState->depthOp);
			desc.DepthWriteMask = this->renderState->isDepthWriteEnabled ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.StencilEnable = this->renderState->isStencilTestEnabled;
			desc.StencilReadMask = this->renderState->stencilReadMask;
			desc.StencilWriteMask = this->renderState->stencilWriteMask;
			desc.FrontFace.StencilFunc = __device_compare_op_map.Get(this->renderState->stencilOp);
			desc.FrontFace.StencilFailOp = __device_stencil_op_map.Get(this->renderState->stencilFail);
			desc.FrontFace.StencilDepthFailOp = __device_stencil_op_map.Get(this->renderState->stencilDepthFail);
			desc.FrontFace.StencilPassOp = __device_stencil_op_map.Get(this->renderState->stencilPass);
			desc.BackFace = desc.FrontFace;

			ID3D11DepthStencilState* state = nullptr;
			this->device->CreateDepthStencilState(&desc, &state);
			this->context->OMSetDepthStencilState(state, this->renderState->stencilRef);
			state->Release();

			this->renderState->isDepthStencilDirty = false;
		}

		if (this->renderState->isRenderTargetDirty)
		{
			this->context->OMSetRenderTargets(1, &this->renderState->renderTarget->renderTargetView,
				this->renderState->depthBuffer->view);
			this->renderState->isRenderTargetDirty = false;
		}
	}

	void Device::EndRender()
	{
		if (renderState->shader != nullptr)
		{
			renderState->shader->End();
		}
	}

	void Device::SetOrtho(float left, float bottom, float width, float height, float znear, float zfar)
	{
		Matrix projection;
		Matrix::Ortho(&projection, left, left + width, bottom, bottom + height, znear, zfar);
		SetProjectionMatrix(projection);
	}

	void Device::SetViewport(int left, int top, int width, int height)
	{
		renderState->viewport.x = left;
		renderState->viewport.y = top;
		renderState->viewport.width = width;
		renderState->viewport.height = height;
		renderState->viewport.minZ = 0;
		renderState->viewport.maxZ = 1;

		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = renderState->viewport.x;
		viewport.TopLeftY = renderState->viewport.y;
		viewport.Width = renderState->viewport.width;
		viewport.Height = renderState->viewport.height;
		viewport.MinDepth = renderState->viewport.minZ;
		viewport.MaxDepth = renderState->viewport.maxZ;
		this->context->RSSetViewports(1, &viewport);
	}

	void Device::SetRenderTarget(Ptr<RenderTexture> texture)
	{
		if (texture == nullptr)
		{
			texture = GetColorBuffer();
		}

		if (this->renderState->renderTarget != texture)
		{
			this->renderState->renderTarget = texture;
			renderState->isRenderTargetDirty = true;
		}
	}

	void Device::SetDepthBuffer(Ptr<DepthBuffer> depthBuffer)
	{
		if (this->renderState->depthBuffer != depthBuffer)
		{
			this->renderState->depthBuffer = depthBuffer;
			renderState->isRenderTargetDirty = true;
		}
	}

	Ptr<DepthBuffer> Device::CreateDepthBuffer(int width, int height, bool forTexture)
	{
		Ptr<DepthBuffer> depthBuffer = Ptr<DepthBuffer>::New();

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (forTexture == false)
			desc.SampleDesc = this->chainDesc.SampleDesc;
		else
		{
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
		}
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		if (FAILED(this->device->CreateTexture2D(&desc, 0, &depthBuffer->buffer)))
			return nullptr;

		if (FAILED(this->device->CreateDepthStencilView(depthBuffer->buffer, nullptr, &depthBuffer->view)))
			return nullptr;

		return depthBuffer;
	}

	void Device::SetBlendMode(const BlendMode& blendMode)
	{
		if (blendMode != this->renderState->blendMode)
		{
			this->renderState->blendMode = blendMode;
			this->renderState->isBlendDirty = true;
		}
	}

	void Device::EnableDepthTest(bool value)
	{
		if (this->renderState->IsDepthTestEnabled() != value)
		{
			this->renderState->isDepthTestEnabled = value;
			this->renderState->isDepthStencilDirty = true;
		}
	}

	bool Device::IsDeviceLost()
	{
		return false;
	}

	bool Device::NeedResetDevice()
	{
		return false;
	}

	void Device::OnLostDevice()
	{
		AssetManager::GetInstance()->OnLostDevice();
	}

	void Device::OnResetDevice()
	{
		TH_SAFE_RELEASE(this->swapChain);
		TH_SAFE_RELEASE(this->context);
		TH_SAFE_RELEASE(this->device);
		Init(this->config);
		AssetManager::GetInstance()->OnResetDevice();
	}

	Ptr<StaticVertexBuffer> Device::CreateStaticVertexBuffer(size_t maxBytes, const void* data)
	{
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = maxBytes;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sd;
		sd.pSysMem = data;
		sd.SysMemPitch = 0;
		sd.SysMemSlicePitch = 0;

		Ptr<StaticVertexBuffer> vb = Ptr<StaticVertexBuffer>::New();
		if (FAILED(this->device->CreateBuffer(&desc, &sd, &vb->buffer)))
			return nullptr;
		return vb;
	}

	Ptr<DynamicVertexBuffer> Device::CreateDynamicVertexBuffer(size_t maxBytes)
	{
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = maxBytes;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		Ptr<DynamicVertexBuffer> vb = Ptr<DynamicVertexBuffer>::New();
		if (FAILED(this->device->CreateBuffer(&desc, nullptr, &vb->buffer)))
			return nullptr;
		return vb;
	}

	Ptr<StaticIndexBuffer> Device::CreateStaticIndexBuffer(size_t maxBytes, const void* data)
	{
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = maxBytes;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sd;
		sd.pSysMem = data;
		sd.SysMemPitch = 0;
		sd.SysMemSlicePitch = 0;

		Ptr<StaticIndexBuffer> ib = Ptr<StaticIndexBuffer>::New();
		if (FAILED(this->device->CreateBuffer(&desc, &sd, &ib->buffer)))
			return nullptr;
		return ib;
	}

	Ptr<DynamicIndexBuffer> Device::CreateDynamicIndexBuffer(size_t maxBytes)
	{
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = maxBytes;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		Ptr<DynamicIndexBuffer> ib = Ptr<DynamicIndexBuffer>::New();
		if (FAILED(this->device->CreateBuffer(&desc, nullptr, &ib->buffer)))
			return nullptr;
		return ib;
	}

	void Device::SetVertexBuffer(Ptr<VertexBuffer> vb, size_t stride, int stream)
	{
		UINT offset = 0;
		this->context->IASetVertexBuffers(stream, 1, &vb->buffer, &stride, &offset);
	}

	void Device::SetIndexBuffer(Ptr<IndexBuffer> ib)
	{
		this->context->IASetIndexBuffer(ib->buffer, DXGI_FORMAT_R32_UINT, 0);
	}

	Ptr<VertexFormat> Device::CreateVertexFormat(const std::vector<VertexFormatItem>& items,
		Ptr<Shader> shader, const char* tech, int pass)
	{
		HRESULT hr;
		std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
		for (const VertexFormatItem& item : items)
		{
			D3D11_INPUT_ELEMENT_DESC desc;
			desc.SemanticName = __device_semantic_map.Get(item.semantic);
			desc.SemanticIndex = item.semanticIndex;
			desc.AlignedByteOffset = item.offset;
			desc.Format = __device_data_format_map.Get(item.dataType);
			desc.InputSlot = item.stream;
			desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc.InstanceDataStepRate = 0;
			descs.push_back(desc);
		}

		D3DX11_PASS_DESC passDesc;
		if (FAILED(hr = shader->effect->GetTechniqueByName(tech)->GetPassByIndex(pass)->GetDesc(&passDesc)))
		{
			auto exceptionManager = ExceptionManager::GetInstance();
			exceptionManager->PushException(Ptr<Exception>::New((String)"获取着色器描述失败。错误代码：" + hr));
			return nullptr;
		}

		Ptr<VertexFormat> format = Ptr<VertexFormat>::New();
		if (FAILED(this->device->CreateInputLayout(&descs[0], descs.size(),
			passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &format->layout)))
		{
			auto exceptionManager = ExceptionManager::GetInstance();
			exceptionManager->PushException(Ptr<Exception>::New((String)"CreateInputLayout失败。错误代码：" + hr));
			return nullptr;
		}
		return format;
	}

	void Device::SetVertexFormat(Ptr<VertexFormat> format)
	{
		this->context->IASetInputLayout(format->layout);
	}

	void Device::Draw(PrimitiveType primitiveType, size_t verticesCount, size_t startVertex)
	{
		SetupRenderState();

		if (renderState->primitiveType != primitiveType)
		{
			renderState->primitiveType = primitiveType;
			this->context->IASetPrimitiveTopology(__device_primitive_type_map.Get(primitiveType));
		}

		this->context->Draw(verticesCount, startVertex);
	}

	void Device::DrawIndexed(PrimitiveType primitiveType, size_t indicesCount, size_t startIndex, size_t startVertex)
	{
		SetupRenderState();

		if (renderState->primitiveType != primitiveType)
		{
			renderState->primitiveType = primitiveType;
			this->context->IASetPrimitiveTopology(__device_primitive_type_map.Get(primitiveType));
		}

		this->context->DrawIndexed(indicesCount, startIndex, startVertex);
	}
}