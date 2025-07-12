//======================================================
// 
// ���[�V�����̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

// �}�N����`
#define KEY_MAX (16)			// �L�[�̍ő吔
#define KEYINFO_MAX (32)		// �L�[�C���t�H�̍ő吔
#define MAX_CHARACTER (256)		// �����̍ő吔

//*****************************************************************************
// ���[�V�����N���X
//*****************************************************************************
class CMotion
{
public:
	// ���[�V�����̎��
	typedef enum
	{
		TYPE_NEUTRAL = 0,	// �ҋ@
		TYPE_WALK,			// ����
		TYPE_ATTACK,		// �U��
		TYPE_JUMP,			// �W�����v
		TYPE_LANDING,		// ���n
		TYPE_MAX
	}TYPE;

	// �L�[�̍\����
	typedef struct
	{
		float fPosX;	// �ʒuX
		float fPosY;	// �ʒuY
		float fPosZ;	// �ʒuZ
		float fRotX;	// ����X
		float fRotY;	// ����Y
		float fRotZ;	// ����Z
	}KEY;

	// �L�[���̍\����
	typedef struct
	{
		int nFrame;			// �Đ��t���[��
		KEY aKey[KEY_MAX];	// �e�p�[�c�̃L�[�v�f
	}KEY_INFO;

	// �L�[���[�V�������\����
	typedef struct
	{
		bool bLoop;				        // ���[�v���邩�ǂ���
		int nNumKey;			        // �L�[�̑���
		KEY_INFO aKeyInfo[KEYINFO_MAX];	// ���f���̃L�[���
	}INFO;

	// �R���X�g���N�^
	CMotion();
	// �f�X�g���N�^
	~CMotion();

	// �����o�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Load(const char* Motionfile);
	void KeysetLoad(int nType, int nCntKey, int nCntParts);
	TYPE GetType(void) { return m_NowType; };
	bool IsFinish(void);
	//void SetMotionInfo(INFO m_MotionInfo);
	void SetType(TYPE Type);
	void SetModel(CModel** apModel,int nNumParts);

private:
	// �����o�ϐ�
	INFO m_MotionInfo[TYPE_MAX];	// ���[�V�������
	TYPE m_NowType;					// ���݂̃��[�V�����^�C�v
	int m_nNumKey;					// �L�[�̑���
	int m_nNumParts;				// �p�[�c�̑���
	bool m_bLoop;					// ���[�v���邩�ǂ���
	int m_nKey;						// ���݂̃L�[No.
	int m_nNextKey;					// ���̃L�[No.
	int m_nCounterMotion;			// ���[�V�����J�E���^�[
	bool m_bMotionEnd;				// ���[�V�������I����Ă��邩
	CModel** m_ppModel;				// ���f���ւ̃_�u���|�C���^

	FILE* m_pfile;					// �ǂݍ��ރt�@�C��
	char m_aString[MAX_CHARACTER];

};

#endif