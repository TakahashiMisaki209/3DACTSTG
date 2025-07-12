//======================================================
// 
// X�t�@�C���̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "objectX.h"
#include "manager.h"

//********************************************
// �R���X�g���N�^
//********************************************
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//********************************************
// �f�X�g���N�^
//********************************************
CObjectX::~CObjectX()
{
}

//********************************************
// ����������
//********************************************
HRESULT CObjectX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	m_pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\Player\\00_body.x",
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
void CObjectX::Uninit(void)
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

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}

//********************************************
// �X�V����
//********************************************
void CObjectX::Update(void)
{

}

//********************************************
// �`�揈��
//********************************************
void CObjectX::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]���Ă���ʒu�ړ��𔻒�I�I�I�I�I

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���X�V
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̌Œ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//  ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);// g_apTextureBlock[nCntMat]

		// �u���b�N�p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//********************************************
// �N���G�C�g����
//********************************************
CObjectX* CObjectX::Create(void)
{
	CObjectX* pObjectX;

	// �I�u�W�F�N�gX�𐶐�
	pObjectX = new CObjectX;

	// ����������
	pObjectX->Init();

	return pObjectX;
}
