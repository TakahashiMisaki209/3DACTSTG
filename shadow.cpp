//======================================================
// 
// �e�̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "shadow.h"
#include "texture.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CShadow::CShadow(int nPriority) :CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CShadow::~CShadow()
{

}

//********************************************
// ����������
//********************************************
HRESULT CShadow::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���̎w��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\shadow000.jpg");

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);

	// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CShadow::Uninit(void)
{
	// �I�u�W�F�N�g3D�̏I������
	CObject3D::Uninit();
}

//********************************************
// �X�V����
//********************************************
void CShadow::Update(void)
{
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z + m_fHeight * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth * 0.5f, m_pos.y, m_pos.z - m_fHeight * 0.5f);

	// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//********************************************
// �`�揈��
//********************************************
void CShadow::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���[���h�}�g���b�N�X�̌Œ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//********************************************
// �ʒu�̐ݒ菈��
//********************************************
void CShadow::SetPos(float fPosX, float fPosZ)
{
	m_pos.x = fPosX;
	m_pos.z = fPosZ;
}

//********************************************
// �N���G�C�g����
//********************************************
CShadow* CShadow::Create(float fPosX, float fPosZ ,D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CShadow* pShadow;

	// �e�𐶐�
	pShadow = new CShadow;

	// �������e�ϐ��ɑ������
	pShadow->m_pos.x = fPosX;
	pShadow->m_pos.z = fPosZ;
	pShadow->m_rot = rot;
	pShadow->m_fWidth = fWidth;
	pShadow->m_fHeight = fHeight;

	// ����������
	pShadow->Init();

	return pShadow;

}