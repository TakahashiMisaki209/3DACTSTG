//======================================================
// 
// �e�L�X�g�t�@�C���̏���
// Author:Takahashi Misaki
// 
//======================================================

#include "txtfile.h"
#include "debugproc.h"
#include "motion.h"

//********************************************
// �R���X�g���N�^
//********************************************
CTxtfile::CTxtfile()
{
	m_pfile = NULL;
	m_aString[MAX_CHARACTER - 1] = {};
}

//********************************************
// �f�X�g���N�^
//********************************************
CTxtfile::~CTxtfile()
{
}

//********************************************
// �t�@�C���ǂݍ��ݏ���
//********************************************
void CTxtfile::Load(void)
{
	//// �f�o�b�N�\���̃|�C���^
	//CDebugproc* pDebugproc;

	//// ���[�V�����̃|�C���^
	//CMotion::MOTION* pMotion;

	//// ���[�V�����̏����擾
	//pMotion = CMotion::GetMotion();

	//// ���݂̃L�[��
	//int nCntKey = 0;

	//// ���݂̃p�[�c
	//int nCntParts = 0;

	//// ���ݓǂݍ���ł��郂�[�V�����̃^�C�v
	//int nType = 0;

	//// ���[�v���邩�ǂ���
	//int bLoop = 0;

	//int nResult = 0;

	//// �t�@�C����ǂݍ���
	//m_pfile = fopen("data/MOTION/motion.txt", "r");

	//if (m_pfile != NULL)
	//{
	//	while (1)
	//	{
	//		// �������̃N���A
	//		memset(&m_aString[0], 0, sizeof(m_aString));

	//		// �擪�̕����̓ǂݍ���
	//		nResult = fscanf(m_pfile, "%s", &m_aString[0]);

	//		if (m_aString == "MOTIONSET")
	//		{
	//		}
	//		else if (m_aString == "MOTION_TYPE")
	//		{
	//			// ���[�V�����̎�ނ�ǂݍ���
	//			nResult = fscanf(m_pfile, "%d", &pMotion->nNowMotionType);

	//			nType = pMotion->nNowMotionType;
	//		}
	//		else if (m_aString == "LOOP")
	//		{
	//			// ���[�V���������[�v���邩�ǂ�����ǂݍ���
	//			nResult = fscanf(m_pfile, "%d", &bLoop);

	//			if (bLoop == 0)
	//			{// ���[�v���Ȃ��ꍇ
	//				pMotion->MotionInfo[nType].bLoop = false;
	//			}
	//			else if (bLoop == 1)
	//			{// ���[�v����ꍇ
	//				pMotion->MotionInfo[nType].bLoop = true;
	//			}

	//			pMotion->bLoop = pMotion->MotionInfo[nType].bLoop;
	//		}
	//		else if (m_aString == "NUM_KEY")
	//		{
	//			// ���[�V�����̃L�[������ǂݍ���
	//			nResult = fscanf(m_pfile, "%d", &pMotion->MotionInfo[nType].nNumKey);
	//			pMotion->nNumKey = pMotion->MotionInfo[nType].nNumKey;

	//		}
	//		else if (m_aString == "KEYSET")
	//		{
	//			// ���݂̃L�[���m�F
	//			int aaa = nCntKey;

	//		}
	//		else if (m_aString == "FRAME")
	//		{
	//			// ���[�V�����̃t���[������ǂݍ���
	//			nResult = fscanf(m_pfile, "%d", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].nFrame);

	//		}
	//		else if (m_aString == "KEY")
	//		{
	//			// ���݂̃p�[�c���m�F
	//			int bbb = nCntParts;
	//		
	//		}
	//		else if (m_aString == "POS")
	//		{
	//			// ���[�V�����̈ʒu��ǂݍ���
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosX);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosY);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ);

	//		}
	//		else if (m_aString == "ROT")
	//		{
	//			// ���[�V�����̌�����ǂݍ���
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fRotX);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fRotY);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ);

	//		}
	//		else if (m_aString == "END_KEY")
	//		{
	//			// ���̃p�[�c�Ɉڂ�
	//			nCntParts++;

	//		}
	//		else if (m_aString == "END_KEYSET")
	//		{
	//			// ���̃L�[�Ɉڂ�
	//			nCntKey++;

	//			// �p�[�c���ŏ��ɖ߂�
	//			nCntParts = 0;
	//		}
	//		else if (m_aString == "END_MOTIONSET")
	//		{
	//			// �L�[���ŏ��ɖ߂�
	//			nCntKey = 0;
	//		}


	//		if (nResult == NULL)
	//		{// �������ǂݍ��߂Ȃ������ꍇ
	//			break;
	//		}
	//		else if (nResult == EOF)
	//		{// �e�L�X�g�t�@�C����S�ēǂݐ؂����ꍇ
	//			break;
	//		}

	//	}

	//	// �t�@�C�������
	//	fclose(m_pfile);
	//}
	//else
	//{
	//	// �f�o�b�N�\��
	//	pDebugproc->Print("�t�@�C�����J���܂���ł���\n");
	//}
}

//********************************************
// �t�@�C�������o������
//********************************************
void CTxtfile::Save(void)
{
	//// �f�o�b�N�\���̃|�C���^
	//CDebugproc* pDebugproc;

	//// ���[�V�����̃|�C���^
	//CMotion::MOTION* pMotion;

	//// ���[�V�����̏����擾
	//pMotion = CMotion::GetMotion();

	//// ���݂̃L�[��
	//int nCntKey = 0;

	//// ���݂̃p�[�c
	//int nCntParts = 0;

	//// �����o�����[�V�����̃^�C�v
	//int nType = pMotion->nNowMotionType;

	//// �\������X�e�[�W�̔ԍ�
	//m_pfile = fopen("data/MOTION/motion.txt", "w");

	//if (m_pfile != NULL)
	//{
	//	while (1)
	//	{
	//		// ���[�V������񏑂��o��
	//		fprintf(m_pfile, "MOTIONSET\n");

	//		// ���[�V�����̃^�C�v�����o��
	//		fprintf(m_pfile, "MOTION_TYPE ");

	//		fprintf(m_pfile, "%d\n", nType);

	//		// ���[�V���������[�v���邩�ǂ����̏����o��
	//		fprintf(m_pfile, "LOOP \n");

	//		fprintf(m_pfile, "%d\n", pMotion->MotionInfo[nType].bLoop);

	//		// �L�[�����̏����o��
	//		fprintf(m_pfile, "LOOP \n");

	//		fprintf(m_pfile, "%d\n", pMotion->MotionInfo[nType].bLoop);

	//		// ���[�V������񏑂��o��
	//		fprintf(m_pfile, "MOTIONSET\n");

	//		fprintf(m_pfile, "\nPOS\n");

	//		// POS�̒l�����o��
	//		fprintf(m_pfile, "%f\n", pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosX);
	//		fprintf(m_pfile, "%f\n", pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosY);
	//		fprintf(m_pfile, "%f\n", pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ);

	//		// �����������o��
	//		fprintf(m_pfile, "\nENDTARGET\n\n");
	//	}

	//	// �t�@�C�������
	//	fclose(m_pfile);
	//}
	//else
	//{
	//	// �f�o�b�N�\��
	//	pDebugproc->Print("�t�@�C�����J���܂���ł���\n");
	//}
}
