// ==============================================
// 
// �r���{�[�h�̏���
// Aouther:Takahashi Misaki
//
// ==============================================

#include "billboard.h"
#include "manager.h"
#include "texture.h"

//********************************************
// �R���X�g���N�^
//********************************************
CObjectBillboard::CObjectBillboard(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//********************************************
// �f�X�g���N�^
//********************************************
CObjectBillboard::~CObjectBillboard()
{

}

//********************************************
// ����������
//********************************************
HRESULT CObjectBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���̎w��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\coin000.png");

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);

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
void CObjectBillboard::Uninit(void)
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
void CObjectBillboard::Update(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	
	CInputKeyboard* pInputKeyboard;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y + MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_TEXTURE_W * 0.5f, m_pos.y - MAX_TEXTURE_H * 0.5f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (pInputKeyboard->GetTrigger(DIK_F10) == true)
	{
		Uninit();
	}
}

//********************************************
// �r���{�[�h�̕`�揈��
//********************************************
void CObjectBillboard::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �v�Z�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X���擾
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �ʒu���X�V
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̌Œ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//********************************************
// ��������
//********************************************
CObjectBillboard* CObjectBillboard::Create(D3DXVECTOR3 pos)
{
	CObjectBillboard* pBillboard;

	// �r���{�[�h�𐶐�
	pBillboard = new CObjectBillboard;

	// ����������
	pBillboard->Init();

	// �ʒu����
	pBillboard->m_pos = pos;

	return pBillboard;
}