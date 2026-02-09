//=================================================
//
// [MeteoManager.h] : 小さな隕石のマネージャーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _METEOMANAGER_H_
#define _METEOMANAGER_H_

#include "main.h"
#include "cmeteorock.h"

constexpr int MAX_METEO = 3;

//**************************************************
// 隕石オブジェクトを管理するクラスを定義
//**************************************************
class CMeteoManager
{
public:
	~CMeteoManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CMeteoRock* GetRock(const int nIdx) { return m_pRock[nIdx]; }

	// インスタンス生成関数
	static CMeteoManager* Instance(void);


private:

	CMeteoManager();					// 格納コンストラクタ
	static CMeteoManager* m_pInstance;	// シングルトン変数
	CMeteoRock* m_pRock[MAX_METEO];		// 隕石(塵)のポインタ
	int m_nSpornPos;					// (-)のスポーン位置
};
#endif

