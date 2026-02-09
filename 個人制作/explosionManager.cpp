//=================================================
//
//	ExplosionManager.cpp // 爆発マネージャーの処理メイン
// 
//	Author:近田 尚也
//
//=================================================
#include "explosionManager.h"

//=================================================
// 静的メンバ変数
//=================================================
CExplosionManager* CExplosionManager::m_pInstance = nullptr; // インスタンス変数

//=================================================
// コンストラクタ
//=================================================
CExplosionManager::CExplosionManager() : m_pExplosion{}
{
	
}

//=================================================
// デストラクタ
//=================================================
CExplosionManager::~CExplosionManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CExplosionManager::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, CBillboard::TYPE type)
{

	m_pExplosion = CExplosion::Create(pos, Tex, fWidth, fHeight, FilePath, type);

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CExplosionManager::Uninit(void)
{
	// シングルトンの破棄
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//=================================================
// 更新
//=================================================
void CExplosionManager::Update(void)
{

}

//=================================================
// 描画
//=================================================
void CExplosionManager::Draw(void)
{

}

//=================================================
// インスタンス取得処理
//=================================================
CExplosionManager* CExplosionManager::Instance(void)
{
	// nullチェック
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CExplosionManager;
	}

	// 生成されたインスタンスを返す
	return m_pInstance;
}
