//======================================================
// 
// �J�����̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "camera.h"
#include "input.h"
#include "manager.h"
#include "player.h"

//********************************************
// �R���X�g���N�^
//********************************************
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// ������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̒����_
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌���
	m_fDistance = 0.0f;								// ���_���璍���_�̋���
	m_bFollow = true;								// �J�������g�p���Ă��邩�ǂ���
	m_bCameraV = false;								// ���_�ƒ����_�̑���̐؂�ւ�
}

//********************************************
// �f�X�g���N�^
//********************************************
CCamera::~CCamera()
{

}

//********************************************
// ����������
//********************************************
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// �����(�Œ�)
	m_rot = D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI * 0.5f, 0.0f);		// ����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �ړ���
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړI�̒����_
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړI�̌���
	m_fDistance = 200.0f;											// ���_�ƒ����_�܂ł̋���
	m_bCameraV = true;												// ����ł���J����(���_)

	return S_OK;
}
//********************************************
// �I������
//********************************************
void CCamera::Uninit(void)
{

}
//********************************************
// �X�V����
//********************************************
void CCamera::Update(void)
{
	// �L�[�{�[�h�̃|�C���^
	CInputKeyboard* pInputKeyboard;
	// �}�E�X�̃|�C���^
	CInputMouse* pInputMouse;
	// �v���C���[�̃|�C���^
	CPlayer* pPlayer;
	// ���b�V���t�B�[���h�̃|�C���^
	CMeshfield* pMeshfield;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();
	// �}�E�X�̎擾
	pInputMouse = CManager::GetInputMouse();
	// �v���C���[�̎擾
	pPlayer = CManager::GetPlayer();
	// ���b�V���t�B�[���h�̎擾
	pMeshfield = CManager::GetMeshfield();

	// ���_�ړ��̑���
	float fSpeed = 5.0f;

	//=================================================
	// �J�����g�p��Ԑ؂�ւ�
	//=================================================
	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{// SPACE�L�[����������
		Init();

		m_bFollow = m_bFollow ? false : true;
	}

	if (m_bFollow == false)
	{// �J�������蓮�����̎�

		//=================================================
		// �����_�̐���(����])
		//=================================================
		if (pInputKeyboard->GetPress(DIK_Q) == true)
		{// ����]
			m_rot.y += 0.03f;

			// ���_����𒍎��_�ɐ؂�ւ���
			m_bCameraV = false;
		}

		if (pInputKeyboard->GetPress(DIK_E) == true)
		{// �E��]
			m_rot.y -= 0.03f;

			// ���_����𒍎��_�ɐ؂�ւ���
			m_bCameraV = false;
		}

		//=================================================
		// �����_�̐���(�c��])
		//=================================================
		if (pInputKeyboard->GetPress(DIK_R) == true)
		{// ���]
			m_rot.x += 0.03f;

			// ���_����𒍎��_�ɐ؂�ւ���
			m_bCameraV = false;
		}

		if (pInputKeyboard->GetPress(DIK_F) == true)
		{// ����]
			m_rot.x -= 0.03f;

			// ���_����𒍎��_�ɐ؂�ւ���
			m_bCameraV = false;
		}

		//=================================================
		// ���_�̐���(����])
		//=================================================
		if (pInputKeyboard->GetPress(DIK_Z) == true)
		{// ����]
			m_rot.y += 0.03f;

			// ���_��������_�ɐ؂�ւ���
			m_bCameraV = true;
		}

		if (pInputKeyboard->GetPress(DIK_C) == true)
		{// �E��]
			m_rot.y -= 0.03f;

			// ���_��������_�ɐ؂�ւ���
			m_bCameraV = true;
		}

		//=================================================
		// ���_�̐���(�c��])
		//=================================================
		if (pInputKeyboard->GetPress(DIK_T) == true)
		{// ���]
			m_rot.x -= 0.03f;

			// ���_��������_�ɐ؂�ւ���
			m_bCameraV = true;
		}

		if (pInputKeyboard->GetPress(DIK_G) == true)
		{// ����]
			m_rot.x += 0.03f;

			// ���_��������_�ɐ؂�ւ���
			m_bCameraV = true;
		}

		//=================================================
		// ���_�̈ړ�
		//=================================================
		if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{// ���ړ�
			m_move.x = sinf(m_rot.y) * fSpeed;
			m_move.z = -cosf(m_rot.y) * fSpeed;
		}

		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{// �E�ړ�
			m_move.x = -sinf(m_rot.y) * fSpeed;
			m_move.z = cosf(m_rot.y) * fSpeed;
		}

		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{// �O�ړ�
			m_move.x = -cosf(m_rot.y) * fSpeed;
			m_move.z = -sinf(m_rot.y) * fSpeed;
		}

		if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// ��ړ�
			m_move.x = cosf(m_rot.y) * fSpeed;
			m_move.z = sinf(m_rot.y) * fSpeed;
		}

		// �p�x�̐��K��
		if (m_rot.x > D3DX_PI - 0.01f)
		{
			m_rot.x = D3DX_PI - 0.01f;
		}
		else if (m_rot.x < 0.01f)
		{
			m_rot.x = 0.0f + 0.01f;
		}

		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		// �ړ��̊���
		m_move = m_move * 0.85f;

		if (m_bCameraV == true)
		{// ���_����̎�
			// �ړ��ʂ����Z
			m_posR += m_move;

			// ���_�̈ʒu�������W�ɕϊ�
			m_posV.x = m_posR.x + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
			m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
			m_posV.z = m_posR.z + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		}
		else if (m_bCameraV == false)
		{// �����_����̎�
			// �ړ��ʂ����Z
			m_posV += m_move;

			// �����_�̈ʒu�������W�ɕϊ�
			m_posR.x = m_posV.x + sinf(m_rot.x) * cosf(m_rot.y) * -m_fDistance;
			m_posR.y = m_posV.y + cosf(m_rot.x) * -m_fDistance;
			m_posR.z = m_posV.z + sinf(m_rot.x) * sinf(m_rot.y) * -m_fDistance;
		}
	}
	else if (m_bFollow == true)
	{// �J�������Ǐ]�����̎�

		//=================================================
		// ���_�̉�����(�L�[�{�[�h)
		//=================================================
		if (pInputKeyboard->GetPress(DIK_Q) == true)
		{// ����]
			m_rot.y += 0.03f;
		}

		if (pInputKeyboard->GetPress(DIK_E) == true)
		{// �E��]
			m_rot.y -= 0.03f;
		}

		if (pInputKeyboard->GetPress(DIK_R) == true)
		{// ���]
			m_rot.x -= 0.03f;
		}

		if (pInputKeyboard->GetPress(DIK_F) == true)
		{// ����]
			m_rot.x += 0.03f;

		}

		////=================================================
		//// �����_�̐���(�}�E�X)
		////=================================================
		//// ���E��]
		//m_rot.y -= pInputMouse->GetMove().x * 0.003f;

		//// �㉺��]
		//m_rot.x -= pInputMouse->GetMove().y * 0.003f;

		// �p�x�̐��K��
		if (m_rot.x > D3DX_PI - 0.01f)
		{
			m_rot.x = D3DX_PI - 0.01f;
		}
		else if (m_rot.x < 0.01f)
		{
			m_rot.x = 0.0f + 0.01f;
		}

		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		// �ړ��ʂ����Z
		m_posR += m_move;

		// ���_�̈ʒu�������W�ɕϊ�
		m_posV.x = m_posR.x + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	}

	// ���_�̈ʒu���|���S���̍����������Ƃ�
	if (m_posV.y <= pMeshfield->GetPos().y)
	{
		m_posV.y = pMeshfield->GetPos().y;
	}

}
//********************************************
// �ݒ菈��
//********************************************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�N�\���̃|�C���^
	CDebugproc* pDebugproc;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIsIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �f�o�b�N�\��
	if (m_bFollow == true)
	{
		pDebugproc->Print("[F2] �J�����̒Ǐ]:ON\n");
	}
	else if (m_bFollow == false)
	{
		pDebugproc->Print("[F2] �J�����̒Ǐ]:OFF\n");

		pDebugproc->Print("--------�J�����̈ړ����@--------\n");
		pDebugproc->Print("���_�ړ��F���L�[\n");
		pDebugproc->Print("���_�c��]�FT [���]], G [����]]\n");
		pDebugproc->Print("���_����]�FZ [����]], C [�E��]]\n");
		pDebugproc->Print("�����_�c��]�FR [���]], F [����]]\n");
		pDebugproc->Print("�����_����]�FQ [����]], E [�E��]]\n\n");


	}

	// ���_�̈ʒu�ƌ���
	pDebugproc->Print("���_�̈ʒu:X %.1f, Y %.1f, Z %.1f\n", m_posV.x, m_posV.y, m_posV.z);
	pDebugproc->Print("���_�̌���:X %.1f, Y %.1f, Z %.1f\n", m_rot.x, m_rot.y, m_rot.z);
	// �����_�̈ʒu
	pDebugproc->Print("�����_�̈ʒu:X %.1f, Y %.1f, Z %.1f\n", m_posR.x, m_posR.y, m_posR.z);

}
//********************************************
// �J�����̈ʒu�̐ݒ菈��
//********************************************
void CCamera::SetPosCamera(D3DXVECTOR3 pos)
{
	m_posV = pos + D3DXVECTOR3(0.0f, 70.f, -200.0f);
	m_posR = pos + D3DXVECTOR3(0.0f, 70.f, 0.0f);
}

//********************************************
// �J�����̈ړ��ʂ̐ݒ菈��
//********************************************
void CCamera::SetMoveCamera(D3DXVECTOR3 move)
{
	m_move = move;
}