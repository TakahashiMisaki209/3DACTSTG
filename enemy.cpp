//======================================================
// 
// �v���C���[����
// Author:Takahashi Misaki
// 
//======================================================

#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "Bullet.h"


//********************************************
// �R���X�g���N�^
//********************************************
CEnemy::CEnemy(int nPriority) :CObject2D(nPriority)
{
	m_Move = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);

	// �e�N�X�`���̏����擾
	m_pEnemyTex = CObject2D::GetTexture();

	m_pEnemyTex->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEnemyTex->fWidth = 60.0f;
	m_pEnemyTex->fHeight = 60.0f;
	m_pEnemyTex->Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}
//********************************************
// �f�X�g���N�^
//********************************************
CEnemy::~CEnemy()
{
}

//********************************************
// ����������
//********************************************
HRESULT CEnemy::Init(void)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CEnemy::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CEnemy::Update(void)
{
	// �e��łԊu���J�E���g����ϐ�
	static int nCntTime = 0;

	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	switch (m_Type)
	{
	case ENEMY_1:
		// �G�P
		
		//==================================
		// �ړ��̏���
		//==================================
		if (m_pEnemyTex->Pos.x <= 0.0f)
		{
			m_Move.x = 2.0f;
		}
		else if (m_pEnemyTex->Pos.x >= SCREEN_WIDTH)
		{
			m_Move.x = -2.0f;
		}

		if (m_pEnemyTex->Pos.y <= 0.0f)
		{
			m_Move.y = 1.0f;
		}
		else if (m_pEnemyTex->Pos.y >= SCREEN_HEIGHT)
		{
			m_Move.y = -1.0f;
		}

		break;

	case ENEMY_2:
		// �G�Q

		if (m_pEnemyTex->Pos.x <= 0.0f)
		{
			m_Move.x = 1.0f;
		}
		else if (m_pEnemyTex->Pos.x >= SCREEN_WIDTH)
		{
			m_Move.x = -1.0f;
		}

		if (m_pEnemyTex->Pos.y <= 0.0f)
		{
			m_Move.y = 2.0f;
		}
		else if (m_pEnemyTex->Pos.y >= SCREEN_HEIGHT)
		{
			m_Move.y= -2.0f;
		}

		break;

	case ENEMY_3:
		// �G�R

		if (m_pEnemyTex->Pos.x <= 0.0f)
		{
			m_Move.x = 2.0f;
		}
		else if (m_pEnemyTex->Pos.x >= SCREEN_WIDTH)
		{
			m_Move.x = -2.0f;
		}

		if (m_pEnemyTex->Pos.y <= 0.0f)
		{
			m_Move.y = 2.0f;
		}
		else if (m_pEnemyTex->Pos.y >= SCREEN_HEIGHT)
		{
			m_Move.y = -2.0f;
		}

		break;

	}

	// �ړ��ʂ����Z
	m_pEnemyTex->Pos.x += m_Move.x;
	m_pEnemyTex->Pos.y += m_Move.y;

	nCntTime++;

	if (nCntTime >= 100)
	{
		nCntTime = 0;

		CBullet::Create(m_pEnemyTex->Pos, TYPE_ENEMY);
	}
}

//********************************************
// �`�揈��
//********************************************
void CEnemy::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//********************************************
// �N���G�C�g����
//********************************************
CEnemy* CEnemy::Create(const D3DXVECTOR3 Pos, const ENEMY Type)
{
	CEnemy* pEnemy;

	// �G�̐���
	pEnemy = new CEnemy;
	
	// �G�̈ʒu����
	pEnemy->m_pEnemyTex->Pos = Pos;

	// �G�̎�ނ���
	pEnemy->m_Type = Type;

	// ��ނ��Ƃ̐ݒ�
	switch (pEnemy->m_Type)
	{
	case ENEMY_1:
		
		// �F�̐ݒ�
		pEnemy->m_pEnemyTex->Col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		break;

	case ENEMY_2:

		// �F�̐ݒ�
		pEnemy->m_pEnemyTex->Col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		break;

	case ENEMY_3:

		// �F�̐ݒ�
		pEnemy->m_pEnemyTex->Col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		break;

	}

	// ����������
	pEnemy->Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	pEnemy->SetTYPE(TYPE_ENEMY);

	return pEnemy;
}
