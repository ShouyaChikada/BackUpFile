//=================================================
//
// [MeteoManager.cpp] : 小さな隕石のマネージャー処理
// Author:chikada shouya
//
//=================================================
#include "meteomanager.h"
#include "timer.h"
#include "playerManager.h"
#include <random>
#include <ctime> 

//=================================================
// 静的メンバ変数
//=================================================
CMeteoManager* CMeteoManager::m_pInstance = nullptr; // インスタンス変数

//=================================================
// コンストラクタ
//=================================================
CMeteoManager::CMeteoManager() : m_pRock{}
{
	m_nSpornPos = NULL;
}

//=================================================
// デストラクタ
//=================================================
CMeteoManager::~CMeteoManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CMeteoManager::Init(void)
{
	m_nSpornPos = -100;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		float fRand = (float)(std::rand() % -m_nSpornPos + m_nSpornPos);

		m_pRock[nCnt] = CMeteoRock::Create(D3DXVECTOR3(fRand, 20.0f, 800.0f));
	}

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CMeteoManager::Uninit(void)
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
void CMeteoManager::Update(void)
{
	int nNumber = CPlayerManager::Instance()->GetPlayer()->GetNumber();

	for (int nCnt = 0;nCnt < MAX_METEO;nCnt++)
	{
		if (nNumber < MAX_METEO && nNumber > -1 && nNumber != nCnt)
		{
			if (m_pRock[nNumber]->CollisionMeteo(m_pRock[nCnt]->GetPosition()))
			{
   				float fRand0 = (float)(std::rand() % -m_nSpornPos + m_nSpornPos);

				m_pRock[nCnt]->Uninit();
				m_pRock[nNumber]->Uninit();
				m_pRock[nCnt] = nullptr;
				m_pRock[nNumber] = nullptr;
				m_pRock[nCnt] = CMeteoRock::Create(D3DXVECTOR3(fRand0, 20.0f, 800.0f));
				m_pRock[nNumber] = CMeteoRock::Create(D3DXVECTOR3(fRand0, 20.0f, 800.0f));
			}
			
		}
	}


	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		if (m_pRock[nCnt] != nullptr)
		{
			bool bDeath = m_pRock[nCnt]->GetDeath();

			if (bDeath == true)
			{
				float fRand0 = (float)(std::rand() % -m_nSpornPos + m_nSpornPos);

				m_pRock[nCnt]->Uninit();

				m_pRock[nCnt] = nullptr;

				m_pRock[nCnt] = CMeteoRock::Create(D3DXVECTOR3(fRand0, 20.0f, 800.0f));
			}
		}
	}
}

//=================================================
// 描画
//=================================================
void CMeteoManager::Draw(void)
{

}

//=================================================
// インスタンス取得処理
//=================================================
CMeteoManager* CMeteoManager::Instance(void)
{
	// nullチェック
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CMeteoManager;
	}

	// 生成されたインスタンスを返す
	return m_pInstance;
}