//======================================================
// 
// �}�l�[�W���[����
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"		// ���C������
#include "renderer.h"	// �����_���[����
#include "input.h"		// ���͏���
#include "sound.h"		// �T�E���h����
#include "player.h"		// �v���C���[����
#include "bullet.h"		// �e����
#include "background.h"	// 2D�w�i����
#include "explosion.h"	// ��������
#include "enemy.h"		// 2D�G����
#include "timer.h"		// �^�C�}�[����
#include "score.h"		// �X�R�A����
#include "effect.h"		// �G�t�F�N�g����
#include "camera.h"		// �J��������
#include "light.h"		// ���C�g����
#include "object3D.h"	// �I�u�W�F�N�g3D�̏���
#include "objectX.h"	// �I�u�W�F�N�gX�̏���
#include "billboard.h"	// �r���{�[�h�̏���
#include "texture.h"	// �e�N�X�`������
#include "sky.h"		// ��̏���
#include "meshfield.h"	// ���b�V���t�B�[���h�̏���

//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:
	// �R���X�g���N�^
	CManager();
	// �f�X�g���N�^
	~CManager();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CRenderer* GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard* GetInputKeyboard(void) { return m_pkeyboard; };
	static CInputMouse* GetInputMouse(void) { return m_pMouse; }
	static CSound* GetSound(void) { return m_pSound; };
	static CCamera* GetCamera(void){ return m_pCamera; };
	static CLight* GetLight(void) { return m_pLight; };
	static CTexture* GetTexture(void) { return m_pTexture; };
	static CPlayer* GetPlayer(void) { return m_pPlayer; };
	static CObject3D* GetObject3D(void) { return m_pObject3D; };
	static CSky* GetSky(void) { return m_Sky; };
	static CMeshfield* GetMeshfield(void) { return m_pMeshfield; };

private:
	// �ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;
	static CInputKeyboard* m_pkeyboard;
	static CInputMouse* m_pMouse;
	static CSound* m_pSound;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CTexture* m_pTexture;
	static CPlayer* m_pPlayer;
	static CObject3D* m_pObject3D;
	static CSky* m_Sky;
	static CMeshfield* m_pMeshfield;

};

#endif _MANAGER_H_