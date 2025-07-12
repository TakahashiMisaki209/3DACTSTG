//======================================================
// 
// �G�t�F�N�g����
// Author:Takahashi Misaki
// 
//======================================================

#include "effect.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CEffect::CEffect(int nPriority):CObject2D(nPriority)
{
	m_nLife = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CEffect::~CEffect()
{
}

//********************************************
// ����������
//********************************************
HRESULT CEffect::Init(void)
{
	// �e�N�X�`���̏����擾
	m_pEffectTex = CObject2D::GetTexture();

	m_pEffectTex->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffectTex->fWidth = 30.0f;
	m_pEffectTex->fHeight = 30.0f;
	m_pEffectTex->Col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	m_nLife = 20;

	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CEffect::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CEffect::Update(void)
{
 	m_pEffectTex->fWidth = m_pEffectTex->fWidth * 0.93f;
	m_pEffectTex->fHeight = m_pEffectTex->fHeight * 0.93f;

	m_pEffectTex->Col.a = m_pEffectTex->Col.a * 0.8f;

	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	// �G�t�F�N�g�̗̑͂����炷
	m_nLife--;

	if (m_nLife <= 0)
	{
		// �G�t�F�N�g�̏I������
		CEffect::Uninit();
	}
}

//********************************************
// �`�揈��
//********************************************
void CEffect::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::AlphaDraw();
}

//********************************************
// �N���G�C�g����
//********************************************
CEffect* CEffect::Create(const D3DXVECTOR3 Pos)
{
	CEffect* pEffect = NULL;

	int nNumAll = CObject::GetNumAll();

	//if (nNumAll < MAX_OBJECT - 1)
	//{// ���������ő�ł͂Ȃ��Ƃ�

	//	// �G�t�F�N�g�̐���
	//	pEffect = new CEffect;

	//	// ����������
	//	pEffect->Init();

	//	pEffect->m_pEffectTex->Pos = Pos;

	//	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	//	pEffect->SetTYPE(TYPE_EFFECT);
	//}

	return pEffect;
}