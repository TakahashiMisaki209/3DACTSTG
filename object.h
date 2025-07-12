//======================================================
// 
// オブジェクト処理
// Author:Takahashi Misaki
// 
//======================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

// マクロ定義
#define MAX_PRIO (8)	// 優先順位の最大数

#include "main.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CObject
{
public:

	// オブジェクトの種類	
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_EFFECT,
		TYPE_TIMER,
		TYPE_MAX
	}TYPE;

	// コンストラクタ(オーバーロード)
	CObject(int nPriority = 0);
	// デストラクタ
	virtual ~CObject();

	// メンバ関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual D3DXVECTOR3 GetPos(void) { return m_Pos; }
	void SetTYPE(TYPE type);
	TYPE GetTYPE(void) { return m_type; }
	CObject* GetNext(void) { return m_pNext; }
	CObject* ObjectDeath(CObject* pObject);

	// 静的メンバ関数
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }
	static int GetNumAll(void) { return m_nNumAll; }

protected:
	void Release(void);

private:
	// メンバ変数
	CObject* m_pPrev;	// 前のオブジェクトへのポインタ
	CObject* m_pNext;	// 次のオブジェクトのポインタ
	int m_nID;			// 自分自身のID
	TYPE m_type;		// オブジェクトの種類
	int m_nPriority;	// 優先順位の位置
	bool m_bDeath;		// 死亡フラグ

	// 静的メンバ変数
	static CObject* m_pTop[MAX_PRIO];		// 先頭のオブジェクトへのポインタ
	static CObject* m_pCur[MAX_PRIO];		// 最後尾のオブジェクトへのポインタ
	static int m_nNumAll;					// オブジェクトの総数
	D3DXVECTOR3 m_Pos;						// オブジェクトの位置
};

#endif _OBJECT_H_