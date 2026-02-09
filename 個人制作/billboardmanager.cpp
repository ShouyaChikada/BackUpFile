//=================================================
//
// [BillboardManager.cpp] // ビルボードマネージャーの処理
// Author:chikada shouya
//
//=================================================
#include "billboardmanager.h"

//=================================================
// 静的メンバ変数
//=================================================
CBillboardManager* CBillboardManager::m_pInstance = nullptr; // インスタンス変数

//=================================================
// コンストラクタ
//=================================================
CBillboardManager::CBillboardManager() : m_pBillboard{}
{
	
}

//=================================================
// デストラクタ
//=================================================
CBillboardManager::~CBillboardManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CBillboardManager::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Tex, float fWidth, float fHeight, std::string FilePath, CBillboard::TYPE type)
{
	m_pBillboard = CBillboard::Create(pos, Tex, fWidth, fHeight, FilePath, type);
	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CBillboardManager::Uninit(void)
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
void CBillboardManager::Update(void)
{

}

//=================================================
// 描画
//=================================================
void CBillboardManager::Draw(void)
{

}

//=================================================
// インスタンス取得処理
//=================================================
CBillboardManager* CBillboardManager::Instance(void)
{
	// nullチェック
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CBillboardManager;
	}

	// 生成されたインスタンスを返す
	return m_pInstance;
}