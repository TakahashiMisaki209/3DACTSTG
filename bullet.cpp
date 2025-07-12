//======================================================
// 
// �ˌ�����
// Author:Takahashi Misaki
// 
//======================================================

#include "bullet.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"
#include "score.h"
#include "effect.h"

//********************************************
// �R���X�g���N�^
//********************************************
CBullet::CBullet(int nPriority) :CObject2D(nPriority)
{
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_nLife = 0;
	m_fMove = 0.0f;
}

//********************************************
// �f�X�g���N�^
//********************************************
CBullet::~CBullet()
{
}

//********************************************
// ����������
//********************************************
HRESULT CBullet::Init(void)
{
	// �e�N�X�`���̏����擾
	m_pBulletTex = CObject2D::GetTexture();

	m_pBulletTex->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBulletTex->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBulletTex->fWidth = 30.0f;
	m_pBulletTex->fHeight = 30.0f;

	m_nCountAnim = 5;
	m_nPatternAnim = 4;
	m_nLife = 120;
	m_fMove = 5.0f;

	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	// �e�N�X�`���̃A�j���[�V��������
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CBullet::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CBullet::Update(void)
{
	bool bCollision = false;

	if (m_type == TYPE_PLAYER)
	{
		m_pBulletTex->Pos.x += m_fMove;

		// �G�t�F�N�g�̐���
		CEffect::Create(m_pBulletTex->Pos);

	}
	else if (m_type == TYPE_ENEMY)
	{
		m_pBulletTex->Pos.x -= m_fMove;
	}

	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	// �e�N�X�`���̃A�j���[�V��������
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	// �G�Ƃ̓����蔻��
	bCollision = CollisionEnemy(m_pBulletTex->Pos);

	if (false == bCollision)
	{// �G�Ɠ������Ă��Ȃ�������
		
		// �̗͂����炷
		m_nLife--;

		if (m_pBulletTex->Pos.x <= 0 || m_pBulletTex->Pos.x >= SCREEN_WIDTH || m_pBulletTex->Pos.y <= 0 || m_pBulletTex->Pos.y >= SCREEN_HEIGHT)
		{// ��ʊO�ɏo����

			//// �����𐶐�
			//CExplosion::Create(m_pBulletTex->Pos);

			// �I������
			Uninit();

		}
		else if (m_nLife == 0)
		{// �̗͂��Ȃ��Ȃ�����

			//// �����𐶐�
			//CExplosion::Create(m_pBulletTex->Pos);

			// �I������
			Uninit();
		}
	}
}

//********************************************
// �`�揈��
//********************************************
void CBullet::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//********************************************
// �G�Ƃ̓����蔻��
//********************************************
bool CBullet::CollisionEnemy(D3DXVECTOR3 Pos)
{
	D3DXVECTOR3 pos = {};

	//for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	//{
	//	CObject* pObj;

	//	// �I�u�W�F�N�g�̎擾
	//	pObj = GetCObject(nCount);

	//	if (pObj != NULL)
	//	{
	//		TYPE type;

	//		// ��ނ̎擾
	//		type = pObj->GetTYPE();

	//		if (type == TYPE_ENEMY && m_type == TYPE_PLAYER )
	//		{// ��ނ��G�̎�

	//			// �G�̈ʒu����
	//			pos = pObj->GetPos();

	//			if (pos.x - m_pBulletTex->fWidth <= Pos.x && pos.x + m_pBulletTex->fWidth >= Pos.x)
	//			{// �G�Ɠ������Ă���ꍇ(X��)

	//				if (pos.y - m_pBulletTex->fHeight <= Pos.y && pos.y + m_pBulletTex->fHeight >= Pos.y)
	//				{// �G�Ɠ������Ă���ꍇ(Y��)

	//					//// �����𐶐�
	//					//CExplosion::Create(Pos);

	//					// �X�R�A�̉��Z����
	//					CScore::AddScore(100);

	//					// �G�̏I������
	//					pObj->Uninit();

	//					// �I������
	//					Uninit();

	//					return true;
	//				}
	//			}
	//		}
	//		else if (type == TYPE_PLAYER && m_type == TYPE_ENEMY)
	//		{// ��ނ��v���C���[�̎�

	//			// �v���C���[�̈ʒu����
	//			pos = pObj->GetPos();

	//			if (pos.x - m_pBulletTex->fWidth <= Pos.x && pos.x + m_pBulletTex->fWidth >= Pos.x)
	//			{// �v���C���[�Ɠ������Ă���ꍇ(X��)

	//				if (pos.y - m_pBulletTex->fHeight <= Pos.y && pos.y + m_pBulletTex->fHeight >= Pos.y)
	//				{// �v���C���[�Ɠ������Ă���ꍇ(Y��)

	//					//// �����𐶐�
 // 						// CExplosion::Create(Pos);

	//					//// �v���C���[�̃q�b�g����
	//					//CPlayer::HitBullet(true);

	//					// �I������
	//					Uninit();

	//					return true;
	//				}
	//			}
	//		}
	//	}
	//}

	return false;
}

//********************************************
// �N���G�C�g����
//********************************************
CBullet* CBullet::Create(const D3DXVECTOR3 Pos, const TYPE type)
{
	CBullet* pBullet = NULL;

	int nNumAll = CObject::GetNumAll();

	//if (nNumAll < MAX_OBJECT - 1)
	//{// ���������ő�ł͂Ȃ��Ƃ�

	//	// �e�̐���
	//	pBullet = new CBullet;

	//	// ����������
	//	pBullet->Init();

	//	pBullet->m_pBulletTex->Pos = Pos;

	//	pBullet->m_type = type;

	//	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	//	pBullet->SetTYPE(TYPE_BULLET);
	//}

	return pBullet;
}