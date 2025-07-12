//======================================================
// 
// �I�u�W�F�N�g����
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

// �}�N����`
#define MAX_PRIO (8)	// �D�揇�ʂ̍ő吔

#include "main.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CObject
{
public:

	// �I�u�W�F�N�g�̎��	
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EFFECT,
		TYPE_TIMER,
		TYPE_MAX
	}TYPE;

	// �R���X�g���N�^(�I�[�o�[���[�h)
	CObject(int nPriority = 0);
	// �f�X�g���N�^
	virtual ~CObject();

	// �����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual D3DXVECTOR3 GetPos(void) { return m_Pos; }
	void SetTYPE(TYPE type);
	TYPE GetTYPE(void) { return m_type; }
	CObject* GetNext(void) { return m_pNext; }
	CObject* ObjectDeath(CObject* pObject);

	// �ÓI�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }
	static int GetNumAll(void) { return m_nNumAll; }

protected:
	void Release(void);

private:
	// �����o�ϐ�
	CObject* m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;	// ���̃I�u�W�F�N�g�̃|�C���^
	int m_nID;			// �������g��ID
	TYPE m_type;		// �I�u�W�F�N�g�̎��
	int m_nPriority;	// �D�揇�ʂ̈ʒu
	bool m_bDeath;		// ���S�t���O

	// �ÓI�����o�ϐ�
	static CObject* m_pTop[MAX_PRIO];		// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_pCur[MAX_PRIO];		// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;					// �I�u�W�F�N�g�̑���
	D3DXVECTOR3 m_Pos;						// �I�u�W�F�N�g�̈ʒu
};

#endif _OBJECT_H_