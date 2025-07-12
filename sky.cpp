// ==============================================
// 
// ��̏���
// Aouther:Takahashi Misaki
//
// ==============================================

#include "sky.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CSky::CSky(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�̃|�C���^
	m_pIdxBuff = NULL;						// �C���f�b�N�X�o�b�t�@�̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_nIdxTexture = 0;						// �e�N�X�`���̃C���f�b�N�X
	m_fRadius = 0;							// �~���̔��a
	m_fHeight = 0;							// �~���̏c��
	m_nIntervalX = 0;						// ���̒��_��
	m_nIntervalY = 0;						// �c�̒��_��
	m_nVertex = 0;							// ���_��
	m_nPolygon = 0;							// �|���S����
	m_nIdx = 0;								// �C���f�b�N
}

//********************************************
// �f�X�g���N�^
//********************************************
CSky::~CSky()
{
}

//********************************************
// ����������
//********************************************
HRESULT CSky::Init(void)
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

	for (int nCntY = 0; nCntY <= m_nIntervalY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= m_nIntervalX; nCntX++)
		{
			// ���_��u���p�x���v�Z
			m_rot.y = D3DX_PI - (D3DX_PI / (float)(m_nIntervalX / 2)) * nCntX;

			// �p�x�̐��K��
			if (m_rot.y < D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}


			// ���_���W�̌v�Z
			float fPosX = cosf(m_rot.y) * m_fRadius;
			float fPosY = ((float)m_fHeight / (float)m_nIntervalY) * (float)nCntY;
			float fPosZ = sinf(m_rot.y) * m_fRadius;

			// �e�N�X�`�����W�̌v�Z
			float fTexX = (float)m_fRadius / ((float)m_fRadius * (float)m_nIntervalX) * (float)nCntX;
			float fTexY = (float)m_fHeight / ((float)m_fHeight * (float)m_nIntervalY) * (float)nCntY;

			// ���_���W�̐ݒ�
			pVtx[nVtx].pos.x = m_pos.x + fPosX;
			pVtx[nVtx].pos.y = m_pos.y + (-fPosY);
			pVtx[nVtx].pos.z = m_pos.z + fPosZ;

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nVtx].tex.x = fTexX;
			pVtx[nVtx].tex.y = fTexY;

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

	for (int nCntY = 0; nCntY < m_nIntervalY; nCntY++)
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
		if (nCntY < m_nIntervalY - 1)
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
void CSky::Uninit(void)
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
void CSky::Update(void)
{
	// �L�[�{�[�h�̃|�C���^
	CInputKeyboard* pInputKeyboard;

	// �L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();
}

//********************************************
// �`�揈��
//********************************************
void CSky::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	// ��̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//********************************************
// ��̐ݒ菈��
//********************************************
void CSky::SetSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname)
{
	// �e�N�X�`���̃|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���̎w��
	m_nIdxTexture = pTexture->Register(textname);

	m_fRadius = Radius;																// �~���̔��a
	m_fHeight = fHeight;															// �~���̏c��
	m_pos = D3DXVECTOR3(pos.x, m_fHeight, pos.z);									// �ʒu
	m_rot = rot;																	// ����
	m_nIntervalX = nIntervalX;														// ���̒��_��
	m_nIntervalY = nIntervalY;														// �c�̒��_��
	m_nVertex = (nIntervalX + 1) * (nIntervalY + 1);								// ���_��
	m_nPolygon = (m_nIntervalX * m_nIntervalY * 2) + ((m_nIntervalY - 1) * 4);		// �|���S����
	m_nIdx = m_nPolygon + 2;														// �C���f�b�N

}

//********************************************
// �N���G�C�g����
//********************************************
CSky* CSky::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Radius, float fHeight, int nIntervalX, int nIntervalY, const char* textname)
{
	CSky* pSky;

	// ��𐶐�
	pSky = new CSky;

	// ��̐ݒ菈��
	pSky->SetSky(pos, rot, Radius, fHeight, nIntervalX, nIntervalY, textname);

	// ����������
	pSky->Init();

	return pSky;
}
