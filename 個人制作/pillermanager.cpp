//=================================================
//
// [rockmanager.cpp]
// Author:chikada shouya
//
//=================================================
#include "pillermanager.h"
#include "timemanager.h"
#include "trajmanager.h"
#include <random>
#include <ctime> 

namespace
{
	float fMinZ1 = -100.0f;		// 最小ランダム変数(1つ目)
	float fMaxZ1 = 100.0f;		// 最大ランダム変数(1つ目)
	float fMinZ2 = -500.0f;		// 最小ランダム変数(2つ目)
	float fMaxZ2 = -100.0f;		// 最大ランダム変数(2つ目)
	int nInitNum = 50;			// 数字の初期化
	int nDeleteNum = 10;		// 毎秒減少させる変数
}

//=================================================
// 静的メンバ変数
//=================================================
CPillarManager* CPillarManager::m_pInstance = nullptr; // インスタンス変数

//=================================================
// コンストラクタ
//=================================================
CPillarManager::CPillarManager() : m_pPillar{}
{
	m_nCntTime = NULL;
}

//=================================================
// デストラクタ
//=================================================
CPillarManager::~CPillarManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CPillarManager::Init(void)
{
	m_nCntTime = 20;

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CPillarManager::Uninit(void)
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
void CPillarManager::Update(void)
{
	int nSec = CTimeManager::Instance()->GetTime()->GetTime();
	int nMin = CTimeManager::Instance()->GetTime()->GetMin();

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// 0から99までの乱数を生成する
	float z1 = ((float)rand() / RAND_MAX) * fMaxZ1 - fMinZ1;
	float z2 = ((float)rand() / RAND_MAX) * fMaxZ2 - fMinZ2;

	if (m_nCntTime < NULL)
	{
		m_nCntTime = nMaxNum;
	}

	if (nSec == m_nCntTime)
	{
		if (m_pPillar[0] == nullptr && m_pPillar[1] == nullptr)
		{
			m_pPillar[0] = CMeteoPillar::Create(D3DXVECTOR3(2100.0f, 20.0f, z1), (CMeteoPillar::ROT)3); //fRand0
			m_pPillar[1] = CMeteoPillar::Create(D3DXVECTOR3(-2100.0f, 20.0f, z2), (CMeteoPillar::ROT)3); //fRand1
			m_nCntTime = m_nCntTime - nDeleteNum;
		}
	}
	for (int nCnt = 0; nCnt < MaxPillar; nCnt++)
	{
		if (m_pPillar[nCnt] != nullptr)
		{
			bool bDeath = m_pPillar[nCnt]->GetDeath();

			if (bDeath == true)
			{
				m_pPillar[nCnt]->Uninit();
				m_pPillar[nCnt] = nullptr;
			}
		}
	}
}

//=================================================
// 描画
//=================================================
void CPillarManager::Draw(void)
{

}

//=================================================
// インスタンス取得処理
//=================================================
CPillarManager* CPillarManager::Instance(void)
{
	// nullチェック
	if (m_pInstance == nullptr)
	{
		// インスタンス生成
		m_pInstance = new CPillarManager;
	}

	// 生成されたインスタンスを返す
	return m_pInstance;
}

