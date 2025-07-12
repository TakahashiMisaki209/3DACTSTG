//======================================================
// 
// ���[�V�����̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "motion.h"
#include "debugproc.h"

//********************************************
// �R���X�g���N�^
//********************************************
CMotion::CMotion()
{
	// �l���N���A����
	m_pfile = NULL;

	for (int nCount = 0; nCount < MAX_CHARACTER; nCount++)
	{
		m_aString[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_MotionInfo[nCount] = {};
	}

	m_NowType = TYPE_MAX;
	m_nNumKey = 0;
	m_nNumParts = 0;
	m_bLoop = false;
	m_nKey = 0;
	m_nNextKey = 0;
	m_nCounterMotion = 0;
	m_bMotionEnd = false;
	m_ppModel = {};

}

//********************************************
// �f�X�g���N�^
//********************************************
CMotion::~CMotion()
{
}

//********************************************
// ����������
//********************************************
void CMotion::Init(void)
{
	m_pfile = NULL;

	for (int nCount = 0; nCount < MAX_CHARACTER; nCount++)
	{
		m_aString[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_MotionInfo[nCount] = {};
	}

	m_NowType = TYPE_MAX;
	m_nNumKey = 0;
	m_nNumParts = 0;
	m_bLoop = false;
	m_nKey = 0;
	m_nNextKey = 1;
	m_nCounterMotion = 0;
	m_bMotionEnd = false;
	m_ppModel = {};

	// �t�@�C���ǂݍ��ݏ���
	Load("data\\MOTION\\motion001.txt");
}

//********************************************
// �I������
//********************************************
void CMotion::Uninit(void)
{
	m_pfile = NULL;

	for (int nCount = 0; nCount < MAX_CHARACTER; nCount++)
	{
		m_aString[nCount] = NULL;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		m_MotionInfo[nCount] = {};
	}

	m_NowType = TYPE_MAX;
	m_nNumKey = 0;
	m_nNumParts = 0;
	m_bLoop = false;
	m_nKey = 0;
	m_nNextKey = 0;
	m_nCounterMotion = 0;
	m_bMotionEnd = false;
	m_ppModel = {};
}

//********************************************
// �X�V����
//********************************************
void CMotion::Update(void)
{
	// �ʒu�ƌ���
	D3DXVECTOR3 Diffpos, Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pos, rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float fRataFrame = 0.0f;

	if (m_nNextKey < m_nNumKey && m_bMotionEnd == false)
	{// ���[�V�����̑S�̃L�[���l���Ⴂ�ꍇ

		m_nCounterMotion++;	// ���[�V�����J�E���g

		// �S���f��(�p�[�c)�̍X�V
		for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
		{
			// �L�[��񂩂�ʒu�E�������Z�o
			Diffpos.x = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fPosX - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			Diffpos.y = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fPosY - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			Diffpos.z = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fPosZ - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
			Diffrot.x = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fRotX - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			Diffrot.y = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fRotY - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			Diffrot.z = m_MotionInfo[m_NowType].aKeyInfo[m_nNextKey].aKey[nCntModel].fRotZ - m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			fRataFrame = (float)(m_nCounterMotion) / (float)(m_MotionInfo[m_NowType].aKeyInfo[m_nKey].nFrame);

			// �p�[�c�̈ʒu�E������ݒ�
			pos.x = m_ppModel[nCntModel]->GetOffsetPos().x + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX + Diffpos.x * fRataFrame;
			pos.y = m_ppModel[nCntModel]->GetOffsetPos().y + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY + Diffpos.y * fRataFrame;
			pos.z = m_ppModel[nCntModel]->GetOffsetPos().z + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ + Diffpos.z * fRataFrame;
			rot.x = m_ppModel[nCntModel]->GetOffsetRot().x + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX + Diffrot.x * fRataFrame;
			rot.y = m_ppModel[nCntModel]->GetOffsetRot().y + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY + Diffrot.y * fRataFrame;
			rot.z = m_ppModel[nCntModel]->GetOffsetRot().z + m_MotionInfo[m_NowType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ + Diffrot.z * fRataFrame;

			m_ppModel[nCntModel]->SetPos(pos);
			m_ppModel[nCntModel]->SetRot(rot);
		}

		if (m_nCounterMotion >= m_MotionInfo[m_NowType].aKeyInfo[m_nKey].nFrame)
		{// �J�E���^�[���Đ��t���[���𒴂��鎞

			// ���[�V�����J�E���^�[������������
			m_nCounterMotion = 0;

			// �L�[����i�߂�
			m_nKey++;
			m_nNextKey++;

			if (m_nNextKey >= m_nNumKey)
			{// �L�[�̑����𒴂��Ă�����

				if (m_bLoop == true)
				{// ���[�v���郂�[�V�����̏ꍇ
					// ���̃L�[��0�ɖ߂�
					m_nNextKey = 0;
				}
				else if (m_bLoop == false)
				{// ���[�v���Ȃ����[�V�����̏ꍇ
					// �L�[��������
					m_nKey = 0;
					m_nNextKey = 1;

					// ���[�V�������I�������Ԃɂ���
					m_bMotionEnd = true;
				}

			}

			if (m_nKey >= m_nNumKey)
			{// �L�[�̑����𒴂��Ă�����
				// ���݂̃L�[��0�ɖ߂�
				m_nKey = 0;
			}
		}
	}
}

//********************************************
// �t�@�C���ǂݍ��ݏ���
//********************************************
void CMotion::Load(const char* Motionfile)
{
	// �f�o�b�N�\���̃|�C���^
	CDebugproc* pDebugproc;

	// ���݂̃L�[��
	int nCntKey = 0;

	// ���݂̃p�[�c
	int nCntParts = 0;

	// ���ݓǂݍ���ł��郂�[�V�����̃^�C�v
	int nType = -1;

	// ���[�v���邩�ǂ���
	int bLoop = 0;

	// ���݂̕��������J�E���g����ϐ�
	int nCnt = 0;

	// �ǂݍ��񂾕�����ۑ�����ϐ�
	char String = NULL;
	char aString[3] = {};

	int nResult = 0;

	// �t�@�C����ǂݍ���
	m_pfile = fopen(Motionfile, "r");

	if (m_pfile != NULL)
	{
		while (1)
		{
			// �������̃N���A
			memset(&String, 0, sizeof(String));

			// �擪�̕����̓ǂݍ���
			nResult = fscanf(m_pfile, "%c", &String);
			
			// �ǂݔ�΂�����
			if (String == '#')
			{// �R�����g��ǂݍ��񂾏ꍇ
				while (1)
				{
					nResult = fscanf(m_pfile, "%c", &String);

					if (String == '\n' || String == EOF)
					{
						break;
					}
				}

				continue;
			}
			else if (String == '\t')
			{// �^�u�̋󔒂�ǂݍ��񂾏ꍇ
				continue;
			}
			else if (String == '\n')
			{// ���s��ǂ񂾏ꍇ
				continue;
			}
			else if (String == ' ')
			{// �󔒂�ǂݍ��񂾏ꍇ
				continue;
			}

			// �ǂݍ��񂾕�����������
			m_aString[nCnt] = String;

			// �J�E���g����i�߂�
			nCnt++;

			if (strcmp(&m_aString[0], "SCRIPT") == 0)
			{
				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "MOTIONSET") == 0)
			{
				// ���[�V�����̎�ނ𑝂₷
				nType++;

				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "LOOP") == 0)
			{
				// =�Ƌ󔒕���ǂݍ���
				fgets(aString, 3, m_pfile);

				// ���[�V���������[�v���邩�ǂ�����ǂݍ���
				nResult = fscanf(m_pfile, "%d", &bLoop);

				if (bLoop == 0)
				{// ���[�v���Ȃ��ꍇ
					m_MotionInfo[nType].bLoop = false;
				}
				else
				{// ���[�v����ꍇ
					m_MotionInfo[nType].bLoop = true;
				}

				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "NUM_KEY") == 0)
			{
				// =�Ƌ󔒕���ǂݍ���
				fgets(aString, 3, m_pfile);

				// ���[�V�����̃L�[������ǂݍ���
				nResult = fscanf(m_pfile, "%d", &m_MotionInfo[nType].nNumKey);

				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "KEYSET") == 0)
			{
				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;

				// �L�[���̓ǂݍ��ݏ���
				KeysetLoad(nType, nCntKey, nCntParts);

				// �L�[�𑝂₷
				nCntKey++;
			}
			else if (strcmp(&m_aString[0], "END_MOTIONSET") == 0)
			{
				// �L�[���ŏ��ɖ߂�
				nCntKey = 0;

				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;
			}
			else if (strcmp(&m_aString[0], "END_SCRIPT") == 0)
			{
				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				// �J�E���g������������
				nCnt = 0;

				break;
			}

			if (nResult == NULL)
			{// �������ǂݍ��߂Ȃ������ꍇ
				break;
			}
			else if (nResult == EOF)
			{// �e�L�X�g�t�@�C����S�ēǂݐ؂����ꍇ
				break;
			}

		}

		// �t�@�C�������
		fclose(m_pfile);
	}
	else
	{
		// �f�o�b�N�\��
		pDebugproc->Print("���[�V�����t�@�C�����J���܂���ł���\n");
	}
}

