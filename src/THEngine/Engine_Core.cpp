#include "stdafx.h"
#include "Engine_Core.h"
#include "../Stage/Stage1/Stage1.h"

/********************************THEngine*************************/
THEngine::THEngine(int width, int height, bool isFullScreen)
{
	_width = width;
	_height = height;
	_isFullScreen = isFullScreen;

	_width_scale = _width / 640.0f;
	_height_scale = _height / 480.0f;
	_shoot_width = 384 * _width_scale;
	_shoot_height = 448 * _height_scale;
	_shoot_left = 32 * _width_scale;
	_shoot_top = 16 * _height_scale;

	for (int i = 0; i < TH_MAX_TEXTURE; i++) {
		_texList[i] = 0;
	}
	for (int i = 0; i < TH_MAX_SOUND; i++) {
		_soundBuffer[i] = 0;
	}
	_isPaused = false;
	_player = NULL;
	_stage = NULL;
	_sprite = NULL;
	_device = NULL;
	_d3d = NULL;
	_sound = NULL;
	_input = NULL;
	_effectFilter = NULL;
	_enemylist = new RenderList<THEnemy>;
	_bulletlist = new RenderList<THBullet>;
	_playerbulletlist = new RenderList<THPlayerBullet>;
	_renderlist = new RenderList<RenderObject>;
	_itemlist = new RenderList<THItem>;
}

THEngine::~THEngine()
{
	Shutdown();
}

void THEngine::Shutdown()
{
	for (int i = 0; i<TH_MAX_TEXTURE; i++){
		TH_D3D_RELEASE(_texList[i]);
	}
	for (int i = 0; i<TH_MAX_SOUND; i++){
		TH_D3D_RELEASE(_soundBuffer[i]);
	}
	TH_SAFE_DELETE(_stage);
	TH_SAFE_DELETE(_player);
	TH_SAFE_DELETE(_enemylist);
	TH_SAFE_DELETE(_bulletlist);
	TH_SAFE_DELETE(_playerbulletlist);
	TH_SAFE_DELETE(_itemlist);
	TH_SAFE_DELETE(_renderlist);
	TH_SAFE_DELETE(_sprite);

	TH_D3D_RELEASE(_effectFilter);
	TH_D3D_RELEASE(_input);
	TH_D3D_RELEASE(_sound);
	TH_D3D_RELEASE(_device);
	TH_D3D_RELEASE(_d3d);
}


