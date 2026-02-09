//=================================================
//
//	game.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "game.h"
#include "manager.h"
#include "result.h"
#include "timer.h"
#include "effect.h"
#include "meshdome.h"
#include "timemanager.h"
#include "meshcylinder.h"
#include "scoremanager.h"
#include "meteomanager.h"
#include "pillermanager.h"
#include "playerManager.h"
#include "energymanager.h"


//=================================================
// 静的メンバ変数
//=================================================
CGrand* CGame::m_pGrand = nullptr;
CObjectX* CGame::m_pObjX = nullptr;
CObject3D* CGame::m_pObj3D = nullptr;
CMeshField* CGame::m_pMeshField = nullptr;
CPauseManager* CGame::m_pPauseManager = nullptr;

bool CGame::m_bCheck = false;

//=================================================
// コンストラクタ
//=================================================
CGame::CGame() : CScene(CScene::MODE_GAME)
{

}

//=================================================
// デストラクタ
//=================================================
CGame::~CGame()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CGame::Init(void)
{
	//m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt
	CManager::GetCamera()->SetFollowing();

	m_bCheck = false;

	m_pPauseManager = new CPauseManager;
	if (FAILED(m_pPauseManager->Init()))
	{
		return E_FAIL;
	}

	// 塵マネージャーの初期化
	CMeteoManager::Instance()->Init();

	// 柱のマネージャーの初期化
	CPillarManager::Instance()->Init();

	// プレイヤーマネージャーの初期化
	CPlayerManager::Instance()->Init(D3DXVECTOR3(0.0f, 10.0f, -100.0f), VEC3_NULL);

	// タイムマネージャーの初期化
	CTimeManager::Instance()->Init(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	// スコアマネージャーの初期化
	CScoreManager::Instance()->Init(D3DXVECTOR3(950.0f,0.0f,0.0f));

	// スタミナマネージャーの初期化
	CEnergyManager::Instance()->Init();

	// 床の生成
	CGrand::Create(D3DXVECTOR3(0.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 月の生成
	CObjectX::Create(D3DXVECTOR3(0.0f, -1900.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\moon.x", CObjectX::ROT_ON1);

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CGame::Uninit(void)
{
	if (m_pPauseManager != nullptr)
	{
		// ポーズマネージャーの終了処理
		m_pPauseManager->Uninit();
		delete m_pPauseManager;
		m_pPauseManager = nullptr;
	}

	// 塵マネージャーの終了
	CMeteoManager::Instance()->Uninit();

	// 柱のマネージャーの終了
	CPillarManager::Instance()->Uninit();

	// プレイヤーマネージャーの終了
	CPlayerManager::Instance()->Uninit();

	// タイムマネージャーの終了
	CTimeManager::Instance()->Uninit();

	// スコアマネージャーの終了
	CScoreManager::Instance()->Uninit();

	// スタミナマネージャーの終了
	CEnergyManager::Instance()->Uninit();
}

//=================================================
// 更新処理
//=================================================
void CGame::Update(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// ポーズの押下確認関数
	m_pPauseManager->SetEnablePause();

	// ポーズの更新処理
	m_pPauseManager->Update();
	
	// 塵マネージャーの更新
	CMeteoManager::Instance()->Update();

	// 柱のマネージャーの更新
	CPillarManager::Instance()->Update();

	//// パッド
	//CInputJoypad* pInputJoypad = nullptr;
	//pInputJoypad = CManager::GetJoypad();

	// フェード
	CFade* pFade = CManager::GetFade();

#ifdef _DEBUG
	if (m_pPauseManager->GetPause() == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{//決定キー(ENTERキー)が押された
			//モード設定(ゲーム画面に移行)
			pFade->SetFade(new CResult());
			m_bCheck = true;
		}
	}
#endif
}

//=================================================
// 描画処理
//=================================================
void CGame::Draw(void)
{

}