//********************************************
// KEY�̓ǂݍ��ݏ���
//********************************************
void CMotion::KeysetLoad(int nType, int nCntKey, int nCntParts)
{
	// �ǂݍ��񂾕�����ۑ�����ϐ�
	char String = NULL;
	char aString[3] = {};

	int nResult = 0;

	int nCnt = 0;

	while (1)
	{
		// �������̃N���A
		memset(&String, 0, sizeof(String));

		// �擪�̕����̓ǂݍ���
		nResult = fscanf(m_pfile, "%c", &String);

		// �ǂݔ�΂�����
		if (String == '#')
		{// �R�����g��ǂݍ��񂾏ꍇ
			while (1)
			{
				nResult = fscanf(m_pfile, "%c", &String);

				if (String == '\n' || String == EOF)
				{
					break;
				}
			}

			continue;
		}
		else if (String == '\t')
		{// �^�u�̋󔒂�ǂݍ��񂾏ꍇ
			continue;
		}
		else if (String == '\n')
		{// ���s��ǂ񂾏ꍇ
			continue;
		}
		else if (String == ' ')
		{// �󔒂�ǂݍ��񂾏ꍇ
			continue;
		}

		// �ǂݍ��񂾕�����������
		m_aString[nCnt] = String;

		// �J�E���g����i�߂�
		nCnt++;

		if (strcmp(&m_aString[0], "FRAME") == 0)
		{
			// =�Ƌ󔒕���ǂݍ���
			fgets(aString, 3, m_pfile);

			// ���[�V�����̃t���[������ǂݍ���
			nResult = fscanf(m_pfile, "%d", &m_MotionInfo[nType].aKeyInfo[nCntKey].nFrame);

			// �������̃N���A
			memset(&m_aString[0], 0, sizeof(m_aString));

			// �J�E���g������������
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "KEY") == 0)
		{
			// �������̃N���A
			memset(&m_aString[0], 0, sizeof(m_aString));

			// �J�E���g������������
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "POS") == 0)
		{
			// =�Ƌ󔒕���ǂݍ���
			fgets(aString, 3, m_pfile);

			// ���[�V�����̈ʒu��ǂݍ���
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);

			// �������̃N���A
			memset(&m_aString[0], 0, sizeof(m_aString));

			// �J�E���g������������
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "ROT") == 0)
		{
			// =�Ƌ󔒕���ǂݍ���
			fgets(aString, 3, m_pfile);

			// ���[�V�����̌�����ǂݍ���
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
			nResult = fscanf(m_pfile, "%f", &m_MotionInfo[nType].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);

			// �������̃N���A
			memset(&m_aString[0], 0, sizeof(m_aString));

			// �J�E���g������������
			nCnt = 0;
		}
		else if (strcmp(&m_aString[0], "END_KEY") == 0)
		{
			// ���̃p�[�c�Ɉڂ�
			nCntParts++;

			// �������̃N���A
			memset(&m_aString[0], 0, sizeof(m_aString));

			// �J�E���g������������
			nCnt = 0;

			// ���̕�����ǂݍ���
			nResult = fscanf(m_pfile, "%s", &m_aString[0]);

			if (strcmp(&m_aString[0], "END_KEYSET") == 0)
			{// END_KEYSET�������ꍇ

				// �p�[�c���ŏ��ɖ߂�
				nCntParts = 0;

				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));

				break;
			}
			else
			{
				// �������̃N���A
				memset(&m_aString[0], 0, sizeof(m_aString));
			}
		}
	}
}

