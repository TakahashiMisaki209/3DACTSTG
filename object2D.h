//======================================================
// 
// オブジェクト2D処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// オブジェクト2Dクラス
//*****************************************************************************
class CObject2D:public CObject
{
public:

	// テクスチャの構造体
	typedef struct
	{
		D3DXVECTOR3 Pos;	// 位置
		D3DXVECTOR3 Rot;	// 角度
		float fWidth;		// 横幅
		float fHeight;		// 縦幅
		D3DXCOLOR Col;		// 色
	}Texture;

	// コンストラクタ
	CObject2D(int nPriority = 7);
	// デストラクタ
	virtual ~CObject2D();

	// メンバ関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void AlphaDraw(void);
	void SetTextureAnim(const int nCountAnim, const int nPatternAnim);	// テクスチャのアニメーション処理
	void SetBGScroll(int nCount);										// 背景のスクロール処理
	Texture* GetTexture(void) { return &m_Texture; };					// テクスチャ情報の取得
	D3DXVECTOR3 GetPos(void) { return m_Texture.Pos; };					// 位置情報の取得

private:

	// メンバ変数
	Texture m_Texture;						// テクスチャの構造体
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	int m_nCountAnim;						// アニメーションのカウント
	int m_nPatternAnim;						// アニメーションのパターン
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の角度
	float m_aPosTexU;

};

#endif _OBJECT2D_H_