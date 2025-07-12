//======================================================
// 
// �i���o�[����
// Author:Takahashi Misaki
// 
//======================================================

#include "number.h"
#include "manager.h"
#include "texture.h"

//********************************************
// �R���X�g���N�^
//********************************************
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fWidth = 0.0f;
	fHeight = 0.0f;
	m_nNumber = 0;
	m_nColume = 0;
	m_nIdxTexture = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CNumber::~CNumber()
{
}

//********************************************
// ����������
//********************************************
HRESULT CNumber::Init(void)
{
	// �l�̐ݒ�
	fWidth = 60.0f;
	fHeight = 80.0f;

	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���̎w��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\number000.png");

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
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f * 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//********************************************
// �X�V����
//********************************************
void CNumber::Update(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y - fHeight * 0.5f, pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth * 0.5f, pos.y + fHeight * 0.5f, pos.z);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber) + 1.0f * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f * 0.1f * m_nNumber) + 1.0f * 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//********************************************
// �`�揈��
//********************************************
void CNumber::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();  // �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̃|�C���^
	CTexture* pTexture = CManager::GetTexture();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �h�b�g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//********************************************
// �ݒ菈��
//********************************************
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}

//********************************************
// �N���G�C�g����
//********************************************
CNumber* CNumber::Create(D3DXVECTOR3 pos)
{
	CNumber* pNumber;

	// �����𐶐�
	pNumber = new CNumber;

	// ����������
	pNumber->Init();

	// ��������
	pNumber->pos = pos;

	return pNumber;
}