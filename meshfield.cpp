// ==============================================
// 
// �I�u�W�F�N�g3D�̏���
// Aouther:Takahashi Misaki
//
// ==============================================

#include "meshfield.h"
#include "manager.h"
#include "input.h"

//********************************************
// �R���X�g���N�^
//********************************************
CMeshfield::CMeshfield(int nPriority):CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTexture = 0;
	m_bWireFrame = false;
	m_fWidth = 0.0f;	
	m_fHeight = 0.0f;
	m_nIntervalX = 0;	
	m_nIntervalZ = 0;	
	m_nVertex = 0;	
	m_nPolygon = 0;	
	m_nIdx = 0;		
}

//********************************************
// �f�X�g���N�^
//********************************************
CMeshfield::~CMeshfield()
{
}

//********************************************
// ����������
//********************************************
HRESULT CMeshfield::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���݂̒��_�ԍ�
	int nVtx = 0;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= m_nIntervalZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_nIntervalX; nCntX++)
		{
			// ���_���W�̌v�Z
			float fPosX = (float)(m_fWidth / m_nIntervalX) * (float)nCntX;
			float fPosZ = (float)(m_fHeight / m_nIntervalZ) * (float)nCntZ;

			// �e�N�X�`�����W�̌v�Z
			float fTexX = (float)m_fWidth / ((float)m_fWidth * (float)m_nIntervalX) * (float)nCntX;
			float fTexZ = (float)m_fHeight / ((float)m_fHeight * (float)m_nIntervalZ) * (float)nCntZ;

			// ���_���W�̐ݒ�
			pVtx[nVtx].pos.x = m_pos.x + fPosX;
			pVtx[nVtx].pos.y = m_pos.y + 0.0f;
			pVtx[nVtx].pos.z = m_pos.z + (-fPosZ);

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nVtx].tex.x = fTexX;
			pVtx[nVtx].tex.y = fTexZ;

			nVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X
	int nIdxA = m_nIntervalX + 1;
	int nIdxB = 0;
	// ���݂̃C���f�b�N�X�ԍ�
	int nIdx = 0;

	for (int nCntZ = 0; nCntZ < m_nIntervalZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_nIntervalX; nCntX++)
		{
			// pIdx�ɉ��i�Ə�i�̒��_�ԍ���ݒ�
			pIdx[nIdx] = nIdxA;			// ���i
			pIdx[nIdx + 1] = nIdxB;		// ��i

			// �ԍ���ݒ肵�������i�߂�
			nIdx += 2;

			// �C���f�b�N�X����i�߂�
			nIdxA++;
			nIdxB++;
		}

		// �k�ރ|���S���p�̒��_�ԍ��ݒ��ǉ�
		if (nCntZ < m_nIntervalZ - 1)
		{
			// pIdx�ɉ��i�Ə�i�̒��_�ԍ���ݒ�
			pIdx[nIdx] = nIdxB - 1;		// ���i
			pIdx[nIdx + 1] = nIdxA;		// ��i

			// �ԍ���ݒ肵�������i�߂�
			nIdx += 2;
		}

	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CMeshfield::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}

//********************************************
// �X�V����
//********************************************
void CMeshfield::Update(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CInputKeyboard* pInputKeyboard;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bWireFrame == false && pInputKeyboard->GetTrigger(DIK_F1) == true)
	{// ���C���[�t���[�����I���ɂ���
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		m_bWireFrame = true;
	}
	else if (m_bWireFrame == true && pInputKeyboard->GetTrigger(DIK_F1) == true)
	{// ���C���[�t���[�����I�t�ɂ���
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		m_bWireFrame = false;
	}

}

//********************************************
// �`�揈��
//********************************************
void CMeshfield::Draw(void)
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

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);

	//=================================================
	// �f�o�b�N�\��
	//=================================================

	if (m_bWireFrame == true)
	{
		pDebugproc->Print("[F1] ���C���[�t���[��:ON\n");
	}
	else if (m_bWireFrame == false)
	{
		pDebugproc->Print("[F1] ���C���[�t���[��:OFF\n");
	}
}

//********************************************
// ���b�V���t�B�[���h�̐ݒ菈��
//********************************************
void CMeshfield::SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float fHeight, int nIntervalX, int nIntervalZ, const char* textname)
{
	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���̎w��
	m_nIdxTexture = pTexture->Register(textname);

	m_fWidth = Width;																		// �~���̔��a
	m_fHeight = fHeight;																	// �~���̏c��
	m_pos = D3DXVECTOR3(pos.x - (m_fWidth * 0.5f), pos.y, pos.z + (m_fHeight * 0.5f));		// �ʒu
	m_rot = rot;																			// ����
	m_nIntervalX = nIntervalX;																// ���̒��_��
	m_nIntervalZ = nIntervalZ;																// �c�̒��_��
	m_nVertex = (nIntervalX + 1) * (nIntervalZ + 1);										// ���_��
	m_nPolygon = (m_nIntervalX * m_nIntervalZ * 2) + ((m_nIntervalZ - 1) * 4);				// �|���S����
	m_nIdx = m_nPolygon + 2;																// �C���f�b�N

}

//********************************************
// �N���G�C�g����
//********************************************
CMeshfield* CMeshfield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float fHeight, int nIntervalX, int nIntervalZ, const char* textname)
{
	CMeshfield* pMeshfield;

	// ���b�V���t�B�[���h�𐶐�
	pMeshfield = new CMeshfield;

	// ��̐ݒ菈��
	pMeshfield->SetMeshfield(pos, rot, Width, fHeight, nIntervalX, nIntervalZ, textname);

	// ����������
	pMeshfield->Init();

	return pMeshfield;
}
