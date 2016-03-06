#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "THCommon.h"
#include "THPlayer.h"
#include "THItem.h"
#include "THStage.h"
#include "THBullet.h"
#include "THSprite.h"
#include "RenderList.h"

/*************游戏状态*******************/
#define GAME_MAIN_MENU               1
#define GAME_START                   2

#define TH_MAX_TEXTURE               1000
#define TH_MAX_SOUND                 200

/************菜单项*********************/
#define TH_MENU_START                   0
#define TH_MENU_EXTRA_START             1
#define TH_MENU_PRACTICE_START          2
#define TH_MENU_SPELL_PRACTICE          3
#define TH_MENU_REPLAY                  4
#define TH_MENU_PLAYER_DATA             5
#define TH_MENU_MUSIC_ROOM              6
#define TH_MENU_OPTION                  7
#define TH_MENU_MANUAL                  8
#define TH_MENU_QUIT                    9

/*************菜单文字*******************/
const TCHAR szMenu[10][15] = {
	TEXT("Game Start"),
	TEXT("Extra Start"),
	TEXT("Practice Start"),
	TEXT("Spell Practice"),
	TEXT("Replay"),
	TEXT("Player Data"),
	TEXT("Music Room"),
	TEXT("Option"),
	TEXT("Manual"),
	TEXT("Quit"),
};

class THEngine{
public:
	int _width;
	int _height;
	bool _isFullScreen;

	float _width_scale;
	float _height_scale;
	int _shoot_width;
	int _shoot_height;
	int _shoot_left;
	int _shoot_top;

	//Direct3D
	D3DPRESENT_PARAMETERS _d3dpp;
	IDirect3D9* _d3d;
	IDirect3DDevice9* _device;

	//Effects
	ID3DXEffect* _effectFilter;

	//Sprite
	THSprite* _sprite;

	//DirectInput
	IDirectInput8* _input;
	IDirectInputDevice8* _keyboard;
	BYTE _keystate[256];

	//DirectSound
	IDirectSound* _sound;
	IDirectSoundBuffer* _soundBuffer[TH_MAX_SOUND];
	int _soundBiu;
	int _soundShoot1;
	int _soundOK;
	int _soundDamage;

	//Font
	ID3DXFont* _fontFPS;

	//Projection Matrices
	D3DXMATRIX _proj, _projShoot;
	D3DVIEWPORT9 _vp, _vpShoot;
	
	//Handles
	HINSTANCE _hInstance;
	HWND _hwnd;

	//FPS
	DWORD _FrameCount;
	int _TimeElapsed;
	int _lasttime;
	int _curtime;
	float _FPS;

	int _GameState;

	bool _isPaused;

	//Stage
	int _stageNumber;
	THStage* _stage;

	//Render objects and lists 
	THPlayer* _player;
	RenderList<THEnemy>* _enemylist;
	RenderList<THBullet>* _bulletlist;
	RenderList<THPlayerBullet>* _playerbulletlist;
	RenderList<THItem>* _itemlist;
	RenderList<RenderObject> *_renderlist;
	//priority_queue<Event *, vector<Event *>, cmp> m_eventlist;*/

	//Textures
	IDirect3DTexture9* _texList[TH_MAX_TEXTURE];
	int _texTitle;
	int _texPlayer;
	int _texBullet;
	int _texBullet2;
	int _texEnemy;
	int _texItem;
	int _texFront;
	int _texGameBgr;
	int _texEffect1;

	//Menu
	int _menuSelection;

	//Score
	int _score;
	int _highscore;

public:
	THEngine(int width, int height, bool isFullScreen);
	virtual ~THEngine();
	
	int Init(HINSTANCE hInstance, HWND hwnd);
	int InitEffects();
	int InitFont();
	int InitDirectInput();
	int InitDirectSound();

	int LoadEffect(TCHAR* srcPath, ID3DXEffect** effect);

	HRESULT DIGetKeyboardState();

	void Biu();
	void GetInput();

	void CalcFPS();
	void DrawFPS();

	void DrawMenu();
	void DrawFront();

	void OnLostDevice();
	void OnResetDevice();

	int LoadContent();
	int LoadTexture();
	int LoadSound();

	void UploadContent();

	void LoadStage();

	void PrintScreen();

	void Update();
	void Render();

	void Shutdown();

	friend class THXYY;
};

#endif