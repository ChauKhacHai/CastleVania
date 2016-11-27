#ifndef INPUT_H_
#define INPUT_H_
#include <dinput.h>
#include "CWindown.h"
#define KEY_DOWN(code) ( IsKeyDown(code) )

#define KEYBOARD_BUFFER_SIZE	1024
class CInput {
private:
	LPDIRECTINPUT8       m_di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 m_Keyboard;	// The keyboard device 
	BYTE  m_KeyStates[256];	
	BYTE m_PreviousKeyStates[256]; 
	// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
	int  m_keydown, m_keyup;//onkeydow or onkeyup
public:
	CInput();
	~CInput();
	int InitKeyboard(HINSTANCE, HWND);
	void ProcessKeyBoard();
	int IsKeyDown(int KeyCode);
	int IsKeyPress(int KeyCode);
	int KeyUp(int KeyCode);
	int GetKeyDown();
	int GetKeyUp();
	 //int OnKeyDown(int KeyCode);
	bool OnKeyUp(int KeyCode);
	void Kill_Keyboard();
};

#endif


