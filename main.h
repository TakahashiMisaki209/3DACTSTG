//======================================================
// 
// window�\������
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _MAIN_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_

#include <windows.h>
#include <crtdbg.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"	// �L�[�{�[�h�̓��͏����p
#include "xaudio2.h"
#include "Xinput.h"	// �W���C�p�b�h�̓��͏����p
#include "stdio.h"

// ���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib") // �W���C�p�b�h�����ɕK�v

// �}�N����`
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "LASER AND TRAVELER"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// ���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; // ���_���W
	float rhw;       // ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;    // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
}VERTEX_2D;

// ���_���[3D]���̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; // ���_���W
	D3DXVECTOR3 nor; // �@���x�N�g��
	D3DCOLOR col;    // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
}VERTEX_3D;

#endif _MAIN_H_