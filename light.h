//======================================================
// 
// ���C�g�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

// �}�N����`
#define MAX_LIGHT (3)

//******************************************************
// ���C�g�N���X
//******************************************************
class CLight
{
public:
	// �R���X�g���N�^
	CLight();
	// �f�X�g���N�^
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];

};

#endif