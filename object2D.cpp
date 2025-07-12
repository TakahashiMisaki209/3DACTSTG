//======================================================
// 
// �I�u�W�F�N�g2D����
// Author:Takahashi Misaki
// 
//======================================================

#include "object2D.h"
#include "manager.h"
#include "input.h"

//********************************************
// �R���X�g���N�^
//********************************************
CObject2D::CObject2D(int nPriority) :CObject(nPriority)
{
	m_Texture.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Texture.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Texture.fWidth = 0.0f;
	m_Texture.fHeight = 0.0f;
	m_Texture.Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_fLength = 0;
	m_fAngle = 0;
	m_aPosTexU = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CObject2D::~CObject2D()
{
}

//********************************************
// ����������
//********************************************
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �Ίp���̒������Z�o����
	m_fLength = sqrtf(m_Texture.fWidth * m_Texture.fWidth + m_Texture.fHeight * m_Texture.fHeight) / 2.0f;

	// �Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_Texture.fWidth, m_Texture.fHeight);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_Texture.Col;
	pVtx[1].col = m_Texture.Col;
	pVtx[2].col = m_Texture.Col;
	pVtx[3].col = m_Texture.Col;

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
void CObject2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}

//********************************************
// �X�V����
//********************************************
void CObject2D::Update(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Texture.Pos.x + sinf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_Texture.Pos.y + cosf(m_Texture.Rot.z + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_Texture.Col;
	pVtx[1].col = m_Texture.Col;
	pVtx[2].col = m_Texture.Col;
	pVtx[3].col = m_Texture.Col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//********************************************
// �`�揈��
//********************************************
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  // �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �h�b�g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//********************************************
// �A���t�@�u�����h����̕`�揈��
//********************************************
void CObject2D::AlphaDraw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  // �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �h�b�g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//********************************************
// �e�N�X�`���̃A�j���[�V��������
//********************************************
void CObject2D::SetTextureAnim(const int nCountAnim, const int nPatternAnim)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 1.0f);

	m_nCountAnim++;

	if ((m_nCountAnim % nCountAnim == 0))
	{
		m_nCountAnim = 0;
		
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f),0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * (10.0f / nPatternAnim * 0.1f) + (10.0f / nPatternAnim * 0.1f), 1.0f);
	
		m_nPatternAnim = (m_nPatternAnim + 1) % nPatternAnim;

	}	

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//********************************************
// �w�i�̃X�N���[������
//********************************************
void CObject2D::SetBGScroll(int nCount)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_aPosTexU += 0.002f * (1 + nCount);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_aPosTexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_aPosTexU + 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
