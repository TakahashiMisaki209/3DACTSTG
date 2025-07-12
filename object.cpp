//======================================================
// 
// オブジェクト処理
// Author:Takahashi Misaki
// 
//======================================================

#include "object.h"
#include "manager.h"

CObject* CObject::m_pTop[MAX_PRIO] = {};
CObject* CObject::m_pCur[MAX_PRIO] = {};
int CObject::m_nNumAll = -1;

//********************************************
// コンストラクタ(オーバーロード)
//********************************************
CObject::CObject(int nPriority)
{
	// 各変数の初期化
	m_nID = -1;
	m_type = TYPE_NONE;
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_nPriority = nPriority;
	m_bDeath = false;

	// 前のポインタに最後尾のポインタを代入する
	m_pPrev = m_pCur[nPriority];

	if (m_pTop[nPriority] == nullptr)
	{// 先頭がいない場合
		// 前のポインタをNULLにする
		m_pPrev = nullptr;

		// 先頭に代入する
		m_pTop[nPriority] = this;
	}
	else
	{// 既にいる場合
		// 前回の次のポインタに自身を代入する
		m_pCur[nPriority]->m_pNext = this;
	}

	// 最後尾のポインタに代入する
	m_pCur[nPriority] = this;

	// 1つづつ増やす
	m_nID++;
	m_nNumAll++;
}

//********************************************
// デストラクタ
//********************************************
CObject::~CObject()
{
}

//********************************************
// オブジェクト破棄
//********************************************
void CObject::Release(void)
{
	// 現在のオブジェクトの死亡フラグを立てる
	m_bDeath = true;
}

//********************************************
// 全てのオブジェクト破棄
//********************************************
void CObject::ReleaseAll(void)
{
	for (int nCntPrio = 0; nCntPrio < MAX_PRIO; nCntPrio++)
	{
		// 先頭のポインタを代入する
		CObject* pObject = m_pTop[nCntPrio];

		while (pObject != nullptr)
		{// オブジェクトが入っている場合

			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;

			// 終了処理
			pObject->Uninit();

			// オブジェクトの破棄
			delete pObject;

			// 次のオブジェクトを代入する
			pObject = pObjectNext;
		}
	}
}

//********************************************
// 全てのオブジェクト更新
//********************************************
void CObject::UpdateAll(void)
{
	for (int nCntPrio = 0; nCntPrio < MAX_PRIO; nCntPrio++)
	{
		// 先頭のポインタを代入する
		CObject* pObject = m_pTop[nCntPrio];

		while (pObject != nullptr)
		{// オブジェクトが入っている場合
			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;

			// 更新処理
			pObject->Update();

			// 次のオブジェクトを代入する
			pObject = pObjectNext;
		}

		// 先頭のポインタを代入する
		CObject* pObj = m_pTop[nCntPrio];

		while (pObj != nullptr)
		{// オブジェクトが入っている場合
			// 次のオブジェクトを保存
			CObject* pObjNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{// 死亡フラグが立っている時
				// オブジェクトをリストから削除して破棄
				pObj = pObj->ObjectDeath(pObj);
			}

			// 次のオブジェクトを代入する
			pObj = pObjNext;
		}
	}
}

//********************************************
// 全てのオブジェクト描画
//********************************************
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();

	// カメラ設定
	pCamera->SetCamera();

	for (int nCntPrio = 0; nCntPrio < MAX_PRIO; nCntPrio++)
	{
		// 先頭のポインタを代入する
		CObject* pObject = m_pTop[nCntPrio];

		while (pObject != nullptr)
		{// オブジェクトが入っている場合

			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;

			// 描画処理
			pObject->Draw();

			// 次のオブジェクトを代入する
			pObject = pObjectNext;
		}
	}

}

//********************************************
// オブジェクトの種類の設定処理
//********************************************
void CObject::SetTYPE(TYPE type)
{
	m_type = type;
}

//********************************************
// 死亡フラグが立ったオブジェクトの破棄
//********************************************
CObject* CObject::ObjectDeath(CObject* pObject)
{
	if (m_pPrev != nullptr)
	{// 前にオブジェクトがある場合
		// 前のオブジェクトの次を自身の次のオブジェクトに変更する
		m_pPrev->m_pNext = m_pNext;
	}
	else
	{// 先頭が消える場合
		// 自身の次のオブジェクトを先頭に変更する
		m_pTop[m_nPriority] = this->m_pNext;
	}

	if (m_pNext != nullptr)
	{// 次にオブジェクトがある場合
		// 次のオブジェクトの前を自身の前のオブジェクトに変更する
		m_pNext->m_pPrev = m_pPrev;
	}
	else
	{// 最後尾が消える場合
		// 自身の前のオブジェクトを最後尾に変更する
		m_pCur[m_nPriority] = this->m_pPrev;
	}

	// ポインタを初期化する
	m_pPrev = nullptr;
	m_pNext = nullptr;

	// 総数を減らす
	m_nNumAll--;

	// オブジェクトの破棄
	delete pObject;

	return pObject;
}