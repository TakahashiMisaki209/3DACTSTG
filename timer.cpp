//======================================================
// 
// �^�C�}�[����
// Author:Takahashi Misaki
// 
//======================================================

#include "timer.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
CNumber* CTimer::m_apNumer[MAX_COLUMET] = {};

//********************************************
// �R���X�g���N�^
//********************************************
CTimer::CTimer(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTime = 0;
}

//********************************************
// �f�X�g���N�^
//********************************************
CTimer::~CTimer()
{
}

//********************************************
// ����������
//********************************************
HRESULT CTimer::Init(void)
{
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.4f, 40.0f, 0.0f);

	int Time = m_nCntTime;
	int number1 = 100, number2 = 10;

	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		m_apNumer[nCount] = CNumber::Create(m_pos);

		m_pos.x += 60.0f;
	}

	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{

		if (nCount == 0)
		{
			Time = m_nCntTime / number1;
		}
		else
		{
			Time = m_nCntTime % number1 / number2;
			number1 = number1 / 10;
			number2 = number2 / 10;
		}

		m_apNumer[nCount]->SetNumber(Time);
	}

	return S_OK;
}

//********************************************
// �I������
//********************************************
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
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
void CTimer::Update(void)
{
	// �t���[�����J�E���g����ϐ�
	static int nCount = 0;
	int Time = m_nCntTime;
	int number1 = 100, number2 = 10;

	// �J�E���g����i�߂�
	nCount++;

	if (nCount >= MAX_FRAME)
	{// �J�E���g���ő�t���[���ɂȂ�����

		// �^�C�������炷
		m_nCntTime--;

		for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
		{

			if (nCount == 0)
			{
				Time = m_nCntTime / number1;
			}
			else
			{
				Time = m_nCntTime % number1 / number2;
				number1 = number1 / 10;
				number2 = number2 / 10;
			}

			m_apNumer[nCount]->SetNumber(Time);
		}

		// �J�E���g�������l�ɖ߂�
		nCount = 0;
	}

	if (m_nCntTime <= 0)
	{// �^�C����0�ɂȂ�����
		m_nCntTime = MAX_TIME;
	}

	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		// �i���o�[�̍X�V����
		m_apNumer[nCount]->Update();
	}
}

//********************************************
// �`�揈��
//********************************************
void CTimer::Draw(void)
{
	for (int nCount = 0; nCount < MAX_COLUMET; nCount++)
	{
		// �i���o�[�̕`�揈��
		m_apNumer[nCount]->Draw();
	}
}

//********************************************
// �N���G�C�g����
//********************************************
CTimer* CTimer::Create(void)
{
	CTimer* pTimer;

	// �^�C�}�[�𐶐�
	pTimer = new CTimer;

	// �^�C����ݒ�
	pTimer->m_nCntTime = MAX_TIME;

	// ����������
	pTimer->Init();

	return pTimer;
}
