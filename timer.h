//======================================================
// 
// �^�C�}�[�̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _TIMER_H_
#define _TIMER_H_

#include "number.h"
#include "object.h"

// �ő�t���[��
#define MAX_FRAME (60)
// ��������
#define MAX_TIME (120)
// �ő包��
#define MAX_COLUMET (3)

//*****************************************************************************
// �^�C�}�[�N���X
//*****************************************************************************
class CTimer :public CObject
{
public:
	// �R���X�g���N�^
	CTimer(int nPriority = 7);
	// �f�X�g���N�^
	~CTimer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTimer* Create(void);

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;						// �ʒu
	int m_nCntTime;							// ����

	// �ÓI�����o�ϐ�
	static CNumber* m_apNumer[MAX_COLUMET];
};

#endif _TIMER_H_
