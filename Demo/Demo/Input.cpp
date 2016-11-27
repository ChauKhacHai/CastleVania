#include"Input.h"
CInput::CInput()
{
}

int CInput::InitKeyboard(HINSTANCE _hInstance, HWND _wndhandle){

	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_di, NULL);
	if (hr != DI_OK) return 0;
	hr = m_di->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL);
	if (hr != DI_OK) return 0;
	hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK) return 0;
	hr = m_Keyboard->SetCooperativeLevel(_wndhandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hr != DI_OK) return 0;

	//DirectInput  cung cấp 2 kiểu data , Buffered and Immediate Data
	//Buffered dùng cho khi sử dụng buttons
	//Immediate sử dụng ngay lập tức.
	//ở đây dùng buffered
	/*
	To retrieve buffered data from the keyboard, you must first set the buffer size (see Device Properties). 
	This step is essential because the default size of the buffer is 0.
	You must also declare an array of DIDEVICEOBJECTDATA structures. This array can have up to the same number of elements as the buffer size.
	You do not have to retrieve the entire contents of the buffer with a single call.
	You can have just one element in the array and retrieve events one at a time until the buffer is empty.

	Each element in the DIDEVICEOBJECTDATA array represents a change in state for a single key-that is, a press or release.
	*/
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = m_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return 0;

	hr = m_Keyboard->Acquire();
	if (hr != DI_OK) return 0;
	return 1;
}
void CInput::ProcessKeyBoard(){
	m_Keyboard->Poll();
	if (!SUCCEEDED(m_Keyboard->GetDeviceState(sizeof(m_KeyStates), m_KeyStates)));
	{
		//keyboard device lost, try to re-acquire
		m_Keyboard->Acquire();
	}

	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = m_Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);
	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			//OnKeyDown(KeyCode);
			m_keydown = KeyCode;
		else
			//OnKeyUp(KeyCode);
			m_keyup = KeyCode;
	}
}
int CInput::IsKeyDown(int KeyCode){
	return (m_KeyStates[KeyCode] & 0x80) > 0;
}
int CInput::IsKeyPress(int KeyCode){
	if ((m_KeyStates[KeyCode] & 0x00000080) && !(m_PreviousKeyStates[KeyCode] & 0x00000080))
	{
		return true;
	}
	return false;
}
int CInput::GetKeyDown()
{
	int	tam = m_keydown;
	m_keydown = 0;
	return tam;
}
int CInput::GetKeyUp()
{
	int	tam = m_keyup;
	m_keydown = 0;
	return tam;
}
//int OnKeyDown(int KeyCode){
//
//}
bool CInput::OnKeyUp(int KeyCode){
	return((m_KeyStates[KeyCode] & 0x80) != 0 ? false : true);
}
CInput::~CInput()
{
}
void CInput::Kill_Keyboard(){
	if (m_Keyboard != NULL)
	{
		m_di->Release();
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = NULL;
	}
}
