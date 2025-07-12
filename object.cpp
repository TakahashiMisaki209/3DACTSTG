//======================================================
// 
// �I�u�W�F�N�g����
// Author:Takahashi Misaki
// 
//======================================================

#include "object.h"
#include "manager.h"

CObject* CObject::m_pTop[MAX_PRIO] = {};
CObject* CObject::m_pCur[MAX_PRIO] = {};
int CObject::m_nNumAll = -1;

//********************************************
// �R���X�g���N�^(�I�[�o�[���[�h)
//********************************************
CObject::CObject(int nPriority)
{
	// �e�ϐ��̏�����
	m_nID = -1;
	m_type = TYPE_NONE;
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_nPriority = nPriority;
	m_bDeath = false;

	// �O�̃|�C���^�ɍŌ���̃|�C���^��������
	m_pPrev = m_pCur[nPriority];

	if (m_pTop[nPriority] == nullptr)
	{// �擪�����Ȃ��ꍇ
		// �O�̃|�C���^��NULL�ɂ���
		m_pPrev = nullptr;

		// �擪�ɑ������
		m_pTop[nPriority] = this;
	}
	else
	{// ���ɂ���ꍇ
		// �O��̎��̃|�C���^�Ɏ��g��������
		m_pCur[nPriority]->m_pNext = this;
	}

	// �Ō���̃|�C���^�ɑ������
	m_pCur[nPriority] = this;

	// 1�Â��₷
	m_nID++;
	m_nNumAll++;
}

//********************************************
// �f�X�g���N�^
//********************************************
CObject::~CObject()
{
}

//********************************************
// �I�u�W�F�N�g�j��
//********************************************
void CObject::Release(void)
{
	// ���݂̃I�u�W�F�N�g�̎��S�t���O�𗧂Ă�
	m_bDeath = true;
}

//********************************************
// �S�ẴI�u�W�F�N�g�j��
//********************************************
void CObject::ReleaseAll(void)
{
	for (int nCntPrio = 0; nCntPrio < MAX_PRIO; nCntPrio++)
	{
		// �擪�̃|�C���^��������
		CObject* pObject = m_pTop[nCntPrio];

		while (pObject != nullptr)
		{// �I�u�W�F�N�g�������Ă���ꍇ

			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �I������
			pObject->Uninit();

			// �I�u�W�F�N�g�̔j��
			delete pObject;

			// ���̃I�u�W�F�N�g��������
			pObject = pObjectNext;
		}
	}
}

//********************************************
// �S�ẴI�u�W�F�N�g�X�V
//********************************************
void CObject::UpdateAll(void)
{
	for (int nCntPrio = 0; nCntPrio < MAX_PRIO; nCntPrio++)
	{
		// �擪�̃|�C���^��������
		CObject* pObject = m_pTop[nCntPrio];

		while (pObject != nullptr)
		{// �I�u�W�F�N�g�������Ă���ꍇ
			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �X�V����
			pObject->Update();

			// ���̃I�u�W�F�N�g��������
			pObject = pObjectNext;
		}

		// �擪�̃|�C���^��������
		CObject* pObj = m_pTop[nCntPrio];

		while (pObj != nullptr)
		{// �I�u�W�F�N�g�������Ă���ꍇ
			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{// ���S�t���O�������Ă��鎞
				// �I�u�W�F�N�g�����X�g����폜���Ĕj��
				pObj = pObj->ObjectDeath(pObj);
			}

			// ���̃I�u�W�F�N�g��������
			pObj = pObjNext;
		}
	}
}

//********************************************
// �S�ẴI�u�W�F�N�g�`��
//********************************************
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();

	// �J�����ݒ�
	pCamera->SetCamera();

	for (int nCntPrio = 0; nCntPrio < MAX_PRIO; nCntPrio++)
	{
		// �擪�̃|�C���^��������
		CObject* pObject = m_pTop[nCntPrio];

		while (pObject != nullptr)
		{// �I�u�W�F�N�g�������Ă���ꍇ

			// ���̃I�u�W�F�N�g��ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �`�揈��
			pObject->Draw();

			// ���̃I�u�W�F�N�g��������
			pObject = pObjectNext;
		}
	}

}

//********************************************
// �I�u�W�F�N�g�̎�ނ̐ݒ菈��
//********************************************
void CObject::SetTYPE(TYPE type)
{
	m_type = type;
}

//********************************************
// ���S�t���O���������I�u�W�F�N�g�̔j��
//********************************************
CObject* CObject::ObjectDeath(CObject* pObject)
{
	if (m_pPrev != nullptr)
	{// �O�ɃI�u�W�F�N�g������ꍇ
		// �O�̃I�u�W�F�N�g�̎������g�̎��̃I�u�W�F�N�g�ɕύX����
		m_pPrev->m_pNext = m_pNext;
	}
	else
	{// �擪��������ꍇ
		// ���g�̎��̃I�u�W�F�N�g��擪�ɕύX����
		m_pTop[m_nPriority] = this->m_pNext;
	}

	if (m_pNext != nullptr)
	{// ���ɃI�u�W�F�N�g������ꍇ
		// ���̃I�u�W�F�N�g�̑O�����g�̑O�̃I�u�W�F�N�g�ɕύX����
		m_pNext->m_pPrev = m_pPrev;
	}
	else
	{// �Ō����������ꍇ
		// ���g�̑O�̃I�u�W�F�N�g���Ō���ɕύX����
		m_pCur[m_nPriority] = this->m_pPrev;
	}

	// �|�C���^������������
	m_pPrev = nullptr;
	m_pNext = nullptr;

	// ���������炷
	m_nNumAll--;

	// �I�u�W�F�N�g�̔j��
	delete pObject;

	return pObject;
}