//======================================================
// 
// �I�u�W�F�N�g2D����
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// �I�u�W�F�N�g2D�N���X
//*****************************************************************************
class CObject2D:public CObject
{
public:

	// �e�N�X�`���̍\����
	typedef struct
	{
		D3DXVECTOR3 Pos;	// �ʒu
		D3DXVECTOR3 Rot;	// �p�x
		float fWidth;		// ����
		float fHeight;		// �c��
		D3DXCOLOR Col;		// �F
	}Texture;

	// �R���X�g���N�^
	CObject2D(int nPriority = 7);
	// �f�X�g���N�^
	virtual ~CObject2D();

	// �����o�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void AlphaDraw(void);
	void SetTextureAnim(const int nCountAnim, const int nPatternAnim);	// �e�N�X�`���̃A�j���[�V��������
	void SetBGScroll(int nCount);										// �w�i�̃X�N���[������
	Texture* GetTexture(void) { return &m_Texture; };					// �e�N�X�`�����̎擾
	D3DXVECTOR3 GetPos(void) { return m_Texture.Pos; };					// �ʒu���̎擾

private:

	// �����o�ϐ�
	Texture m_Texture;						// �e�N�X�`���̍\����
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	int m_nCountAnim;						// �A�j���[�V�����̃J�E���g
	int m_nPatternAnim;						// �A�j���[�V�����̃p�^�[��
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̊p�x
	float m_aPosTexU;

};

#endif _OBJECT2D_H_