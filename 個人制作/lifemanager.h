//=================================================
//
// [LifeManager.h]	// ライフマネージャーのヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _LIFEMANAGER_H_
#define _LIFEMANAGER_H_

#include "main.h"
#include "life.h"

#define MAX_LIFE (3)

//**************************************************
// ライフを管理するクラスを定義
//**************************************************
class CLifeManager
{
public:

		~CLifeManager();

		HRESULT Init(void);
		void Uninit(void);
		void Update(void);
		void Draw(void);

		// ゲッター
		CLife* GetLife(const int nIdx) { return m_pLife[nIdx]; }

		// インスタンス生成関数
		static CLifeManager* Instance(void);


	private:

		CLifeManager();					// 格納コンストラクタ
		static CLifeManager* m_pInstance;	// シングルトン変数
		CLife* m_pLife[MAX_LIFE];		// 隕石(塵)のポインタ
	};
#endif



