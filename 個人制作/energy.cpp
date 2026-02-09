//=============================================
//
// Energy.cpp スタミナの処理メイン
// author chikada shouya
//
//=============================================
#include "energy.h"
#include "playerManager.h"
#include "input.h"
#include "manager.h"

namespace Energy
{
	float fMaxCol = 1.0f;	// カラーの最大基準値
	float fMinCol = 0.75f;	// カラーの最低基準値
	float fSize = 40.0f;	// サイズ
	float fNullCol = 0.0f;	// カラーの初期値
	float fPulNum = 0.02f;	// カラーをだんだん下げる値
};
//=============================================
// コンストラクタ
//=============================================
CEnergy::CEnergy(int nPriority) : CObject2D(nPriority)
{
	m_Type = ENERGY_NONE;
	m_nCharge = NULL;
	m_fCol = NULL;
	m_fPosTexU = NULL;
	m_bColChange = false;
}

//=============================================
// デストラクタ
//=============================================
CEnergy::~CEnergy()
{

}

//=============================================
// 生成
//=============================================
CEnergy* CEnergy::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, std::string FilePath, CObject2D::ANCHORTYPE type, ENERGY Energy)
{
	CEnergy* pEnergy = nullptr;
	pEnergy = new CEnergy;

	// ローカルポインタがnullptrじゃなかったら
	if (pEnergy != nullptr)
	{
		pEnergy->SetPosition(pos);
		pEnergy->SetEnergyType(Energy);
		pEnergy->SetSize(fWidth,fHeight);
		pEnergy->SetTexPath(FilePath);
		pEnergy->SetType(type);
		pEnergy->Init();
		return pEnergy;
	}
	else
	{
		return nullptr;
	}
}

//=============================================
// 初期化
//=============================================
HRESULT CEnergy::Init(void)
{
	// 基底蔵の初期化
	CObject2D::Init();

	// カラー設定
	m_fCol = Energy::fMaxCol;

	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void CEnergy::Uninit(void)
{
	// 基底クラスの破棄
	CObject2D::Uninit();

	//自分の破棄
	CObject::Release();
}

//=============================================
// 更新処理
//=============================================
void CEnergy::Update(void)
{
	// 基底クラスの更新
	CObject2D::Update();

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	int nStamina = CPlayerManager::Instance()->GetPlayer()->GetStamina();
	
	// タイプがゲージだった場合
	if (m_Type == ENERGY_GAUGE)
	{
		// サイズを設定
		SetSize((float)(nStamina), Energy::fSize);

		// カラーを設定
		SetCol(D3DXCOLOR(Energy::fMaxCol, m_fCol, Energy::fNullCol, Energy::fMaxCol));
	}

	// チャージがスタミナ以上だったら
	if (m_nCharge >= nStamina)
	{
		// カラーの入れ替えが有効だったら
		if (m_bColChange)
		{
			// カラーを加算
			m_fCol += Energy::fPulNum;

			// カラーが最大値を超えたら
			if (m_fCol > Energy::fMaxCol)
			{
				// カラー入れ替えを無効に
				m_bColChange = false;
			}
		}
		// カラー入れ替えが無効だったら
		if (!m_bColChange)
		{
			// カラーを減算
			m_fCol -= Energy::fPulNum;

			// カラーが最小値を下回ったら
			if (m_fCol < Energy::fMinCol)
			{
				// カラー入れ替えを有効に
				m_bColChange = true;
			}
		}
	}
	else
	{
		// カラーに最大値を代入
		m_fCol = Energy::fMaxCol;
	}

	// スタミナを保存用変数に代入
	m_nCharge = nStamina;
}

//=============================================
// 描画処理
//=============================================
void CEnergy::Draw(void)
{
	// 基底クラスの描画
	CObject2D::Draw();
}