int THEngine::Init(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT hr;
	UINT refresh;

	//记录日志
	ofstream logFile("THLog.txt");
	SYSTEMTIME time;
	GetLocalTime(&time);
	logFile << "游戏开始于" << time.wYear << "年" << time.wMonth << "月"
		<< time.wDay << "日" << time.wHour << ":" << time.wMinute << ":" << time.wSecond << "。" << endl;

	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 d3dcaps;
	_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps);

	int vertexProcessingType = 0;
	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT){
		vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		logFile << "使用硬件处理顶点。" << endl;
	}
	else{
		vertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		logFile << "使用软件处理顶点。" << endl;
	}

	//D3DDISPLAYMODE mode;
	//m_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	//int count = m_d3d9->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8R8G8B8);
	//m_d3d->EnumAdapterModes(D3DADAPTER_DEFAULT, mode.Format, 0, &mode);

	if (!_isFullScreen){
		refresh = 0;
	}
	else{
		refresh = 60;
		ShowCursor(FALSE);
	}

	ZeroMemory(&_d3dpp, sizeof(_d3dpp));
	_d3dpp.BackBufferWidth = _width;
	_d3dpp.BackBufferHeight = _height;
	_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	_d3dpp.BackBufferCount = 1;
	_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	_d3dpp.MultiSampleQuality = 0;
	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow = hwnd;
	_d3dpp.Windowed = !_isFullScreen;
	_d3dpp.EnableAutoDepthStencil = true;
	_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	_d3dpp.Flags = 0;
	_d3dpp.FullScreen_RefreshRateInHz = refresh;
	_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	hr = _d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		vertexProcessingType,
		&_d3dpp,
		&_device);

	if (FAILED(hr)){
		if (hr == D3DERR_INVALIDCALL){
			THMessageBox(TEXT("CreateDevice Failed!"));
		}
		return -1;
	}

	_hwnd = hwnd;
	_hInstance = hInstance;

	/******************初始化视口******************/
	_vp.X = 0;
	_vp.Y = 0;
	_vp.Width = _width;
	_vp.Height = _height;
	_vp.MinZ = 0;
	_vp.MaxZ = 1;

	_vpShoot.X = _shoot_left;
	_vpShoot.Y = _shoot_top;
	_vpShoot.Width = _shoot_width;
	_vpShoot.Height = _shoot_height;
	_vpShoot.MinZ = 0;
	_vpShoot.MaxZ = 1;

	/*****************矩阵初始化*********************/
	D3DXMatrixOrthoOffCenterLH(
		&_proj,
		0,
		640,
		0,
		480,
		0,
		1000);

	D3DXMATRIX trans1;
	D3DXMatrixIdentity(&trans1);
	trans1._22 = -1;
	_proj *= trans1;

	D3DXMatrixOrthoOffCenterLH(&_projShoot, 0, 384, 0, 448, 0, 1000);
	_projShoot *= trans1;

	_device->SetTransform(D3DTS_PROJECTION, &_proj);

	/*****************初始化Effects********************/
	if (InitEffects() < 0){
		return -1;
	}



	/*****************初始化DirectInput****************/
	if (InitDirectInput() < 0){
		THMessageBox(TEXT("DirectInput初始化失败了!"));
		return -1;
	}
	logFile << "DirectInput正常初始化了。" << endl;

	/*****************初始化DirectSound****************/
	if (InitDirectSound() < 0){
		THMessageBox(TEXT("DirectSound初始化失败了!"));
		return -1;
	}
	logFile << "DirectSound正常初始化了。" << endl;

	/*****************计算菜单位置*********************/
	//m_menuleft = screen_width * 0.75;
	//m_menutop = screen_height * 0.5;
	//m_menuwidth = screen_width * 0.25;
	//m_menuheight = screen_height * 0.05;

	if (InitFont() < 0){
		THMessageBox(TEXT("字体创建失败!"));
		return -1;
	}

	/****************杂项初始化********************/
	_TimeElapsed = 0;
	_FrameCount = 0;
	_curtime = _lasttime = -1;
	_FPS = 0;

	_GameState = GAME_MAIN_MENU;
	_menuSelection = TH_MENU_START;

	if (LoadContent() < 0){
		return -1;
	}

	if (LoadSound() < 0){
		return -1;
	}
	//srand(time(NULL));

	//return D3D_OK;
	return 0;
}

int THEngine::InitEffects()
{
	if (LoadEffect(TEXT("fx/Filter.fx"), &_effectFilter) < 0){
		return -1;
	}
	_effectFilter->SetTechnique("Filter");
	return 0;
}


int THEngine::LoadEffect(TCHAR* srcPath, ID3DXEffect** effect)
{
	ID3DXBuffer *error;
	if (FAILED(D3DXCreateEffectFromFile(_device, srcPath, NULL, NULL, D3DXSHADER_DEBUG, NULL, effect, &error))){
		if (error){
			char *ErrorString = (char*)error->GetBufferPointer();
			TCHAR WideErrorString[500];
			MultiByteToWideChar(CP_ACP, NULL, ErrorString, error->GetBufferSize(), WideErrorString, sizeof(WideErrorString));
			THMessageBox(WideErrorString);
		}
		return -1;
	}
	return 0;
}

