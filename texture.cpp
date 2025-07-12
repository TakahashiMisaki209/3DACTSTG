// ==============================================
// 
// �e�N�X�`���̏���
// Aouther:Takahashi Misaki
//
// ==============================================

#include "texture.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
int CTexture::m_nNumAll = 0;

//********************************************
// �R���X�g���N�^
//********************************************
CTexture::CTexture()
{
	for (int nCount = 0; nCount < MAX_NUMTEXTUER; nCount++)
	{
		m_apTexture[nCount] = NULL;
	}
}

//********************************************
// �f�X�g���N�^
//********************************************
CTexture::~CTexture()
{
}

//********************************************
// �ǂݍ��ݏ���
//********************************************
HRESULT CTexture::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���ׂẴe�N�X�`���ǂݍ���
	for (int nCount = 0; nCount < MAX_NUMTEXTUER; nCount++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			NULL,
			&m_apTexture[nCount]);
	}

	return S_OK;
}

//********************************************
// �e�N�X�`���̔j���̏���
//********************************************
void CTexture::Unload(void)
{
	// �S�Ẵe�N�X�`���j��
	for (int nCount = 0; nCount < MAX_NUMTEXTUER; nCount++)
	{
		// ���_�o�b�t�@�̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//********************************************
// �w��e�N�X�`���̓ǂݍ��ݏ���
//********************************************
int CTexture::Register(const char* pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pFilename,
		&m_apTexture[m_nNumAll]);

	return m_nNumAll++;

}