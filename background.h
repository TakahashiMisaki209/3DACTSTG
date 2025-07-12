//======================================================
// 
// �w�i����
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "object2D.h"

// �}�N����`
#define MAX_BG (3)

//*****************************************************************************
// �w�i�N���X
//*****************************************************************************
class CBG2D :public CObject2D
{
public:
	// �R���X�g���N�^
	CBG2D(int nPriority = 1);
	// �f�X�g���N�^
	~CBG2D();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�ϐ�
	static CBG2D* Create(void);

private:
	// �����o�ϐ�
	Texture* m_pBGTex;
	int m_nID;
};

#endif _BACKGROUND_H_