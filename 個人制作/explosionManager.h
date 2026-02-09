//=================================================
//
//	ExplosionManager.h // 爆発マネージャーの処理ヘッダー
// 
//	Author:近田 尚也
//
//=================================================
#ifndef _EXPLOSIONMANAGER_H_
#define _EXPLOSIONMANAGER_H_

#include "main.h"
#include "explosion.h"

//**************************************************
// 爆発オブジェクトを管理するクラスを定義
//**************************************************
class CExplosionManager
{
public:

	~CExplosionManager();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, CBillboard::TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	CExplosion* GetExplosion(void) { return m_pExplosion; }

	// インスタンス生成関数
	static CExplosionManager* Instance(void);


private:

	CExplosionManager();					// 格納コンストラクタ
	static CExplosionManager* m_pInstance;	// シングルトン変数
	CExplosion* m_pExplosion;		// 爆発のポインタ

};

#endif