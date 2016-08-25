#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <THEngine.h>

namespace THEngine
{
	class TitleMenu : public Layer, IKeyDownListener
	{
	protected:
		int itemCount;
		int currentItem;
		Texture* texMenuItem;
		Rect spriteRect[10][3];

	protected:
		virtual void OnKeyDown(EngineObject* sender, int key) override;

	public:
		TitleMenu();
		virtual ~TitleMenu();

		virtual void Update() override;
		virtual void Draw() override;

		virtual void DrawMenuItem(int item);
		virtual void OnMenuItemSelected(int item);
		virtual void OnMenuItemChanged(int previousItem, int currentItem);
	};
}

#endif