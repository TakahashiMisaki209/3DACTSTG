//======================================================
// 
// �v���C���[����
// Author:Takahashi Misaki
// 
//======================================================

#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "bullet.h"
#include "camera.h"
#include "object3D.h"

//********************************************
// �R���X�g���N�^
//********************************************
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_bJump = false;
	m_pMotion = NULL;
	m_pShadow = NULL;

	for (int nCount = 0; nCount < MAX_MODEL; nCount++)
	{
		m_apModel[nCount] = NULL;

		m_nNumModel++;
	}
}

//********************************************
// �f�X�g���N�^
//********************************************
CPlayer::~CPlayer()
{

}

//********************************************
// ����������
//********************************************
HRESULT CPlayer::Init(void)
{
	// �J�����̃|�C���^
	CCamera* pCamera;

	// �J�����̎擾
	pCamera = CManager::GetCamera();

	// ���[�V�����̐���
	m_pMotion = new CMotion;

	// ���[�V�����̏���������
	m_pMotion->Init();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_rot = D3DXVECTOR3(0.0f, pCamera->GetRot().y - D3DX_PI * 0.5f, 0.0f);
	m_rotDest.y = pCamera->GetRot().y - D3DX_PI * 0.5f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���f���̐���(�S�p�[�c��)
	m_apModel[0] = CModel::Create("data\\MODEL\\Player\\00_body.x");	// ��
	m_apModel[1] = CModel::Create("data\\MODEL\\Player\\01_head.x");	// ��
	m_apModel[2] = CModel::Create("data\\MODEL\\Player\\04_armL.x");	// ���r
	m_apModel[3] = CModel::Create("data\\MODEL\\Player\\05_handL.x");	// ����
	m_apModel[4] = CModel::Create("data\\MODEL\\Player\\02_armR.x");	// �E�r
	m_apModel[5] = CModel::Create("data\\MODEL\\Player\\03_handR.x");	// �E��
	m_apModel[6] = CModel::Create("data\\MODEL\\Player\\08_legL.x");	// ���r
	m_apModel[7] = CModel::Create("data\\MODEL\\Player\\09_footL.x");	// ����
	m_apModel[8] = CModel::Create("data\\MODEL\\Player\\06_legR.x");	// �E�r
	m_apModel[9] = CModel::Create("data\\MODEL\\Player\\07_footR.x");	// �E��

	// �e���f���̐ݒ�(�S�p�[�c��)
	m_apModel[0]->SetParent(NULL, D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// ��
	m_apModel[1]->SetParent(m_apModel[0], D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ��
	m_apModel[2]->SetParent(m_apModel[0], D3DXVECTOR3(-7.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���r
	m_apModel[3]->SetParent(m_apModel[2], D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
	m_apModel[4]->SetParent(m_apModel[0], D3DXVECTOR3(7.0f, 12.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �E�r
	m_apModel[5]->SetParent(m_apModel[4], D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �E��
	m_apModel[6]->SetParent(m_apModel[0], D3DXVECTOR3(-4.0f, -0.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ���r
	m_apModel[7]->SetParent(m_apModel[6], D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
	m_apModel[8]->SetParent(m_apModel[0], D3DXVECTOR3(4.0f, -0.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �E�r
	m_apModel[9]->SetParent(m_apModel[8], D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �E��

	// ���[�V�����̐ݒ菈��
	m_pMotion->SetModel(m_apModel, m_nNumModel);

	// �v���C���[�̃��[�V�����^�C�v��ݒ�
	m_pMotion->SetType(CMotion::TYPE_NEUTRAL);

	// �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
	pCamera->SetPosCamera(m_pos);

	// �e�̐���
	m_pShadow = CShadow::Create(m_pos.x, m_pos.z, m_rot, 50.0f, 50.0f);

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CPlayer::Uninit(void)
{
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{// NULL�`�F�b�N
			// ���f���̏I������
			m_apModel[nCount]->Uninit();
			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{// NULL�`�F�b�N
		// ���f���̏I������
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}

//********************************************
// �X�V����
//********************************************
void CPlayer::Update(void)
{
	// �f�o�C�X�̃|�C���^
	CInputKeyboard* pInputKeyboard;
	//// �T�E���h�̃|�C���g
	//CSound* pSound;
	// �J�����̃|�C���^
	CCamera* pCamera;
	// ���b�V���t�B�[���h�̃|�C���^
	CMeshfield* pMeshfield;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();
	//// �T�E���h�̎擾
	//pSound = CManager::GetSound();
	// �J�����̎擾
	pCamera = CManager::GetCamera();
	// ���b�V���t�B�[���h�̎擾
	pMeshfield = CManager::GetMeshfield();

	// �d��
	float fGravity = 1.0f;

	// �������������ւ̍�
	float fDiff = 0.0f;

	//=============================================
	// �v���C���[�̈ړ�����
	//=============================================

	if (pInputKeyboard->GetPress(DIK_W) == true)
	{// ���ړ�
		
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{// �����ړ�
			m_rotDest.y = -pCamera->GetRot().y + D3DX_PI * 0.25f;

			m_move.x -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
			m_move.z -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{// �E���ړ�
			m_rotDest.y = -pCamera->GetRot().y + D3DX_PI * 0.75f;

			m_move.x -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
			m_move.z -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
		}
		else
		{// ���ړ�
			m_rotDest.y = -pCamera->GetRot().y + D3DX_PI * 0.5f;

			m_move.x -= cosf(pCamera->GetRot().y) * 1.5f;
			m_move.z -= sinf(pCamera->GetRot().y) * 1.5f;
		}

		if (m_bJump == false)
		{// �W�����v���Ă��Ȃ��ꍇ�̂�
			// ���郂�[�V�����ɐݒ�
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{// ��O�ړ�

		if (pInputKeyboard->GetPress(DIK_A) == true)
		{// ����O�ړ�
			m_rotDest.y = -pCamera->GetRot().y - D3DX_PI * 0.25f;

			m_move.x += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
			m_move.z += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * 1.5f;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{// �E��O�ړ�
			m_rotDest.y = -pCamera->GetRot().y - D3DX_PI * 0.75f;

			m_move.x += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
			m_move.z += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 1.5f;
		}
		else
		{// ��O�ړ�
			m_rotDest.y = -pCamera->GetRot().y - D3DX_PI * 0.5f;

			m_move.x += cosf(pCamera->GetRot().y) * 1.5f;
			m_move.z += sinf(pCamera->GetRot().y) * 1.5f;
		}

		if (m_bJump == false)
		{// �W�����v���Ă��Ȃ��ꍇ�̂�
			// ���郂�[�V�����ɐݒ�
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{// ���ړ�
		m_rotDest.y = -pCamera->GetRot().y;

		m_move.x += sinf(pCamera->GetRot().y) * 1.5f;
		m_move.z -= cosf(pCamera->GetRot().y) * 1.5f;

		if (m_bJump == false)
		{// �W�����v���Ă��Ȃ��ꍇ�̂�
			// ���郂�[�V�����ɐݒ�
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{// �E�ړ�
		m_rotDest.y = -pCamera->GetRot().y - D3DX_PI;

		m_move.x -= sinf(pCamera->GetRot().y) * 1.5f;
		m_move.z += cosf(pCamera->GetRot().y) * 1.5f;

		if (m_bJump == false)
		{// �W�����v���Ă��Ȃ��ꍇ�̂�
			// ���郂�[�V�����ɐݒ�
			m_pMotion->SetType(CMotion::TYPE_WALK);
		}
	}
	else
	{
		if (m_bJump == false && m_pMotion->GetType() == CMotion::TYPE_WALK)
		{// ���郂�[�V�����̏ꍇ
			// �ҋ@���[�V�����ɐݒ�
			m_pMotion->SetType(CMotion::TYPE_NEUTRAL);
		}
	}

	//=============================================
	// �v���C���[�̃W�����v����
	//=============================================
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{
		// �W�����v���Ă����Ԃɂ���
		m_bJump = true;

		m_move.y = 20.0f;

		// �W�����v���[�V�����ɐݒ�
		m_pMotion->SetType(CMotion::TYPE_JUMP);
	}

	// �������������ւ̍������߂�
	fDiff = m_rotDest.y - m_rot.y;

	if (fDiff < -D3DX_PI)
	{// ����-3.14�𒴂����Ƃ�
		fDiff += D3DX_PI * 2.0f;
	}
	else if (fDiff > D3DX_PI)
	{// ����3.14�𒴂����Ƃ�
		fDiff -= D3DX_PI * 2.0f;
	}

	// �p�x���X�V
	m_rot.y += fDiff * 0.25f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	if (m_bJump == true)
	{// �W�����v���Ă���ꍇ
		// �d�͂����Z
		m_move.y -= fGravity;
	}

	// �ړ��̊���
	m_move.x = m_move.x * 0.85f;
	m_move.z = m_move.z * 0.85f;

	// �ړ��ʂ����Z
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// �n�ʂ͈̔͊O�ɏo����ړ��ʂ��O�ɂ���
	if (m_pos.x < pMeshfield->GetPos().x)
	{// ���[�ɂ����Ƃ�
		m_pos.x = pMeshfield->GetPos().x;

		m_move.x = 0.0f;
	}
	else if (m_pos.x > pMeshfield->GetPos().x + pMeshfield->GetSizeX())
	{// �E�[�ɂ����Ƃ�
		m_pos.x = pMeshfield->GetPos().x + pMeshfield->GetSizeX() ;

		m_move.x = 0.0f;
	}

	if (m_pos.z > pMeshfield->GetPos().z)
	{// ���ɂ����Ƃ�
		m_pos.z = pMeshfield->GetPos().z;

		m_move.z = 0.0f;
	}
	else if (m_pos.z < pMeshfield->GetPos().z - pMeshfield->GetSizeZ())
	{// ��O�ɂ����Ƃ�
		m_pos.z = pMeshfield->GetPos().z - pMeshfield->GetSizeZ();

		m_move.z = 0.0f;
	}

	if (m_pos.y <= pMeshfield->GetPos().y)
	{// �v���C���[�̈ʒu���n�ʂ𒴂��鎞
		if (m_bJump == true)
		{// ���[�V�����؂�ւ�
			// ���n���[�V�����ɐݒ�
 			m_pMotion->SetType(CMotion::TYPE_LANDING);
		}

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;

		m_pos.y = pMeshfield->GetPos().y;
	}

	if (m_pMotion->IsFinish() == true && m_pMotion->GetType() == CMotion::TYPE_LANDING)
	{// ���n���[�V�������I�������
		// �ҋ@���[�V�����ɐݒ�
		m_pMotion->SetType(CMotion::TYPE_NEUTRAL);
	}

	if (pCamera->GetFollow() == true)
	{// �J�����Ǐ]��ON�ɂȂ��Ă��鎞

		// �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
		pCamera->SetPosCamera(m_pos);
	}

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	// �e�̈ʒu�ݒ�
	m_pShadow->SetPos(m_pos.x, m_pos.z);
}

//********************************************
// �`�揈��
//********************************************
void CPlayer::Draw(void)
{
	// �f�o�b�N�\���̃|�C���^
	CDebugproc* pDebugproc;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]���Ă���ʒu�ړ��𔻒�I�I�I�I�I

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���X�V
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`�揈��

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Draw();
	}

	// �f�o�b�N�\��
	pDebugproc->Print("�v���C���[�̈ʒu X:%.1f, Y:%.1f, Z:%.1f\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugproc->Print("�v���C���[�̌��� X:%.1f, Y:%.1f, Z:%.1f\n", m_rot.x, m_rot.y, m_rot.z);
}

//********************************************
// ��������
//********************************************
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer;

	// �v���C���[�̐���
	pPlayer = new CPlayer;

	// ����������
	pPlayer->Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	pPlayer->SetTYPE(TYPE_PLAYER);

	return pPlayer;
}

