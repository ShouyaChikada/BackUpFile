//=================================================
//
// [playerManager.h] : プレイヤーのマネージャーヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_

#include "main.h"
#include "player.h"

//**************************************************
// プレイヤーを管理するクラスを定義
//**************************************************
class CPlayerManager
{
public:

	~CPlayerManager();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CPlayer* GetPlayer(void) { return m_pPlayer; }

	static CPlayerManager* Instance(void);

private:

	CPlayerManager();						// 格納コンストラクタ
	static CPlayerManager* m_pInstance;		// シングルトン変数
	CPlayer* m_pPlayer;						// プレイヤーのポインタ

};
#endif