//======================================================
// 
// ��������
// Author:Takahashi Misaki
// 
//======================================================

#include "explosion.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CExplosion::CExplosion(int nPriority):CObject2D(nPriority)
{
	// �e�N�X�`���̏����擾
	m_pExplosionTex = CObject2D::GetTexture();

	m_pExplosionTex->fWidth = 50.0f;
	m_pExplosionTex->fHeight = 50.0f;

	m_nCountAnim  = 5;
	m_nPatternAnim = 8;
	m_nCounter = m_nCountAnim * m_nPatternAnim;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}
//********************************************
// �f�X�g���N�^
//********************************************
CExplosion::~CExplosion()
{
}
//********************************************
// ����������
//********************************************
HRESULT CExplosion::Init(void)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	// �e�N�X�`���̃A�j���[�V��������
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CExplosion::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CExplosion::Update(void)
{
	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	// �e�N�X�`���̃A�j���[�V��������
	CObject2D::SetTextureAnim(m_nCountAnim, m_nPatternAnim);

	m_nCounter--;

	if (m_nCounter ==  0)
	{// �A�j���[�V�������I�������
		// �I������
		CExplosion::Uninit();
	}

}

//********************************************
// �`�揈��
//********************************************
void CExplosion::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}
//********************************************
// �N���G�C�g����
//********************************************
CExplosion* CExplosion::Create(const D3DXVECTOR3 Pos)
{
	CExplosion* pExplosion = NULL;

	int nNumAll = CObject::GetNumAll();

	//if (nNumAll < MAX_OBJECT - 1)
	//{// ���������ő�ł͂Ȃ��Ƃ�

	//	// �����̐���
	//	pExplosion = new CExplosion(4);

	//	// ����������
	//	pExplosion->Init();

	//	pExplosion->m_pExplosionTex->Pos = Pos;
	//}

	return pExplosion;
}
