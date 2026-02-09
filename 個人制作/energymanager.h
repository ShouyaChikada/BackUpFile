//=================================================
//
// [EnergyManager.h]	// スタミナマネージャーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _ENERGYMANAGER_H_
#define _ENERGYMANAGER_H_

#include "main.h"
#include "energy.h"

#define MAX_ENERGY (3)

//**************************************************
// ライフを管理するクラスを定義
//**************************************************
class CEnergyManager
{
public:

	~CEnergyManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CEnergy* GetLife(const int nIdx) { return m_pEnergy[nIdx]; }

	// インスタンス生成関数
	static CEnergyManager* Instance(void);


private:

	CEnergyManager();					// 格納コンストラクタ
	static CEnergyManager* m_pInstance;	// シングルトン変数
	CEnergy* m_pEnergy[MAX_ENERGY];		// 隕石(塵)のポインタ
};
#endif



