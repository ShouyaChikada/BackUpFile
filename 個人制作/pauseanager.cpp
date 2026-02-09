//=================================================
//
//	pausemanager.h	ポーズマネージャー処理全般
// 
//	Author:chikada shouya
//
//=================================================
#include "pausemanager.h"
#include "input.h"
#include "game.h"
#include "manager.h"
#include "scene.h"
#include "title.h"

//=================================================
// 静的メンバ変数
//=================================================
bool CPauseManager::m_bPause = false;
bool CPauseManager::m_bCheck = false;
bool CPauseManager::m_bEnable = false;

//=================================================
// コンストラクタ
//=================================================
CPauseManager::CPauseManager()
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		m_pPause[nCnt] = nullptr;
	}

	m_SelectIdx = 1;
}

//=================================================
// デストラクタ
//=================================================
CPauseManager::~CPauseManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CPauseManager::Init(void)
{
	m_bPause = false;
	m_bCheck = false;
	m_bEnable = false;

	m_pPause[0] = CPause::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), 640.0f, 360.0f, "data\\TEXTURE\\brack.png");
	m_pPause[1] = CPause::Create(D3DXVECTOR3(640.0f, 180.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 125.0f, 60.0f, "data\\TEXTURE\\continue2.png");
	m_pPause[2] = CPause::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 275.0f, 60.0f, "data\\TEXTURE\\retry2.png");
	m_pPause[3] = CPause::Create(D3DXVECTOR3(640.0f, 540.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),300.0f, 60.0f,"data\\TEXTURE\\quit2.png");

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CPauseManager::Uninit(void)
{

}

//=================================================
// 更新処理
//=================================================
void CPauseManager::Update(void)
{
	if (!m_bPause) return;

	m_bEnable = false;

	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	
	CInputJoypad* pInputJoypad = CManager::GetJoypad();

	// フェード
	CFade* pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		if (m_SelectIdx == 1)
		{
			m_SelectIdx = 3;
		}
		else if (m_SelectIdx == 2)
		{
			m_SelectIdx = 1;
		}
		else if (m_SelectIdx == 3)
		{
			m_SelectIdx = 2;
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		if (m_SelectIdx == 1)
		{
			m_SelectIdx = 2;
		}
		else if (m_SelectIdx == 2)
		{
			m_SelectIdx = 3;
		}
		else if (m_SelectIdx == 3)
		{
			m_SelectIdx = 1;
		}
	}

	// カラー
	switch (m_SelectIdx - 1)
	{
	case MENU_CONTINUE:
		m_pPause[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		m_pPause[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pPause[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		m_pPause[1]->Easing(true, 0.1f, 0.2f, 0.2f, 0.4f);
		m_pPause[2]->Easing(false, NULL, NULL, NULL, NULL);
		m_pPause[3]->Easing(false, NULL, NULL, NULL, NULL);

		break;
	case MENU_RETRY:
		m_pPause[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		m_pPause[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pPause[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		m_pPause[1]->Easing(false, NULL, NULL, NULL, NULL);
		m_pPause[2]->Easing(true, 0.1f, 0.3f, 0.1f, 0.2f);
		m_pPause[3]->Easing(false, NULL, NULL, NULL, NULL);

		break;
	case MENU_QUIT:
		m_pPause[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		m_pPause[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pPause[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		
		m_pPause[1]->Easing(false, NULL, NULL, NULL, NULL);
		m_pPause[2]->Easing(false, NULL, NULL, NULL, NULL);
		m_pPause[3]->Easing(true, 0.3f, 0.5f, 0.1f, 0.2f);
		
		break;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//決定キー(ENTERキー)が押された
		//メニューに合わせてモードの切り替え
		switch (m_SelectIdx - 1)
		{
		case MENU_CONTINUE:
			SetEnablePause(false);
			m_bEnable = true;
			break;
		case MENU_RETRY:
			pFade->SetFade(new CGame());
			SetEnablePause(false);
			m_bCheck = true;
			break;
		case MENU_QUIT:
			pFade->SetFade(new CTitle());
			SetEnablePause(false);
			m_bCheck = true;
			break;
		}
	}

}

//=================================================
// 描画
//=================================================
void CPauseManager::Draw(void)
{

}

//=================================================
// 有効化設定
//=================================================
void CPauseManager::SetEnablePause(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_TAB) == true)
	{//ポーズキー(TABキー)が押された

		// 選択してるインデックスを1に戻す
		m_SelectIdx = 1;

		m_bPause = m_bPause ? false:true;
	}
}
