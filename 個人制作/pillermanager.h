//=================================================
//
// [PiilerManager.h] : 柱のマネージャー
// Author:chikada shouya
//
//=================================================
#ifndef _PILLERMANAGER_H_
#define _PILLERMANAGER_H_

#include "main.h"
#include "meteopillar.h"

constexpr int MaxPillar = 2;

//**************************************************
// 柱オブジェクトを管理するクラスを定義
//**************************************************
class CPillarManager
{
public:

	~CPillarManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CMeteoPillar* GetPillar(const int nIdx) { return m_pPillar[nIdx]; }

	static CPillarManager* Instance(void);

private:

	CPillarManager();						// 格納コンストラクタ
	static CPillarManager* m_pInstance;		// シングルトン変数
	CMeteoPillar* m_pPillar[MaxPillar];	// 隕石(柱)のポインタ
	int m_nCntTime;							// 生成時間

};
#endif