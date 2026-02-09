//=================================================
//
// [Life.cpp]	// ライフの処理全般
// Author:chikada shouya
//
//=================================================
#include "life.h"
#include "easing.h"
#include "playerManager.h"

//=================================================
// コンストラクタ
//=================================================
CLife::CLife(int nPriolity) : CObject2D(nPriolity)
{
	m_fEaseWidth = NULL;
	m_fEaseHeight = NULL;
	m_fCountFrame = NULL;
m_fMaxFrame = NULL;
m_bEasing = false;
}

//=================================================
// デストラクタ
//=================================================
CLife::~CLife()
{

}

//=================================================
// 生成
//=================================================
CLife* CLife::Create(D3DXVECTOR3 pos)
{
	CLife* pLife = nullptr;
	pLife = new CLife;

	if (pLife != nullptr)
	{
		pLife->SetPosition(pos);
		pLife->SetType(ANCHORTYPE_CENTER);
		pLife->SetSize(35.0f, 35.0f);
		pLife->SetTexPath("data\\TEXTURE\\heart.png");
		pLife->Init();

		return pLife;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CLife::Init(void)
{
	// 基底クラスの初期化
	CObject2D::Init();

	// 現在の位置を取得
	m_fEaseWidth = 15.0f;
	m_fEaseHeight = 15.0f;
	m_fMaxFrame = 30.0f;

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CLife::Uninit()
{
	// 基底クラスの破棄
	CObject2D::Uninit();
}

//=================================================
// 更新
//=================================================
void CLife::Update()
{
	// 基底クラスの更新
	CObject2D::Update();

	// プレイヤーのライフの取得
	int nLife = CPlayerManager::Instance()->GetPlayer()->GetLife();

	// 位置の取得
	auto pos = GetPosition();

	// 初期の大きさ
	D3DXVECTOR2 Apper = { 0.075f * pos.x, 0.075f * pos.y };
	// 目標の大きさ
	D3DXVECTOR2 Dest = { 0.05f * pos.x,0.05f * pos.y };

	// イージング用変数
	D3DXVECTOR3 Setpos = {};
	
	// ライフが残り1つだったら
	if (nLife < 2)
	{
		// イージング判定が無効なら
		if (m_bEasing == false)
		{
			// アニメーションカウンターを進める
			m_fCountFrame++;

			// 設定する大きさの変数
			D3DXVECTOR2 Size = {};
			// 今のアニメーションの進行割合を計算
			float Ratio = EaseInOutSine(m_fCountFrame / m_fMaxFrame);
			// 最終的な大きさから初期の大きさからの差分
			D3DXVECTOR2 Diff = { Dest.x - Apper.x,Dest.y - Apper.y };
			// 今の大きさを計算
			Size = Apper + Diff * Ratio;

			// サイズの設定
			CObject2D::SetSize(Size.x, Size.y);

		}
		// イージング判定が有効なら
		else if (m_bEasing == true)
		{
			// アニメーションカウンターを進める
			m_fCountFrame--;

			// 設定する大きさの変数
			D3DXVECTOR2 Size = {};
			// 今のアニメーションの進行割合を計算
			float Ratio = EaseInOutSine(m_fCountFrame / m_fMaxFrame);
			// 最終的な大きさから初期の大きさからの差分
			D3DXVECTOR2 Diff = { Dest.x + Apper.x,Dest.y + Apper.y };
			// 今の大きさを計算
			Size = Apper - Diff * Ratio;

			// サイズの設定
			CObject2D::SetSize(Size.x, Size.y);
		}
		// フレームカウントがマックスフレームと一緒になったら
		else if (m_fCountFrame == m_fMaxFrame)
		{
			// イージング判定を有効にする
			m_bEasing = true;
		}
		// フレームカウントが0.0fなら
		else if (m_fCountFrame == 0.0f)
		{
			// イージング判定を無効にする
			m_bEasing = false;
		}
	}
}

//=================================================
// 描画
//=================================================
void CLife::Draw()
{
	// 基底クラスの描画
	CObject2D::Draw();
}