//********************************************
// ��ސݒ菈��
//********************************************
void CMotion::SetType(TYPE nType)
{
	// ���̃��[�V�����̏������݂̃��[�V�����ɐݒ�
	m_nNumKey = m_MotionInfo[nType].nNumKey;	// �L�[�̑���
	m_bLoop = m_MotionInfo[nType].bLoop;		// ���[�v���邩�ǂ���
	m_bMotionEnd = false;							// ���[�V�������I����Ă��Ȃ���Ԃɂ���

	if (m_bLoop == false)
	{// ���[�v���Ȃ����[�V�����̏ꍇ
		m_nKey = 0;										// ���݂̃L�[No.
		m_nNextKey = m_nKey + 1;						// ���̃L�[No.
		m_nCounterMotion = 0;							// �J�E���g������������
	}
	else if (m_bLoop == true)
	{// ���[�v���郂�[�V�����̏ꍇ
		if (m_NowType != nType)
		{// ���݂̃��[�V�����Ǝ�ނ��Ⴄ�ꍇ
			m_nCounterMotion = 0;							// �J�E���g������������
			m_nKey = 0;									// ���݂̃L�[No.
			m_nNextKey = m_nKey + 1;					// ���̃L�[No.
		}
	}

	// ���[�V�����̎�ނ̐ݒ�
	m_NowType = nType;

}

//********************************************
// �ݒ菈��
//********************************************
void CMotion::SetModel(CModel** apModel, int nNumParts)
{
	m_ppModel = apModel;
	m_nNumParts = nNumParts;
}

//********************************************
// ���[�V�������I��邩�ǂ����̏���
//********************************************
bool CMotion::IsFinish(void)
{
	return m_bMotionEnd;
}
