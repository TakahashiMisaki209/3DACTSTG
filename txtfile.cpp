//======================================================
// 
// テキストファイルの処理
// Author:Takahashi Misaki
// 
//======================================================

#include "txtfile.h"
#include "debugproc.h"
#include "motion.h"

//********************************************
// コンストラクタ
//********************************************
CTxtfile::CTxtfile()
{
	m_pfile = NULL;
	m_aString[MAX_CHARACTER - 1] = {};
}

//********************************************
// デストラクタ
//********************************************
CTxtfile::~CTxtfile()
{
}

//********************************************
// ファイル読み込み処理
//********************************************
void CTxtfile::Load(void)
{
	//// デバック表示のポインタ
	//CDebugproc* pDebugproc;

	//// モーションのポインタ
	//CMotion::MOTION* pMotion;

	//// モーションの情報を取得
	//pMotion = CMotion::GetMotion();

	//// 現在のキー数
	//int nCntKey = 0;

	//// 現在のパーツ
	//int nCntParts = 0;

	//// 現在読み込んでいるモーションのタイプ
	//int nType = 0;

	//// ループするかどうか
	//int bLoop = 0;

	//int nResult = 0;

	//// ファイルを読み込む
	//m_pfile = fopen("data/MOTION/motion.txt", "r");

	//if (m_pfile != NULL)
	//{
	//	while (1)
	//	{
	//		// メモリのクリア
	//		memset(&m_aString[0], 0, sizeof(m_aString));

	//		// 先頭の文字の読み込み
	//		nResult = fscanf(m_pfile, "%s", &m_aString[0]);

	//		if (m_aString == "MOTIONSET")
	//		{
	//		}
	//		else if (m_aString == "MOTION_TYPE")
	//		{
	//			// モーションの種類を読み込み
	//			nResult = fscanf(m_pfile, "%d", &pMotion->nNowMotionType);

	//			nType = pMotion->nNowMotionType;
	//		}
	//		else if (m_aString == "LOOP")
	//		{
	//			// モーションがループするかどうかを読み込み
	//			nResult = fscanf(m_pfile, "%d", &bLoop);

	//			if (bLoop == 0)
	//			{// ループしない場合
	//				pMotion->MotionInfo[nType].bLoop = false;
	//			}
	//			else if (bLoop == 1)
	//			{// ループする場合
	//				pMotion->MotionInfo[nType].bLoop = true;
	//			}

	//			pMotion->bLoop = pMotion->MotionInfo[nType].bLoop;
	//		}
	//		else if (m_aString == "NUM_KEY")
	//		{
	//			// モーションのキー総数を読み込み
	//			nResult = fscanf(m_pfile, "%d", &pMotion->MotionInfo[nType].nNumKey);
	//			pMotion->nNumKey = pMotion->MotionInfo[nType].nNumKey;

	//		}
	//		else if (m_aString == "KEYSET")
	//		{
	//			// 現在のキーを確認
	//			int aaa = nCntKey;

	//		}
	//		else if (m_aString == "FRAME")
	//		{
	//			// モーションのフレーム数を読み込み
	//			nResult = fscanf(m_pfile, "%d", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].nFrame);

	//		}
	//		else if (m_aString == "KEY")
	//		{
	//			// 現在のパーツを確認
	//			int bbb = nCntParts;
	//		
	//		}
	//		else if (m_aString == "POS")
	//		{
	//			// モーションの位置を読み込み
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosX);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosY);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ);

	//		}
	//		else if (m_aString == "ROT")
	//		{
	//			// モーションの向きを読み込み
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fRotX);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fRotY);
	//			nResult = fscanf(m_pfile, "%f", &pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ);

	//		}
	//		else if (m_aString == "END_KEY")
	//		{
	//			// 次のパーツに移る
	//			nCntParts++;

	//		}
	//		else if (m_aString == "END_KEYSET")
	//		{
	//			// 次のキーに移る
	//			nCntKey++;

	//			// パーツを最初に戻す
	//			nCntParts = 0;
	//		}
	//		else if (m_aString == "END_MOTIONSET")
	//		{
	//			// キーを最初に戻す
	//			nCntKey = 0;
	//		}


	//		if (nResult == NULL)
	//		{// 正しく読み込めなかった場合
	//			break;
	//		}
	//		else if (nResult == EOF)
	//		{// テキストファイルを全て読み切った場合
	//			break;
	//		}

	//	}

	//	// ファイルを閉じる
	//	fclose(m_pfile);
	//}
	//else
	//{
	//	// デバック表示
	//	pDebugproc->Print("ファイルを開けませんでした\n");
	//}
}

//********************************************
// ファイル書き出し処理
//********************************************
void CTxtfile::Save(void)
{
	//// デバック表示のポインタ
	//CDebugproc* pDebugproc;

	//// モーションのポインタ
	//CMotion::MOTION* pMotion;

	//// モーションの情報を取得
	//pMotion = CMotion::GetMotion();

	//// 現在のキー数
	//int nCntKey = 0;

	//// 現在のパーツ
	//int nCntParts = 0;

	//// 書き出すモーションのタイプ
	//int nType = pMotion->nNowMotionType;

	//// 表示するステージの番号
	//m_pfile = fopen("data/MOTION/motion.txt", "w");

	//if (m_pfile != NULL)
	//{
	//	while (1)
	//	{
	//		// モーション情報書き出し
	//		fprintf(m_pfile, "MOTIONSET\n");

	//		// モーションのタイプ書き出し
	//		fprintf(m_pfile, "MOTION_TYPE ");

	//		fprintf(m_pfile, "%d\n", nType);

	//		// モーションがループするかどうかの書き出し
	//		fprintf(m_pfile, "LOOP \n");

	//		fprintf(m_pfile, "%d\n", pMotion->MotionInfo[nType].bLoop);

	//		// キー総数の書き出し
	//		fprintf(m_pfile, "LOOP \n");

	//		fprintf(m_pfile, "%d\n", pMotion->MotionInfo[nType].bLoop);

	//		// モーション情報書き出し
	//		fprintf(m_pfile, "MOTIONSET\n");

	//		fprintf(m_pfile, "\nPOS\n");

	//		// POSの値書き出し
	//		fprintf(m_pfile, "%f\n", pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosX);
	//		fprintf(m_pfile, "%f\n", pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosY);
	//		fprintf(m_pfile, "%f\n", pMotion->MotionInfo[nType].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ);

	//		// 文末を書き出し
	//		fprintf(m_pfile, "\nENDTARGET\n\n");
	//	}

	//	// ファイルを閉じる
	//	fclose(m_pfile);
	//}
	//else
	//{
	//	// デバック表示
	//	pDebugproc->Print("ファイルを開けませんでした\n");
	//}
}
