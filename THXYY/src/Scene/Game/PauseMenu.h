#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "PauseMenuItem.h"

class PauseMenu : public Menu
{
private:
	Sprite* black = nullptr;
	PauseMenuItem* title = nullptr;

public:
	PauseMenu();
	virtual ~PauseMenu();

	virtual void OnKeyDown(EngineObject* sender, int key) override;

	void DoPause();
	void DoResume();
};

#endif