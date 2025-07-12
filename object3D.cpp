// ==============================================
// 
// �I�u�W�F�N�g3D�̏���
// Aouther:Takahashi Misaki
//
// ==============================================

#include "object3D.h"
#include "manager.h"
#include "input.h"

//********************************************
// �R���X�g���N�^
//********************************************
CObject3D::CObject3D(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;	
	m_fHeight = 0.0f;
	m_bWireFrame = false;
	m_nIdxTexture = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CObject3D::~CObject3D()
{

}

//********************************************
// ����������
//********************************************
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

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
void CObject3D::Uninit(void)
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
void CObject3D::Update(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CInputKeyboard* pInputKeyboard;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_F1) == true)
	{// ���C���[�t���[���@�\�̐؂�ւ�
		m_bWireFrame ? true : false;
	}

	if (m_bWireFrame == false)
	{// ���C���[�t���[�����I���ɂ���
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		m_bWireFrame = true;
	}
	else if (m_bWireFrame == true)
	{// ���C���[�t���[�����I�t�ɂ���
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		m_bWireFrame = false;
	}

}

//********************************************
// �`�揈��
//********************************************
void CObject3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�N�\���̃|�C���^
	CDebugproc* pDebugproc;

	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

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

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (m_bWireFrame == true)
	{// ���C���[�t���[���@�\���I���ɂȂ��Ă��鎞
		pDebugproc->Print("[F1] ���C���[�t���[��:ON\n");
	}
	else if (m_bWireFrame == false)
	{// ���C���[�t���[���@�\���I�t�ɂȂ��Ă��鎞
		pDebugproc->Print("[F1] ���C���[�t���[��:OFF\n");
	}
}
