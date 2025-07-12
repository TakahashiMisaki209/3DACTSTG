//======================================================
// 
// �}�l�[�W���[����
// Author:Takahashi Misaki
// 
//======================================================

#include "manager.h"

// �ÓI�����o�ϐ�
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pkeyboard = NULL;
CInputMouse* CManager::m_pMouse = NULL;
CSound* CManager::m_pSound = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CTexture* CManager::m_pTexture = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CObject3D* CManager::m_pObject3D = NULL;
CSky* CManager::m_Sky = NULL;
CMeshfield* CManager::m_pMeshfield = NULL;

//********************************************
// �R���X�g���N�^
//********************************************
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pkeyboard = NULL;
	m_pMouse = NULL;
	m_pSound = NULL;
	m_pCamera = NULL;
	m_pLight = NULL;
	m_pTexture = NULL;
	m_pPlayer = NULL;
	m_pObject3D = NULL;
	m_Sky = NULL;
}
//********************************************
// �f�X�g���N�^
//********************************************
CManager::~CManager()
{
}

//********************************************
// ����������
//********************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�𐶐�
	m_pRenderer = new CRenderer;
	// �L�[�{�[�h�𐶐�
	m_pkeyboard = new CInputKeyboard;
	// �}�E�X�𐶐�
	m_pMouse = new CInputMouse;
	// �T�E���h�𐶐�
	m_pSound = new CSound;
	// �J�����𐶐�
	m_pCamera = new CCamera;
	// ���C�g�𐶐�
	m_pLight = new CLight;
	// �e�N�X�`���𐶐�
	m_pTexture = new CTexture;

	// �����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
	{// ���������������s�����Ƃ�
		return-1;
	}

	// �L�[�{�[�h�̏���������
	if (FAILED(m_pkeyboard->Init(hInstance, hWnd)))
	{// ���������������s�����Ƃ�
		return-1;
	}

	// �}�E�X�̏���������
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{// ���������������s�����Ƃ�
		return-1;
	}

	// �T�E���h�̏���������
	if (FAILED(m_pSound->Init(hWnd)))
	{// ���������������s�����Ƃ�
		return-1;
	}

	// �J�����̏���������
	if (FAILED(m_pCamera->Init()))
	{// ���������������s�����Ƃ�
		return-1;
	}

	// ���C�g�̏���������
	if (FAILED(m_pLight->Init()))
	{// ���������������s�����Ƃ�
		return-1;
	}

	// �e�N�X�`���̓ǂݍ��ݏ���
	m_pTexture->Load();

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	// �^�C�}�[�̐���
	CTimer::Create();

	// �X�R�A�̐���
	CScore::Create();

	// ���b�V���t�B�[���h�̐���
	m_pMeshfield = CMeshfield::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 2000.0f, 100, 100, "data\\TEXTURE\\ground000.jpg");

	// ��̐���
	CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 2000.0f, 50, 50, "data\\TEXTURE\\sky000.jpeg");

	// �r���{�[�h�̐���
	CObjectBillboard::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));
	CObjectBillboard::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f));

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �e�N�X�`���̏I������
	m_pTexture->Unload();

	// �e�N�X�`���̔j��
	if (m_pLight != NULL)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		// �I������
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		// �I������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �I������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// �}�E�X�̔j��
	if (m_pMouse != NULL)
	{
		// �I������
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pkeyboard != NULL)
	{
		// �I������
		m_pkeyboard->Uninit();
		delete m_pkeyboard;
		m_pkeyboard = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//********************************************
// �X�V����
//********************************************
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V����
	m_pkeyboard->Update();
	// �}�E�X�̍X�V����
	m_pMouse->Update();
	// �����_���[�̍X�V����
	m_pRenderer->Update();
	// �J�����̍X�V����
	m_pCamera->Update();
	// ���C�g�̍X�V����
	m_pLight->Update();
}

//********************************************
// �`�揈��
//********************************************
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	m_pRenderer->Draw();
}
