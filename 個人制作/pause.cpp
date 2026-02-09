//=================================================
//
//	pause.cpp	ポーズの処理全般
// 
// Author:chikada shouya
//
//=================================================
#include "pause.h"
#include "texturemanager.h"
#include "manager.h"
#include "pausemanager.h"
#include "easing.h"

//=================================================
// コンストラクタ
//=================================================
CPause::CPause(int nPriolity): CObject2D(nPriolity)
{
	m_bEasing = false;
	m_fX = NULL;
	m_fY = NULL;
}

//=================================================
// デストラクタ
//=================================================
CPause::~CPause()
{

}

//=================================================
// 生成
//=================================================
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fX, float fY, std::string aName)
{
	CPause* pPause = nullptr;
	pPause = new CPause;

	if (pPause != nullptr)
	{
		pPause->SetCol(col);
		pPause->SetSize(fX, fY);
		pPause->SetPosition(pos);
		pPause->m_fX = fX;
		pPause->m_fY = fY;
		pPause->SetTexPath(aName);
		pPause->SetType(CObject2D::ANCHORTYPE_CENTER);
		pPause->Init();
		return pPause;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CPause::Init(void)
{
	// タイプの設定
	CObject::SetType(TYPE_PAUSE);

	// 基底クラスの初期化
	CObject2D::Init();

	m_fCountFrame = 0.0f;
	m_fMaxFrame = 60.0f;

	return S_OK;
}

//=================================================
// 終了
//=================================================
void CPause::Uninit(void)
{
	// 基底クラスの終了
	CObject2D::Uninit();
}

//=================================================
// 更新処理
//=================================================
void CPause::Update(void)
{
	// 基底クラスの更新
	CObject2D::Update();	
}

//=================================================
// 描画
//=================================================
void CPause::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (CPauseManager::GetPause() == true)
	{
		CObject2D::Draw();
	}
}

//=================================================
// イージング用関数
//=================================================
void CPause::Easing(bool bEasing, float fXMin, float fXMax, float fYMin, float fYMax)
{
	// 位置を取得
	auto pos = CObject2D::GetPosition();

	// 初期の大きさ
	D3DXVECTOR2 Apper = { fXMin * pos.x, fYMin * pos.y };
	// 目標の大きさ
	D3DXVECTOR2 Dest = { fXMax * pos.x, fYMax * pos.y };

	// イージング用変数
	D3DXVECTOR3 Setpos = {};

	// イージング判定が有効だったら
	if (bEasing == true)
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
	else
	{
		// サイズの設定
		SetSize(m_fX, m_fY);
	}

}