//======================================================
// 
// �f�o�b�N�\������
// Author:Takahashi Misaki
// 
//======================================================

#include "debugproc.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
LPD3DXFONT CDebugproc::m_pFont = NULL;
char CDebugproc::m_aStr[1024] = {};
int CDebugproc::m_nIdx = 0;

//********************************************
// �R���X�g���N�^
//********************************************
CDebugproc::CDebugproc()
{
	m_pFont = NULL;

	for (int nCount = 0; nCount < 1024; nCount++)
	{
		m_aStr[nCount] = NULL;
	}
}

//********************************************
// �f�X�g���N�^
//********************************************
CDebugproc::~CDebugproc()
{
}

//********************************************
// ����������
//********************************************
void CDebugproc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice,			// �f�o�C�X
		18,							// �t�H���g�̍���
		0,							// �t�H���g�̉���
		0,							// �t�H���g�̑���
		0,							// ����
		FALSE,						// �Α�
		SHIFTJIS_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x
		DEFAULT_QUALITY,			// �����i��
		DEFAULT_PITCH | FF_SWISS,	// �s�b�`�ƃt�@�~��
		"Terminal",					// �t�H���g��
		&m_pFont);					// Font�|�C���^

}

//********************************************
// �I������
//********************************************
void CDebugproc::Uninit(void)
{
	m_pFont = NULL;

	for (int nCount = 0; nCount < 1024; nCount++)
	{
		m_aStr[nCount] = NULL;
	}

}

//********************************************
// �v�����g����
//********************************************
void CDebugproc::Print(const char* fmt, ...)
{
	// �������i�[���郊�X�g
	va_list arg;

	// fmt�����̑S�Ă̈��������X�g�Ɋi�[����
	va_start(arg, fmt);

	// ���݂̃o�b�t�@�̐擪�ɕۊ�
	m_nIdx += vsnprintf(&m_aStr[m_nIdx], *fmt, fmt, arg);

	// ���X�g�̒��g���N���A����
	va_end(arg);
}

//********************************************
// �`�揈��
//********************************************
void CDebugproc::Draw(void)
{
	// �t�H���g�̍��W
	RECT rc = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �t�H���g�̕`��
	m_pFont->DrawText(NULL,					// NULL
		&m_aStr[0],							// �`�悷��e�L�X�g
		-1,									// �e�L�X�g�̒���
		&rc,								// �\���͈�
		DT_LEFT,							// �����
		D3DCOLOR_ARGB(255, 255, 0, 0));	// �F

	for (int nCount = 0; nCount < 1024; nCount++)
	{
		m_aStr[nCount] = NULL;
	}

	// �C���f�b�N�X�̃N���A
	m_nIdx = 0;

}