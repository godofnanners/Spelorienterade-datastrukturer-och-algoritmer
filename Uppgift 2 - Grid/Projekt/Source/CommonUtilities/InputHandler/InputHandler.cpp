#include "InputHandler.h"
#include <WinUser.h>
namespace CommonUtilities
{
	InputHandler& InputHandler::Instance()
	{
		static InputHandler input;

		return input;
	}
	bool InputHandler::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			//Keyboard Input
		case(WM_KEYDOWN):
		{
			myKeyboardInputs.HandlePressedKeyBoardInput(wParam, lParam);
			break;
		}
		case (WM_KEYUP):
		{
			myKeyboardInputs.HandleReleasedKeyBoardInput(wParam, lParam);
			break;
		}
		//Mouse Input
		case (WM_MOUSEMOVE):
		{
			myMouseInput.HandleMouseMovement(lParam);
			break;
		}
		case (WM_MOUSEWHEEL):
		{
			myMouseInput.HandleMouseScroll(wParam);
			break;
		}

		case (WM_LBUTTONDOWN):
		case (WM_RBUTTONDOWN):
		case (WM_MBUTTONDOWN):
		case(WM_XBUTTONDOWN):
		{
			myMouseInput.HandleMouseButtonInput(wParam, lParam);
			break;
		}

		case (WM_LBUTTONUP):
		case (WM_RBUTTONUP):
		case (WM_MBUTTONUP):
		case(WM_XBUTTONUP):
		{
			myMouseInput.HandleReleasedMouseButtonInput(wParam, lParam);
			break;
		}

		/*if window comes out of focus release all buttons/keys*/
		case(WM_SETFOCUS):
		{
			ResetEvents();
		}

		default:
			break;
		}
		return false;
	}


	void InputHandler::ResetEvents()
	{
		myKeyboardInputs.ResetReleaseKeyBoardKeys();
		myMouseInput.ResetReleaseMouseInput();
	}


	bool InputHandler::CheckIfKeyIsPressed(int aKeyCode) const
	{
		return myKeyboardInputs.CheckIfKeyIsPressed(aKeyCode);
	}

	bool InputHandler::CheckIfKeyIsHeld(int aKeyCode) const
	{
		return myKeyboardInputs.CheckIfKeyIsHeld(aKeyCode);
	}

	bool InputHandler::CheckIfKeyJustWasReleased(int aKeyCode) const
	{
		return myKeyboardInputs.CheckIfKeyJustWasReleased(aKeyCode);
	}

	const std::array<float, 2> & InputHandler::CheckMouseMovement() const
	{
		return myMouseInput.GetMouseMovement();
	}

	int InputHandler::CheckScrollWheelDelta() const
	{
		return myMouseInput.GetMouseWheelDeltaScroll();
	}

	bool InputHandler::CheckIfMouseButtonIsPressed(int aMouseButton) const
	{
		return myMouseInput.GetIsMouseButtonPressed(aMouseButton);
	}

	bool InputHandler::CheckIfMouseButtonWasJustReleased(int aMouseButton) const
	{
		return myMouseInput.GetIsMouseButtonReleased(aMouseButton);
	}

	bool InputHandler::CheckIfMouseButtonIsHeldDown(int aMouseButton) const
	{
		return myMouseInput.GetIsMouseButtonHeld(aMouseButton);
	}

	std::array<float, 2> InputHandler::CheckMousePos() const
	{
		return myMouseInput.GetMousePos();
	}

	std::array<float, 2> InputHandler::CheckMousePosInWindow(HWND& aWindow) const
	{
		return myMouseInput.GetMousePosInWindow(aWindow);
	}

	void InputHandler::SetMousePosition(int aX, int anY)
	{
		myMouseInput.HandleSetMousePosition(aX, anY);
	}
}
