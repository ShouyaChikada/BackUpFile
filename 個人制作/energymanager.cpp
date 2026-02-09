//=================================================
//
// [EnergyManager.cpp] : スタミナマネージャー処理
// Author:chikada shouya
//
//=================================================
#include "energymanager.h"

//=================================================
// 静的メンバ変数
//=================================================
CEnergyManager* CEnergyManager::m_pInstance = nullptr; // インスタンス変数

//=================================================
// コンストラクタ
//=================================================
CEnergyManager::CEnergyManager() : m_pEnergy{}
{

}

//=================================================
// デストラクタ
//=================================================
CEnergyManager::~CEnergyManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CEnergyManager::Init(void)
{

	m_pEnergy[0] = CEnergy::Create(D3DXVECTOR3(0.0f, 650.0f, 0.0f),600.0f,70.0f,"data\\TEXTURE\\sutamina.png", CObject2D::ANCHORTYPE_LEFT,CEnergy::ENERGY_NONE);
	m_pEnergy[1] = CEnergy::Create(D3DXVECTOR3(17.5f, 665.0f, 0.0f),545.0f,40.0f,"data\\TEXTURE\\",CObject2D::ANCHORTYPE_LEFT,CEnergy::ENERGY::ENERGY_GAUGE);
	m_pEnergy[2] = CEnergy::Create(D3DXVECTOR3(0.0f, 650.0f, 0.0f),600.0f,70.0f,"data\\TEXTURE\\sutaminaber.png", CObject2D::ANCHORTYPE_LEFT,CEnergy::ENERGY::ENERGY_NONE);

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CEnergyManager::Uninit(void)
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
void CEnergyManager::Update(void)
{

}

//=================================================
// 描画
//=================================================
void CEnergyManager::Draw(void)
{

}

//=================================================
// インスタンス取得処理
//=================================================
CEnergyManager* CEnergyManager::Instance(void)
{
	// nullチェック
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CEnergyManager;
	}

	// 生成されたインスタンスを返す
	return m_pInstance;
}