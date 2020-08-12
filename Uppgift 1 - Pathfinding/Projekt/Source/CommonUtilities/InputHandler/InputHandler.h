#pragma once
#include <Windows.h>
#include "KeyBoardInputs.h"
#include "MouseInput.h"
#include <WinUser.h>
namespace CommonUtilities
{
#define InputInstance CommonUtilities::InputHandler::Instance()
	class InputHandler
	{
	public:
		static InputHandler& Instance();

		bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);
		void ResetEvents();
		const std::array<float, 2> & CheckMouseMovement() const;
		int CheckScrollWheelDelta() const;
		bool CheckIfKeyIsPressed(int aKeyCode) const;
		bool CheckIfKeyIsHeld(int aKeyCode) const;
		bool CheckIfKeyJustWasReleased(int aKeyCode) const;
		bool CheckIfMouseButtonIsPressed(int aKeyCode) const;
		bool CheckIfMouseButtonWasJustReleased(int aKeyCode) const;
		bool CheckIfMouseButtonIsHeldDown(int aKeyCode)const;
		std::array<float, 2> CheckMousePos() const;
		std::array<float, 2> CheckMousePosInWindow(HWND& aWindow) const;
		void SetMousePosition(int aX, int anY);
	private:
		KeyBoardInputs myKeyboardInputs;
		MouseInput myMouseInput;

	};
}
