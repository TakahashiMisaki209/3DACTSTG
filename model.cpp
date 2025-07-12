//======================================================
// 
// ���f���̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "model.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CModel::CModel()
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Offsetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Offsetrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
}

//********************************************
// �f�X�g���N�^
//********************************************
CModel::~CModel()
{
}

//********************************************
// ����������
//********************************************
HRESULT CModel::Init(const char* pXfileName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pXfileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CModel::Uninit(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//********************************************
// �`�揈��
//********************************************
void CModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

	// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]���Ă���ʒu�ړ��𔻒�I�I�I�I�I

	// �p�[�c�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);

	// �p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	// �p�[�c��[�e�̃}�g���b�N�X]��ݒ�
	if (m_pParent != NULL)
	{// �e�̃��f��������ꍇ
		// �e���f���̃}�g���b�N�X���擾����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// �e�̃��f�����Ȃ��ꍇ
		// ����(�ŐV)�̃}�g���b�N�X���擾����[ = �v���C���[�̃}�g���b�N�X]
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//  ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// �p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);// g_apTextureBlock[nCntMat]

		// �p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//********************************************
// �ݒ菈��
//********************************************
void CModel::SetParent(CModel* pModel, D3DXVECTOR3 Offsetpos, D3DXVECTOR3 Offsetrot)
{
	m_pParent = pModel;
	m_Offsetpos = Offsetpos;
	m_Offsetrot = Offsetrot;
	m_pos = Offsetpos;
	m_rot = Offsetrot;
}
//********************************************
// �N���G�C�g����
//********************************************
CModel* CModel::Create(const char* pXfileName)
{
	CModel* pModel;

	// �I�u�W�F�N�gX�𐶐�
	pModel = new CModel;

	// ����������
	pModel->Init(pXfileName);

	return pModel;
}
