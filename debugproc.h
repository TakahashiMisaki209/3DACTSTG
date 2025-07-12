//======================================================
// 
// �f�o�b�N�\������
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

//*****************************************************************************
// �f�o�b�N�\���N���X
//*****************************************************************************
class CDebugproc
{
public:
	// �R���X�g���N�^
	CDebugproc();
	// �f�X�g���N�^
	~CDebugproc();

	// �����o�֐�
	void Init(void);
	void Uninit(void);
	
	// �ÓI�����o�֐�
	static void Print(const char* fmt, ...);
	static void Draw(void);

private:

	// �ÓI�����o�ϐ�
	static LPD3DXFONT m_pFont;	// �t�H���g�ւ̃|�C���^
	static char m_aStr[1024];	// ��������i�[����o�b�t�@
	static int m_nIdx;			// ���݂̃o�b�t�@�̈ʒu

};

#endif _DEBUGPROC_H_