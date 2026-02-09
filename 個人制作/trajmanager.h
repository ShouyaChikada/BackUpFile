//=================================================
//
// [TrajManager.h] : 軌跡のマネージャーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _TRAJMANAGER_H_
#define _TRAJMANAGER_H_

#include "main.h"
#include "meshtrajectory.h"

//**************************************************
// 軌跡オブジェクトを管理するクラスを定義
//**************************************************
class CTrajManager
{
public:

	~CTrajManager();

	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CMeshTrajectory* GetTrajctory(void) { return m_pTrajctory; }

	static CTrajManager* Instance(void);


private:

	CTrajManager();						// 格納コンストラクタ
	static CTrajManager* m_pInstance;	// シングルトン変数
	CMeshTrajectory* m_pTrajctory;		// 軌跡のポインタ
	bool m_bFinish;
};
#endif