int THEngine::InitDirectInput()
{
	HRESULT hr;
	hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_input, NULL);
	if (FAILED(hr)){
		THMessageBox(TEXT("Create DirectInput failed!"));
		return -1;
	}

	hr = _input->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL);
	if (FAILED(hr)){
		THMessageBox(TEXT("Create keyboard device failed!"));
		return -1;
	}

	hr = _keyboard->SetCooperativeLevel(_hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)){
		THMessageBox(TEXT("Set keyboard cooperative level failed!"));
		return -1;
	}

	hr = _keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)){
		THMessageBox(TEXT("Set keyboard data format failed!"));
		return -1;
	}

	hr = _keyboard->Acquire();
	if (FAILED(hr)){
		THMessageBox(TEXT("Acquire keyboard failed!"));
		return -1;
	}
	return 0;
}

int THEngine::InitDirectSound()
{
	HRESULT hr;
	// Create DirectSound.
	if (FAILED(hr = DirectSoundCreate(NULL, &_sound, NULL)))
		return -1;

	// Set cooperative level.
	if (FAILED(hr = _sound->SetCooperativeLevel(_hwnd, DSSCL_PRIORITY)))
		return -1;

	return 0;
}

int THEngine::InitFont()
{
	D3DXFONT_DESC df;
	ZeroMemory(&df, sizeof(df));
	df.Height = 20;
	df.Weight = 8;
	df.MipLevels = D3DX_DEFAULT;
	df.Italic = false;
	df.CharSet = GB2312_CHARSET;
	df.OutputPrecision = 0;
	df.Quality = 0;
	df.PitchAndFamily = 0;
	lstrcpy(df.FaceName, TEXT("微软雅黑"));

	HRESULT hr = D3DXCreateFontIndirect(_device, &df, &_fontFPS);
	if (FAILED(hr)){
		return -1;
	}
	return 0;
}

int THEngine::LoadContent()
{
	/*****************初始化Sprite********************/
	_sprite = new THSprite;
	if (_sprite->Create(this) < 0){
		return -1;
	}

	if (LoadTexture() < 0){
		return -1;
	}

	if (InitEffects() < 0){
		return -1;
	}

	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_GAUSSIANQUAD);
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_GAUSSIANQUAD);
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_GAUSSIANQUAD);

	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	return 0;
}

int THEngine::LoadTexture()
{
	if ((_texBullet = CreateTexture(TEXT("res/bullet/etama.png"))) < 0){
		return -1;
	}
	if ((_texBullet2 = CreateTexture(TEXT("res/bullet/etama2.png"))) < 0){
		return -1;
	}
	if ((_texPlayer = CreateTexture(TEXT("res/player00.png"))) < 0){
		return -1;
	}
	if ((_texItem = CreateTexture(TEXT("res/bullet/item.jpg"))) < 0){
		return -1;
	}
	if ((_texFront = CreateTexture(TEXT("res/front/front00.png"))) < 0){
		return -1;
	}
	if ((_texEnemy = CreateTexture(TEXT("res/enemy/enemy.png"))) < 0){
		return -1;
	}
	if ((_texTitle = CreateTexture(TEXT("res/title00.jpg"))) < 0){
		return -1;
	}
	if ((_texGameBgr = CreateTexture(TEXT("res/front/gamebg.png"))) < 0){
		return -1;
	}
	if ((_texEffect1 = CreateTexture(TEXT("res/effect/effect1.png"))) < 0){
		return -1;
	}
	return 0;
}

int THEngine::LoadSound()
{
	if ((_soundBiu = CreateSound(TEXT("SE/se_pldead00.wav"))) < 0){
		return -1;
	}
	if ((_soundShoot1 = CreateSound(TEXT("SE/se_tan01.wav"))) < 0){
		return -1;
	}
	if ((_soundOK = CreateSound(TEXT("SE/se_ok00.wav"))) < 0){
		return -1;
	}
	if ((_soundDamage = CreateSound(TEXT("SE/se_damage00.wav"))) < 0){
		return -1;
	}
	return 0;
}

