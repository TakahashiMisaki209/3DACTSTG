//======================================================
// 
// ���͏���
// Author:Takahashi Misaki
// 
//======================================================

#include "input.h"
#include "manager.h"

// �ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//********************************************
// �R���X�g���N�^
//********************************************
CInput::CInput()
{
	m_pInput = NULL;
	m_pDevice = NULL;
}

//********************************************
// �f�X�g���N�^
//********************************************
CInput::~CInput()
{

}

//********************************************
// ����������
//********************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// Directinput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

	}

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CInput::Uninit()
{
	// ���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// Directinput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================
// �L�[�{�[�h�̏���
//=============================================

//********************************************
// �R���X�g���N�^
//********************************************
CInputKeyboard::CInputKeyboard()
{
	for (int nCount = 0; nCount < MAX_NUM_KEY; nCount++)
	{
		m_aKeyState[nCount] = NULL;
		m_aOldState[nCount] = NULL;
	}
}

//********************************************
// �f�X�g���N�^
//********************************************
CInputKeyboard::~CInputKeyboard()
{

}

//********************************************
// ����������
//********************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏���������
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CInputKeyboard::Uninit()
{
	// ���͏����̏I������
	CInput::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_NUM_KEY];
	int nCntKey;

	for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// �L�[�{�[�h�̃A�N�Z�X�����l��
		m_pDevice->Acquire();
	}

}

//********************************************
// �L�[�v���X�����擾
//********************************************
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//********************************************
// �L�[�{�[�h�̃g���K�[�����擾
//********************************************
bool CInputKeyboard::GetTrigger(int nKey)
{
	bool Trigger = false;

	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;
}
//********************************************
// �L�[�{�[�h�̃����[�X�����擾
//********************************************
bool CInputKeyboard::GetRelease(int nKey)
{
	bool Trigger = false;

	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;

}
//********************************************
// �L�[�{�[�h�̃��s�[�g�����擾
//********************************************
bool CInputKeyboard::GetRepeat(int nKey)
{
	bool Trigger = false;

	if (m_aOldState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}

	return Trigger;
}

////=============================================
//// �W���C�p�b�h�̏���
////=============================================
//
////********************************************
//// �R���X�g���N�^
////********************************************
//CInputKeyboard::CInputKeyboard()
//{
//	for (int nCount = 0; nCount < MAX_NUM_KEY; nCount++)
//	{
//		m_aKeyState[nCount] = NULL;
//		m_aOldState[nCount] = NULL;
//	}
//}
//
////********************************************
//// �f�X�g���N�^
////********************************************
//CInputKeyboard::~CInputKeyboard()
//{
//
//}
//
////********************************************
//// ����������
////********************************************
//HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
//{
//	// ���͏����̏���������
//	CInput::Init(hInstance, hWnd);
//
//	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
//	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
//	{
//		return E_FAIL;
//	}
//
//	// �f�[�^�t�H�[�}�b�g��ݒ�
//	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
//	{
//		return E_FAIL;
//	}
//
//	// �������[�h��ݒ�
//	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
//		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
//	{
//		return E_FAIL;
//	}
//
//	// �W���C�p�b�h�̃A�N�Z�X�����l��
//	m_pDevice->Acquire();
//
//	return S_OK;
//}
//
////********************************************
//// �I������
////********************************************
//void CInputKeyboard::Uninit()
//{
//	// ���͏����̏I������
//	CInput::Uninit();
//}
//
////********************************************
//// �X�V����
////********************************************
//void CInputKeyboard::Update()
//{
//	BYTE aKeyState[MAX_NUM_KEY];
//	int nCntKey;
//
//	for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
//	{
//		m_aOldState[nCntKey] = m_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
//	}
//
//	// ���̓f�o�C�X����f�[�^���擾
//	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
//	{
//		for (nCntKey = 0; nCntKey < MAX_NUM_KEY; nCntKey++)
//		{
//			m_aKeyState[nCntKey] = aKeyState[nCntKey];
//		}
//	}
//	else
//	{
//		// �W���C�p�b�h�̃A�N�Z�X�����l��
//		m_pDevice->Acquire();
//	}
//
//}
//
////********************************************
//// �W���C�p�b�h�̃v���X�����擾
////********************************************
//bool CInputKeyboard::GetPress(int nKey)
//{
//	return (m_aKeyState[nKey] & 0x80) ? true : false;
//}
////********************************************
//// �W���C�p�b�h�̃g���K�[�����擾
////********************************************
//bool CInputKeyboard::GetTrigger(int nKey)
//{
//	bool Trigger = false;
//
//	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
//	{
//		Trigger = true;
//	}
//
//	return Trigger;
//}
////********************************************
//// �W���C�p�b�h�̃����[�X�����擾
////********************************************
//bool CInputKeyboard::GetRelease(int nKey)
//{
//	bool Trigger = false;
//
//	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
//	{
//		Trigger = true;
//	}
//
//	return Trigger;
//
//}
////********************************************
//// �W���C�p�b�h�̃��s�[�g�����擾
////********************************************
//bool CInputKeyboard::GetRepeat(int nKey)
//{
//	bool Trigger = false;
//
//	if (m_aOldState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
//	{
//		Trigger = true;
//	}
//
//	return Trigger;
//
//}

