#ifndef THMENU_H
#define THMENU_H

#include "../Common/THCommon.h"
#include "../Core/THLayer.h"
#include "THEventSystem.h"
#include "THMenuItem.h"

namespace THEngine
{
	class Menu : public Layer, public IKeyDownListener
	{
	protected:
		ArrayList<MenuItem*> itemList;

		int currentSelection = -1;

		Sound* soundSelect = nullptr;

	public:
		Menu();
		Menu(int left, int top, int width, int height);
		virtual ~Menu();

		virtual bool OnKeyDown(EngineObject* sender, int key) override;

		virtual void OnActivate() override;
		virtual void OnDestroy() override;
		
		virtual void OnMenuItemClicked(int item);

		inline void Select(int index) { Select(index, true); }

		void Click(int index);

		void Select(int index, bool playSound);

		void SetSelection(int index);

		inline int GetItemCount() { return itemList.Size(); }
		inline MenuItem* GetMenuItem(int index) { return itemList.Get(index); }

		void AddMenuItem(MenuItem* menuItem);

		inline void ClearItems()
		{
			itemList.Clear();
			currentSelection = -1;
		}
	};
}

#endif