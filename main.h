//======================================================
// 
// window表示処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _MAIN_H_ // このマクロ定義がされていなかったら
#define _MAIN_H_

#include <windows.h>
#include <crtdbg.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"	// キーボードの入力処理用
#include "xaudio2.h"
#include "Xinput.h"	// ジョイパッドの入力処理用
#include "stdio.h"

// ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib") // ジョイパッド処理に必要

// マクロ定義
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "LASER AND TRAVELER"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// 頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; // 頂点座標
	float rhw;       // 座標変換用係数(1.0fで固定)
	D3DCOLOR col;    // 頂点カラー
	D3DXVECTOR2 tex; // テクスチャ座標
}VERTEX_2D;

// 頂点情報[3D]をの構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; // 頂点座標
	D3DXVECTOR3 nor; // 法線ベクトル
	D3DCOLOR col;    // 頂点カラー
	D3DXVECTOR2 tex; // テクスチャ座標
}VERTEX_3D;

#endif _MAIN_H_