//=============================================
// �}�E�X�̏���
//=============================================

//********************************************
// �R���X�g���N�^
//********************************************
CInputMouse::CInputMouse()
{
	m_bCursor = true;		// �g�p���Ă����Ԃɂ���
}

//********************************************
// �f�X�g���N�^
//********************************************
CInputMouse::~CInputMouse()
{

}

//********************************************
// ����������
//********************************************
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏���������
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�i�}�E�X�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	m_hWnd = hWnd;

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CInputMouse::Uninit()
{
	// ���͏����̏I������
	CInput::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CInputMouse::Update()
{
	// �Â��}�E�X�̏����X�V
	m_mouseOld = m_mouse;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouse)))
	{// ���̓f�o�C�X����f�[�^���擾

		for (int nCntButn = 0; nCntButn < MOUSU_MAX; nCntButn++)
		{// �}�E�X�̃{�^������
			m_Trigger.rgbButtons[nCntButn] = m_mouse.rgbButtons[nCntButn] & ~m_mouseOld.rgbButtons[nCntButn];	// �g���K�[�̔���
			m_Release.rgbButtons[nCntButn] = m_mouseOld.rgbButtons[nCntButn] & ~m_mouse.rgbButtons[nCntButn];	// �����[�X�̔���
		}
	}
	else
	{
		m_pDevice->Acquire();	// �}�E�X�̃A�N�Z�X�����l��
	}

	// �J�[�\���̈ʒu����ۑ�����ϐ�
	POINT cp;	

	// �}�E�X���W���擾����
	GetCursorPos(&cp);

	if (m_bCursor == true)
	{// �g�p���Ă����ԂȂ�
		// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
		if (ScreenToClient(m_hWnd, &cp))
		{
			// �f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			// DirectX�̃T�C�Y���擾����
			float width = 0.0f;
			float height = 0.0f;
			IDirect3DSurface9* pBackBuffer = NULL;

			if (SUCCEEDED(pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer)))
			{
				// �o�b�N�o�b�t�@�̎擾
				D3DSURFACE_DESC desc;
				pBackBuffer->GetDesc(&desc);
				width = (float)desc.Width;
				height = (float)desc.Height;

				// �擾��������
				pBackBuffer->Release(); 
			}
			else
			{
				width = (float)SCREEN_WIDTH;
				height = (float)SCREEN_HEIGHT;
			}

			// �N���C�A���g�̈�̃T�C�Y���擾
			RECT clientRect;
			GetClientRect(m_hWnd, &clientRect);

			// �N���C�A���g���W��DirectX�̍��W�ɃX�P�[�����O
			float scaleX = width / (clientRect.right - clientRect.left);
			float scaleY = height / (clientRect.bottom - clientRect.top);

			int fixedX = static_cast<int>(cp.x * scaleX);
			int fixedY = static_cast<int>(cp.y * scaleY);

			// ���W��͈͓��ɌŒ�
			fixedX = max(0, min((int)width, fixedX));
			fixedY = max(0, min((int)height, fixedY));

			cp.x = fixedX;
			cp.y = fixedY;

			m_mouse.lX = cp.x;
			m_mouse.lY = cp.y;

		}

		// �ړ��ʂ��v�Z���đ��
		m_move.lX = m_mouse.lX - m_mouseOld.lX;
		m_move.lY = m_mouse.lY - m_mouseOld.lY;
	}
	else if (m_bCursor == false)
	{// �g�p���Ă��Ȃ���Ԃ̎�
		// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
		if (ScreenToClient(m_hWnd, &cp))
		{
			RECT csize = {};		// �E�B���h�E�̃T�C�Y�ۑ��p

			// �N���C�A���g�̃T�C�Y�擾
			GetClientRect(m_hWnd, &csize);

			// �J�[�\���̈ړ��ʂ��v�Z����
			m_move.lX = cp.x - (LONG)((float)csize.right * 0.5f);
			m_move.lY = cp.y - (LONG)((float)csize.bottom * 0.5f);

			// �J�[�\�����W����ʒ����ɐݒ�
			cp.x = (LONG)((float)csize.right * 0.5f);
			cp.y = (LONG)((float)csize.bottom * 0.5f);

			if (ClientToScreen(m_hWnd, &cp))
			{// �X�N���[�����W�ɖ߂�
				// �J�[�\���ʒu��ݒ�
				SetCursorPos(cp.x, cp.y);
			}
		}
	}
}
