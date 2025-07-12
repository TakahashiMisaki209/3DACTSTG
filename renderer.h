//======================================================
// 
// �����_�����O����
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "object.h"
#include "debugproc.h"

//*****************************************************************************
// �����_���[�N���X
//*****************************************************************************
class CRenderer
{
public:

	// �R���X�g���N�^
	CRenderer();
	// �f�X�g���N�^
	~CRenderer();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	// �����o�ϐ�
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	// �ÓI�����o�ϐ�
	static CDebugproc* m_pDebugproc;

};

#endif _RENDERER_H_