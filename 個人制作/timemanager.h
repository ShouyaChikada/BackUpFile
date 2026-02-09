//=================================================
//
// [TimeManager.h] : タイムのマネージャーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

#include "main.h"
#include "timer.h"

//**************************************************
// タイムを管理するクラスを定義
//**************************************************
class CTimeManager
{
public:

	~CTimeManager();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CTimer* GetTime(void) { return m_pTime; }

	static CTimeManager* Instance(void);

private:

	CTimeManager();						// 格納コンストラクタ
	static CTimeManager* m_pInstance;	// シングルトン変数
	CTimer* m_pTime;					// タイムのポインタ

};
#endif