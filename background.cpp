//======================================================
// 
// �w�i����
// Author:Takahashi Misaki
// 
//======================================================
 
#include "background.h" 
#include "manager.h"


//********************************************
// �R���X�g���N�^
//********************************************
CBG2D::CBG2D(int nPriority) :CObject2D(nPriority)
{
	// �e�N�X�`���̏����擾
	m_pBGTex = CObject2D::GetTexture();

	m_pBGTex->Pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	m_pBGTex->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBGTex->fWidth = SCREEN_WIDTH;
	m_pBGTex->fHeight = SCREEN_HEIGHT;
	m_pBGTex->Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_nID = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CBG2D::~CBG2D()
{
}

//********************************************
// ����������
//********************************************
HRESULT CBG2D::Init(void)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CBG2D::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CBG2D::Update(void)
{
	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	// �w�i�̃X�N���[������	
	CObject2D::SetBGScroll(m_nID);
}

//********************************************
// �`�揈��
//********************************************
void CBG2D::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//********************************************
// �N���G�C�g����
//********************************************
CBG2D* CBG2D::Create(void)
{
	static int nCount = 0;

	CBG2D* pBG;

	// �w�i�̐���
	pBG = new CBG2D;

	// ����������
	pBG->Init();

	pBG->m_nID = nCount;

	nCount++;

	return pBG;
}
