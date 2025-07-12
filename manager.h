//======================================================
// 
// マネージャー処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"		// メイン処理
#include "renderer.h"	// レンダラー処理
#include "input.h"		// 入力処理
#include "sound.h"		// サウンド処理
#include "player.h"		// プレイヤー処理
#include "bullet.h"		// 弾処理
#include "background.h"	// 2D背景処理
#include "explosion.h"	// 爆発処理
#include "enemy.h"		// 2D敵処理
#include "timer.h"		// タイマー処理
#include "score.h"		// スコア処理
#include "effect.h"		// エフェクト処理
#include "camera.h"		// カメラ処理
#include "light.h"		// ライト処理
#include "object3D.h"	// オブジェクト3Dの処理
#include "objectX.h"	// オブジェクトXの処理
#include "billboard.h"	// ビルボードの処理
#include "texture.h"	// テクスチャ処理
#include "sky.h"		// 空の処理
#include "meshfield.h"	// メッシュフィールドの処理

//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:
	// コンストラクタ
	CManager();
	// デストラクタ
	~CManager();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
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
	// 静的メンバ変数
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