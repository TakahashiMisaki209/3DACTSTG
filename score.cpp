//======================================================
// 
// �X�R�A�̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "score.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;
CNumber* CScore::m_apNumer[MAX_COLUMES] = {};
int CScore::m_nScore = 0;

//********************************************
// �R���X�g���N�^
//********************************************
CScore::CScore(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//********************************************
// �f�X�g���N�^
//********************************************
CScore::~CScore()
{
}

//********************************************
// ����������
//********************************************
HRESULT CScore::Init(void)
{
	// �ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.65f, 40.0f, 0.0f);

	int nScore = m_nScore;
	int number1 = 10000000, number2 = 1000000;

	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		m_apNumer[nCount] = CNumber::Create(m_pos);

		m_pos.x += 60.0f;

		if (nCount == 0)
		{
			nScore = m_nScore / number1;
		}
		else
		{
			nScore = m_nScore % number1 / number2;
			number1 = number1 / 10;
			number2 = number2 / 10;
		}

		m_apNumer[nCount]->SetNumber(nScore);
	}

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		if (m_apNumer[nCount] != NULL)
		{
			// �i���o�[�̏I������
			m_apNumer[nCount]->Uninit();
			delete m_apNumer[nCount];
			m_apNumer[nCount] = NULL;
		}
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}

//********************************************
// �X�V����
//********************************************
void CScore::Update(void)
{
	int nScore = m_nScore;
	int number1 = 10000000, number2 = 1000000;

	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		if (nCount == 0)
		{
			nScore = m_nScore / number1;
		}
		else
		{
			nScore = m_nScore % number1 / number2;
			number1 = number1 / 10;
			number2 = number2 / 10;
		}

		// �i���o�[�̐ݒ菈��
		m_apNumer[nCount]->SetNumber(nScore);

		// �i���o�[�̍X�V����
		m_apNumer[nCount]->Update();
	}
}

//********************************************
// �`�揈��
//********************************************
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_COLUMES; nCount++)
	{
		// �i���o�[�̕`�揈��
		m_apNumer[nCount]->Draw();
	}
}

//********************************************
// ���Z����
//********************************************
void CScore::AddScore(int nScore)
{
	m_nScore += nScore;
}

//********************************************
// �N���G�C�g����
//********************************************
CScore* CScore::Create(void)
{
	CScore* pScore;

	// �X�R�A�𐶐�
	pScore = new CScore;

	// ����������
	pScore->Init();

	return pScore;
}