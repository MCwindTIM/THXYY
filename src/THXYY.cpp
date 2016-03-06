#include "stdafx.h"
#include "THXYY.h"
#include "Player.h"
#include "Resource.h"

THXYY::THXYY()
{
	_engine = NULL;
}

THXYY::~THXYY()
{
	TH_SAFE_DELETE(_engine);
}

THEngine* THXYY::GetEngine()
{
	return _engine;
}

int THXYY::CreateGame(HINSTANCE hInstance, UINT nCmdShow, int width, int height, bool isFullScreen)
{
	_hInstance = hInstance;
	_width = width;
	_height = height;
	_isFullScreen = isFullScreen;

	const int MAX_LOADSTRING = 100;
	TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
	TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THXYY, szWindowClass, MAX_LOADSTRING);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_THXYY));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	// 执行应用程序初始化: 
	UINT windowStyle = WS_OVERLAPPEDWINDOW;
	windowStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);            //固定窗口大小
	_hwnd = CreateWindow(szWindowClass, szTitle, windowStyle,
		CW_USEDEFAULT, 0, _width, _height, NULL, NULL, hInstance, NULL);

	if (!_hwnd)
	{
		return -1;
	}

	ShowWindow(_hwnd, nCmdShow);
	UpdateWindow(_hwnd);

	RECT clientRect;
	GetClientRect(_hwnd, &clientRect);
	RECT windowRect;
	GetWindowRect(_hwnd, &windowRect);

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	
	MoveWindow(_hwnd, (screen_width - _width) / 2, (screen_height - _height) / 2, _width + windowRect.right - windowRect.left - clientRect.right - clientRect.left,
		_height + windowRect.bottom - windowRect.top - clientRect.bottom - clientRect.top, TRUE);

	if (InitEngine() < 0){
		return -1;
	}

	return 0;
}

int THXYY::InitEngine()
{
	_engine = new THEngine(_width, _height, _isFullScreen);
	engine = _engine;
	if (_engine->Init(_hInstance, _hwnd) < 0) {
		return -1;
	}
	return 0;
}

int THXYY::Run()
{
	// 主消息循环:
	MSG msg;
	HACCEL hAccelTable;

	hAccelTable = LoadAccelerators(_hInstance, MAKEINTRESOURCE(IDC_THXYY));
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else{
			_engine->Update();
			_engine->Render();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK THXYY::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (engine->_GameState){
		case GAME_MAIN_MENU:
			if (wParam == VK_DOWN){
				PlaySE(engine->_soundOK);
				if (engine->_menuSelection < 9){
					engine->_menuSelection++;
				}
			}
			else if (wParam == VK_UP){
				PlaySE(engine->_soundOK);
				if (engine->_menuSelection > 0){
					engine->_menuSelection--;
				}
			}
			else if ((wParam == VK_RETURN) || (wParam == 'Z')){
				PlaySE(engine->_soundOK);
				switch (engine->_menuSelection){
				case TH_MENU_START:
					game.GameStart();
					break;
				case TH_MENU_QUIT:
					game.GameShutdown();
					break;
				}
			}
			break;
		case GAME_START:
			if (wParam == VK_ESCAPE){
				engine->_isPaused = false;
				game.BackToMainMenu();
			}
			else if (wParam == 'p' || wParam == 'P'){
				engine->_isPaused = !engine->_isPaused;
			}
			else if (wParam == 'Q' || wParam == 'q'){
				if (engine->_isPaused){
					engine->_isPaused = false;
					engine->Update();
					engine->Render();
					engine->_isPaused = true;
				}
			}
			break;
		default:
			break;
		}
		if (wParam == VK_HOME){
			engine->PrintScreen();
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void THXYY::GameStart()
{
	_engine->_GameState = GAME_START;
	_engine->_stageNumber = 1;
	_engine->LoadStage();
	_engine->_isPaused = false;
	_engine->_player = new Reimu;
	_engine->_score = 0;
	_engine->_highscore = 0;
}

void THXYY::GameShutdown()
{
	PostQuitMessage(0);
}

void THXYY::BackToMainMenu()
{
	engine->_GameState = GAME_MAIN_MENU;
	engine->_menuSelection = 0;
	engine->_enemylist->Clear();
	engine->_bulletlist->Clear();
	engine->_itemlist->Clear();
	engine->_renderlist->Clear();
	engine->_playerbulletlist->Clear();
	TH_SAFE_DELETE(engine->_player);
	TH_SAFE_DELETE(engine->_stage);

	/*while (!_engine->_eventlist.empty()){
		Event *e = m_engine->m_eventlist.top();
		if (e->nEventType == EVENT_CREATION)
			SAFE_DELETE(((EventCreation*)e)->m_obj)
			delete e;
		m_engine->m_eventlist.pop();
	}*/
}