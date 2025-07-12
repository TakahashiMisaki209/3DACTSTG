//======================================================
// 
// レンダリング処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "object.h"
#include "debugproc.h"

//*****************************************************************************
// レンダラークラス
//*****************************************************************************
class CRenderer
{
public:

	// コンストラクタ
	CRenderer();
	// デストラクタ
	~CRenderer();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	// メンバ変数
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	// 静的メンバ変数
	static CDebugproc* m_pDebugproc;

};

#endif _RENDERER_H_