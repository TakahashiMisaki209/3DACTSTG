//======================================================
// 
// ���͏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

// �}�N����`
#define MAX_NUM_KEY (256)

//*****************************************************************************
// �C���v�b�g�N���X
//*****************************************************************************
class CInput
{
public:
	// �R���X�g���N�^
	CInput();
	// �f�X�g���N�^
	virtual ~CInput();

	// �����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	// �ÓI�����o�ϐ�
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

};

//*****************************************************************************
// �L�[�{�[�h�N���X
//*****************************************************************************
class CInputKeyboard:public CInput
{
public:
	// �R���X�g���N�^
	CInputKeyboard();
	// �f�X�g���N�^
	~CInputKeyboard();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[MAX_NUM_KEY];
	BYTE m_aOldState[MAX_NUM_KEY];

};

//*****************************************************************************
// �}�E�X�N���X
//*****************************************************************************
class CInputMouse :public CInput
{
public:

	// �}�E�X�̃{�^���̎��
	typedef enum
	{
		MOUSE_LEFT = 0,
		MOUSU_RIGHT,
		MOUSU_MAX
	}MOUSU;

	// �R���X�g���N�^
	CInputMouse();
	// �f�X�g���N�^
	~CInputMouse();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(MOUSU mousubutten) { return (m_mouse.rgbButtons[mousubutten] & 0x80) ? true : false; };
	bool GetTrigger(MOUSU mousubutten){ return (m_Trigger.rgbButtons[mousubutten] & 0x80) ? true : false; };
	bool GetRelease(MOUSU mousubutten){ return (m_Release.rgbButtons[mousubutten] & 0x80) ? true : false; };
	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3((float)m_mouse.lX, (float)m_mouse.lY, (float)m_mouse.lZ); };
	D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3((float)m_move.lX, (float)m_move.lY, (float)m_move.lZ); };

private:
	DIMOUSESTATE m_mouse;		// �}�E�X�̏��
	DIMOUSESTATE m_move;		// �}�E�X�̈ړ��ʏ��
	DIMOUSESTATE m_mouseOld;	// �Â��}�E�X�̏��
	DIMOUSESTATE m_Trigger;		// �}�E�X�g���K�[�̏��
	DIMOUSESTATE m_Release;		// �}�E�X�����[�X�̏��
	bool m_bCursor;				// �J�[�\�����g�p���邩�ǂ���
	HWND m_hWnd;
};

////*****************************************************************************
//// �W���C�p�b�h�N���X
////*****************************************************************************
//class CInputJoypad :public CInput
//{
//public:
//
//	// �{�^���̎��
//	typedef enum
//	{
//		JOYKEY_UP = 0,			// �\���L�[��
//		JOYKEY_DOWN,			// �\���L�[��
//		JOYKEY_LEFT,			// �\���L�[��
//		JOYKEY_RIGHT,			// �\���L�[�E
//		JOYKEY_START,			// �X�^�[�g�{�^��
//		JOYKEY_BACK,			// �o�b�N�{�^��
//		JOYKEY_LSTICK_BUTTON,	// L�X�e�B�b�N�{�^��
//		JOYKEY_RSTICK_BUTTON,	// R�X�e�B�b�N�{�^��
//		JOYKEY_L1,				// L1�{�^��
//		JOYKEY_R1,				// R1�{�^��
//		JOYKEY_L2,				// L2�g���K�[
//		JOYKEY_R2,				// R2�g���K�[
//		JOYKEY_A,				// A�{�^��
//		JOYKEY_B,				// B�{�^��
//		JOYKEY_X,				// X�{�^��
//		JOYKEY_Y,				// Y�{�^��
//		JOYKEY_MAX
//	}JOYKEY;
//
//	// �R���X�g���N�^
//	CInputJoypad();
//	// �f�X�g���N�^
//	~CInputJoypad();
//
//	// �����o�֐�
//	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
//	void Uninit(void);
//	void Update(void);
//	bool GetPress(int nKey);
//	bool GetTrigger(int nKey);
//	bool GetRelease(int nKey);
//	bool GetRepeat(int nKey);
//
//private:
//	BYTE m_aKeyState[MAX_NUM_KEY];
//	BYTE m_aOldState[MAX_NUM_KEY];
//
//};

#endif 