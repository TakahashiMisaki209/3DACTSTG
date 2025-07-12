//======================================================
// 
// �J�����̏���
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//******************************************************
// �J�����N���X
//******************************************************
class CCamera
{
public:
	// �R���X�g���N�^
	CCamera();
	// �f�X�g���N�^
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetPosCamera(D3DXVECTOR3 pos);
	void SetMoveCamera(D3DXVECTOR3 move);
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	bool GetFollow(void) { return m_bFollow; };

private:
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_posVDest;		// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;		// �ړI�̒����_
	D3DXVECTOR3 m_rotDest;		// �ړI�̌���
	float m_fDistance;			// ���_���璍���_�̋���
	bool m_bFollow;				// �����Ǐ]�Ǝ蓮����؂�ւ�
	bool m_bCameraV;			// ���_�ƒ����_�̑���̐؂�ւ�
};

#endif