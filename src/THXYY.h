#ifndef THXYY_H
#define THXYY_H

#include "THEngine/THEngine.h"

class THXYY{
protected:
	HINSTANCE _hInstance;

	int _width;
	int _height;
	bool _isFullScreen;
	THEngine* _engine;

	//Window
	HWND _hwnd;

protected:
	int InitEngine();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	THXYY();
	virtual ~THXYY();
	THEngine* GetEngine();
	int CreateGame(HINSTANCE hInstance, UINT nCmdShow, int width, int height, bool isFullScreen);
	int Run();

	void GameStart();
	void GameShutdown();

	void BackToMainMenu();
};

#endif