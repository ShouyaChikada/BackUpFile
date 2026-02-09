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
// オブジェクト3D生成
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
// 初期化処理
//=============================================
HRESULT CEnergy::Init(void)
{
	CObject2D::Init();

	m_fCol = 1.0f;

	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void CEnergy::Uninit(void)
{
	CObject2D::Uninit();

	//自分の破棄
	CObject::Release();
}

//=============================================
// 更新処理
//=============================================
void CEnergy::Update(void)
{
	CObject2D::Update();

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	int nStamina = CPlayerManager::Instance()->GetPlayer()->GetStamina();
	
	// タイプがゲージだった場合
	if (m_Type == ENERGY_GAUGE)
	{

		SetSize((float)(nStamina), 40.0f);

		SetCol(D3DXCOLOR(1.0f, m_fCol,0.0f,1.0f));
	}

	if (m_nCharge >= nStamina)
	{
		if (m_bColChange)
		{
			m_fCol += 0.02f;

			if (m_fCol > 1.0f)
			{
				m_bColChange = false;
			}
		}
		if (!m_bColChange)
		{
			m_fCol -= 0.02f;

			if (m_fCol < 0.75f)
			{
				m_bColChange = true;
			}
		}
	}
	else
	{
		m_fCol = 1.0f;
	}

	m_nCharge = nStamina;
}

//=============================================
// 描画処理
//=============================================
void CEnergy::Draw(void)
{
	CObject2D::Draw();
}