void THEngine::UploadContent()
{
	TH_D3D_RELEASE(_effectFilter);
	TH_SAFE_DELETE(_sprite);
	for (int i = 0; i<TH_MAX_TEXTURE; i++){
		TH_D3D_RELEASE(_texList[i]);
	}
}

void THEngine::LoadStage()
{
	TH_SAFE_DELETE(_stage);
	switch (_stageNumber){
	case 1:
		_stage = new Stage1;
		break;
	}
}

void THEngine::CalcFPS()
{
	_curtime = GetTickCount();
	if (_lasttime > 0){
		_TimeElapsed += _curtime - _lasttime;
	}
	_lasttime = _curtime;
	_FrameCount++;

	if (_TimeElapsed >= 1000.0f){
		_FPS = (float)_FrameCount / _TimeElapsed * 1000;
		_TimeElapsed = _FrameCount = 0;
	}
}

void THEngine::DrawFPS()
{
	RECT rc;
	rc.left = _width - 100;
	rc.right = _width - 10;
	rc.top = _height - 30;
	rc.bottom = _height - 10;
	TCHAR string[15];
	LPTSTR szBuffer = string;
	swprintf(string, sizeof(string), TEXT("%.2f FPS"), _FPS);
	_fontFPS->DrawText(NULL, string, lstrlen(string), &rc, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

void THEngine::DrawMenu()
{
	int i;
	int menuleft = _width * 0.75;
	int menutop = _height * 0.5;
	int menuwidth = _width * 0.25;
	int menuheight = _height * 0.05;

	for (i = 0; i < 10; i++) {
		RECT rc;
		rc.left = menuleft;
		rc.right = rc.left + menuwidth;
		rc.top = menutop + menuheight * i;
		rc.bottom = rc.top + menuheight;
		if (i == _menuSelection){
			_fontFPS->DrawText(NULL, szMenu[i], lstrlen(szMenu[i]), &rc, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 0, 0));
		}
		else{
			_fontFPS->DrawText(NULL, szMenu[i], lstrlen(szMenu[i]), &rc, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		}
	}
}

void THEngine::DrawFront()
{
	D3DXMATRIX dm;
	D3DXMatrixIdentity(&dm);
	_sprite->SetTransform(&dm);
	SpriteBegin();

	//绘制最高得分和得分栏
	SpriteDraw(_texFront, 0, 0, 72, 24, 424, 36, 0);
	SpriteDraw(_texFront, 0, 24, 72, 48, 424, 60, 0);
	int score[11];
	int temp = _highscore;
	for (int i = 0; i<10; i++){
		score[i] = temp % 10;
		temp /= 10;
	}
	for (int i = 9; i >= 0; i--){
		SpriteDraw(_texFront, 80 + 16 * score[i], 0, 96 + 16 * score[i], 24, 504 + (9 - i) * 12, 36, 0);
	}
	temp = _score;
	for (int i = 0; i<10; i++){
		score[i] = temp % 10;
		temp /= 10;
	}
	for (int i = 9; i >= 0; i--){
		SpriteDraw(_texFront, 80 + 16 * score[i], 0, 96 + 16 * score[i], 24, 504 + (9 - i) * 12, 60, 0);
	}

	//绘制残机和符卡栏
	SpriteDraw(_texFront, 0, 48, 72, 72, 424, 100, 0);
	SpriteDraw(_texFront, 0, 72, 72, 96, 424, 124, 0);

	//灵力栏
	SpriteDraw(_texFront, 80, 48, 128, 72, 424, 160, 0);
	int power[3];
	temp = _player->power;
	for (int i = 0; i<3; i++){
		power[i] = temp % 10;
		temp /= 10;
	}
	SpriteDraw(_texFront, 80 + 16 * power[2], 24, 96 + 16 * power[2], 48, 504, 160, 0);
	SpriteDraw(_texFront, 160, 48, 176, 72, 516, 160, 0);
	SpriteDraw(_texFront, 80 + 16 * power[1], 24, 96 + 16 * power[1], 48, 528, 160, 0);
	SpriteDraw(_texFront, 80 + 16 * power[0], 24, 96 + 16 * power[0], 48, 540, 160, 0);
	SpriteDraw(_texFront, 144, 48, 160, 72, 556, 160, 0);
	temp = _player->maxpower;
	for (int i = 0; i<3; i++){
		power[i] = temp % 10;
		temp /= 10;
	}
	SpriteDraw(_texFront, 80 + 16 * power[2], 24, 96 + 16 * power[2], 48, 572, 160, 0);
	SpriteDraw(_texFront, 160, 48, 176, 72, 584, 160, 0);
	SpriteDraw(_texFront, 80 + 16 * power[1], 24, 96 + 16 * power[1], 48, 596, 160, 0);
	SpriteDraw(_texFront, 80 + 16 * power[0], 24, 96 + 16 * power[0], 48, 608, 160, 0);

	SpriteEnd();
}

void THEngine::OnLostDevice()
{
	_fontFPS->OnLostDevice();
	UploadContent();
}

void THEngine::OnResetDevice()
{
	HRESULT hr;
	//m_fontMenu->OnResetDevice();
	if (!_device)
		return;
	hr = _device->Reset(&_d3dpp);
	if (FAILED(hr)){
		TCHAR str[50];
		swprintf(str, sizeof(str), L"ResetDevice Failed!\nError Code:%d", hr);
		THMessageBox(str);
		return;
	}
	LoadContent();
	//LoadStageContent();
}

HRESULT THEngine::DIGetKeyboardState()
{
	HRESULT hr;
	if (!_keyboard){
		return S_OK;
	}
	while ((hr = _keyboard->GetDeviceState(256, &_keystate)) == DIERR_INPUTLOST){
		hr = _keyboard->Acquire();
		if (FAILED(hr)){
			return hr;
		}
	}
	if (FAILED(hr))
		return hr;
	return S_OK;
}

void THEngine::GetInput()
{
	HRESULT hr;
	if (!_player->IsDead()){
		hr = DIGetKeyboardState();
		if (SUCCEEDED(hr)){
			if (DIKEYDOWN(_keystate, DIK_LSHIFT) || DIKEYDOWN(_keystate, DIK_RSHIFT)){
				_player->bHigh = false;
			}
			else{
				_player->bHigh = true;
			}
			if (DIKEYDOWN(_keystate, DIK_LEFT)){
				if (DIKEYDOWN(_keystate, DIK_UP)){
					_player->SetPlayerDirection(DIRECTION_LEFT_AND_UP);
				}
				else if (DIKEYDOWN(_keystate, DIK_DOWN)){
					_player->SetPlayerDirection(DIRECTION_LEFT_AND_DOWN);
				}
				else{
					_player->SetPlayerDirection(DIRECTION_LEFT);
				}
			}
			else if (DIKEYDOWN(_keystate, DIK_RIGHT)){
				if (DIKEYDOWN(_keystate, DIK_UP)){
					_player->SetPlayerDirection(DIRECTION_RIGHT_AND_UP);
				}
				else if (DIKEYDOWN(_keystate, DIK_DOWN)){
					_player->SetPlayerDirection(DIRECTION_RIGHT_AND_DOWN);
				}
				else{
					_player->SetPlayerDirection(DIRECTION_RIGHT);
				}
			}
			else if (DIKEYDOWN(_keystate, DIK_UP)) _player->SetPlayerDirection(DIRECTION_UP);
			else if (DIKEYDOWN(_keystate, DIK_DOWN)) _player->SetPlayerDirection(DIRECTION_DOWN);
			else _player->SetPlayerDirection(DIRECTION_STABLE);
		}
	}
}

void THEngine::Biu()
{
	_player->Biu();
	PlaySE(_soundBiu);
}

void THEngine::PrintScreen()
{
	IDirect3DSurface9 *surface;
	_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	D3DXSaveSurfaceToFile(TEXT("snapshot/1.png"), D3DXIFF_PNG, surface, NULL, NULL);
}

void THEngine::Update()
{
	HRESULT hr;

	switch (_GameState){
	case GAME_START:
		if (_isPaused){
			break;
		}

		_stage->CommonUpdate();

		if (!_player->IsDead()){
			RenderObjectNode<THBullet> *p;
			for (p = _bulletlist->head->next; p; p = p->next){
				if (p->obj->HasDetermination()){
					if (p->obj->Hit(_player->GetX(), _player->GetY(), _player->r)){
						Biu();
					}
				}
			}
		}

		RenderObjectNode<THEnemy> *p;
		RenderObjectNode<THPlayerBullet> *q;
		for (p = _enemylist->head->next; p; p = p->next){
			for (q = _playerbulletlist->head->next; q; q = q->next){
				if (q->obj->Hit(
					p->obj->GetX() - p->obj->GetDamageRectW() / 2,
					p->obj->GetY() - p->obj->GetDamageRectH() / 2,
					p->obj->GetX() + p->obj->GetDamageRectW() / 2,
					p->obj->GetY() + p->obj->GetDamageRectH() / 2
					)){
					PlaySE(_soundDamage);
					p->obj->SetLife(p->obj->GetLife() - q->obj->GetDamage());
					if (q->obj->AttackOnce()){
						q->obj->MarkDelete();
					}
				}
			}
		}
		GetInput();
		_player->Update();
		if (!_player->IsDead() && DIKEYDOWN(_keystate, DIK_Z)){
			_player->Fire();
		}

		/*if (!m_eventlist.empty()){
			Event *e = m_eventlist.top();
			if (e->nOccurFrame == m_FrameElapsed){
				e->onEvent();
				m_eventlist.pop();
				delete e;
			}
		}*/

		_enemylist->Update();
		_bulletlist->Update();
		_playerbulletlist->Update();
		_itemlist->Update();
		_renderlist->Update();

		break;
	}
}

void THEngine::Render()
{
	if (_isPaused){
		return;
	}
	_device->SetViewport(&_vp);
	_device->SetTransform(D3DTS_PROJECTION, &_proj);

	_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(1, 0, 255, 255), 1, 0);
	_device->BeginScene();
	switch (_GameState){
	case GAME_MAIN_MENU:
	{
		SpriteBegin();
		D3DXMATRIX dm;
		D3DXMatrixScaling(&dm, 0.625, 0.9375, 1);
		_sprite->SetTransform(&dm);
		SpriteDraw(_texTitle, 0, 0, 1024, 512, 0, 0, 100);
		SpriteEnd();

		DrawMenu();
		break;
	}
	case GAME_START:
	{
		SpriteBegin();
		D3DXMATRIX dm;
		D3DXMatrixScaling(&dm, 0.625, 0.9375, 1);
		_sprite->SetTransform(&dm);
		SpriteDraw(_texGameBgr, 0, 0, 1024, 512, 0, 0, 999);
		SpriteEnd();

		DrawFront();

		_device->SetViewport(&_vpShoot);

		_stage->CommonDraw();

		_device->SetTransform(D3DTS_PROJECTION, &_projShoot);

		SpriteBegin();
		_player->Draw();
		_enemylist->Render();
		_bulletlist->Render();
		_playerbulletlist->Render();
		_itemlist->Render();
		_renderlist->Render();
		SpriteEnd();
		break;
	}
	}
	_device->SetViewport(&_vp);
	_device->SetTransform(D3DTS_PROJECTION, &_proj);
	CalcFPS();
	DrawFPS();
	_device->EndScene();
	if (_device->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST){
		HRESULT hr = _device->TestCooperativeLevel();
		if (hr == D3DERR_DEVICENOTRESET){
			OnLostDevice();
			OnResetDevice();
		}
	}
}

