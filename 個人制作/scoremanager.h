//=================================================
//
// [ScoreManager.h] : スコアマネージャーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _SCOREMANAGER_H_
#define _SCOREMANAGER_H_

#include "main.h"
#include "score.h"

//**************************************************
// スコアを管理するクラスを定義
//**************************************************
class CScoreManager
{
public:

		~CScoreManager();

		HRESULT Init(D3DXVECTOR3 pos);
		void Uninit(void);
		void Update(void);
		void Draw(void);

		// ゲッター
		CScore* GetScore(void) { return m_pScore; }

		static CScoreManager* Instance(void);

	private:

		CScoreManager();						// 格納コンストラクタ
		static CScoreManager* m_pInstance;		// シングルトン変数
		CScore* m_pScore;						// プレイヤーのポインタ

	};
#endif