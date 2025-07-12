//======================================================
// 
// テキストファイルの処理
// Author:Takahashi Misaki
// 
//======================================================

#ifndef _TXTFILE_H_
#define _TXTFILE_H_

#include "main.h"

// マクロ定義
#define MAX_CHARACTER (256)

//*****************************************************************************
// テキストファイルクラス
//*****************************************************************************
class CTxtfile
{
public:
	// コンストラクタ
	CTxtfile();
	// デストラクタ
	~CTxtfile();

	// メンバ関数
	void Load(void);
	void Save(void);

private:
	// メンバ変数
	FILE* m_pfile;
	char m_aString[MAX_CHARACTER];

	// 静的メンバ変数

};

#endif
