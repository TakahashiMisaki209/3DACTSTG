//======================================================
// 
// �e�L�X�g�t�@�C���̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _TXTFILE_H_
#define _TXTFILE_H_

#include "main.h"

// �}�N����`
#define MAX_CHARACTER (256)

//*****************************************************************************
// �e�L�X�g�t�@�C���N���X
//*****************************************************************************
class CTxtfile
{
public:
	// �R���X�g���N�^
	CTxtfile();
	// �f�X�g���N�^
	~CTxtfile();

	// �����o�֐�
	void Load(void);
	void Save(void);

private:
	// �����o�ϐ�
	FILE* m_pfile;
	char m_aString[MAX_CHARACTER];

	// �ÓI�����o�ϐ�

};

#endif
