//======================================================
// 
// �v���C���[�̏���
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "model.h"
#include "motion.h"
#include "shadow.h"

//******************************************************
// �v���C���[�N���X
//******************************************************
class CPlayer:public CObject
{
public:

	// �R���X�g���N�^
	CPlayer(int nPriority = 3);

	// �f�X�g���N�^
	~CPlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXVECTOR3 GetMove(void) { return m_move; };

	// �ÓI�����o�֐�
	static CPlayer* Create(void);

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����
	D3DXVECTOR3 m_rotDest;			// �������������܂ł̍�
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	int m_nNumModel;				// ���f��(�p�[�c)�̑���
	bool m_bJump;					// �W�����v���Ă邩�ǂ���
	CShadow* m_pShadow;				// �e�ւ̃|�C���^
	CMotion* m_pMotion;				// ���[�V�����ւ̃|�C���^
	CModel* m_apModel[MAX_MODEL];	// ���f��(�p�[�c)�ւ̃|�C���^

};

#endif _PLAYER_H_