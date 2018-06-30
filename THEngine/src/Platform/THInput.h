#ifndef THINPUT_H
#define THINPUT_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION   0x0800
#endif

#include <dinput.h>
#include <Common\THCommon.h>

#define DIKEYDOWN(data,id) (data[id] & 0x80)

namespace THEngine
{
	class Application;
	struct Vector2f;

	class Input : public Object, public Singleton<Input>
	{
		friend class Singleton<Input>;

	private:
		IDirectInput8 * input = nullptr;
		IDirectInputDevice8* keyboard;

		BYTE keystate[256];

	private:
		Input() = default;
		int GetKeyboardState();

	public:
		virtual ~Input();

		bool Init();

		//ˢ�¼��̡������豸��״̬
		void Update();

		bool KeyDown(int key);

		bool SetMousePosition(const Vector2f& pos);
		bool GetMousePosition(Vector2f* out);

		bool HasFocus() const;
	};
}

#endif