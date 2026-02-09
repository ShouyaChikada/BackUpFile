//=================================================
//
// [meteopillar.cpp]	隕石(柱)の処理全般
// 
// Author:chikada shouya
//
//=================================================
#include "meteopillar.h"
#include "billboardmanager.h"
#include "debugproc.h"

namespace
{
	float fLimitPos = 2100.0f;	// 飛んでくる柱の制限
	int nCntTime = 180;				// クールタイム
}
//=================================================
// コンストラクタ
//=================================================
CMeteoPillar::CMeteoPillar()
{
	m_posOld = VEC3_NULL;
	for (int nCnt = 0; nCnt < nMaxNum; nCnt++)
	{
		m_bChange[nCnt] = false;
	}
	m_bDeath = false;
	m_nMoveCntTime = NULL;
}

//=================================================
// デストラクタ
//=================================================
CMeteoPillar::~CMeteoPillar()
{

}

//=================================================
// 生成
//=================================================
CMeteoPillar* CMeteoPillar::Create(D3DXVECTOR3 pos, ROT rot)
{
	CMeteoPillar* pMeteoPillar = nullptr;
	pMeteoPillar = new CMeteoPillar;

	if (pMeteoPillar != nullptr)
	{
		pMeteoPillar->SetPosition(pos);
		pMeteoPillar->SetIdx("data\\MODEL\\hasira.x");
		pMeteoPillar->SetRotaiton(CObjectX::ROT::ROT_OFF);
		pMeteoPillar->Init();
		pMeteoPillar->SetRotSize(rot);

		return pMeteoPillar;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CMeteoPillar::Init(void)
{
	m_nMoveCntTime = nCntTime;

	auto pos = GetPosition();

	CRock::Init();

	if (pos.x >= fLimitPos)
	{
		CBillboardManager::Instance()->Init(D3DXVECTOR3(0.0f,pos.y,pos.z), D3DXVECTOR2(1.0f,1.0f), 1000.0f, 45.0f, "data\\TEXTURE\\warningber.png",CBillboard::TYPE_BLINKING);
	}
	else if (pos.x <= -fLimitPos)
	{
		CBillboardManager::Instance()->Init(D3DXVECTOR3(0.0f, pos.y, pos.z), D3DXVECTOR2(1.0f, 1.0f), 1000.0f, 45.0f, "data\\TEXTURE\\warningber.png", CBillboard::TYPE_BLINKING);
	}

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CMeteoPillar::Uninit(void)
{
	// 基底クラスの破棄
	CRock::Uninit();

	// ビルボードインスタンスの破棄
	CBillboardManager::Instance()->Uninit();
}

//=================================================
// 更新
//=================================================
void CMeteoPillar::Update(void)
{
	//外側から飛んでくる隕石
	MovePillar();	

	// 基底クラスの更新
	CRock::Update();
}

//=================================================
// 描画
//=================================================
void CMeteoPillar::Draw(void)
{
	// 基底クラスの描画
	CRock::Draw();

	// 位置の取得
	auto Pos = CRock::GetPosition();
	
	CDebugProc::Print("------------ { 柱 } ------------ \n");
	CDebugProc::Print("座標 { pos.x %.2f pos.z %.2f } \n", Pos.x, Pos.z);
	//CDebugProc::Draw();
}

//=================================================
// 向きの変更
//=================================================
void CMeteoPillar::SetRotSize(ROT Rot)
{
	// 向きの初期化 & サイズの取得
	auto rot = VEC3_NULL;
	auto size = GetSize();

	switch (Rot)
	{
	case ROT_NONE:
		rot = VEC3_NULL;
		size = D3DXVECTOR3(size.x, size.y, size.z);
		break;

	// 向きとサイズをX軸に回転
	case ROT_X:
		rot = D3DXVECTOR3(1.57f, 0.0f, 0.0f);
		size = D3DXVECTOR3(size.x, size.z, size.y);
		break;

	// 向きとサイズをY軸に回転
	case ROT_Y:
		rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		size = D3DXVECTOR3(size.x, size.y, size.z);
		break;

	// 向きとサイズをZ軸に回転
	case ROT_Z:
		rot = D3DXVECTOR3(0.0f, 0.0f, 1.57f);
		size = D3DXVECTOR3(size.y, size.x, size.z);
		break;

	case ROT_MAX:
		break;

	default:
		break;
	}

	// 向きを設定
	SetRot(rot);
	// サイズを設定
	SetSize(size);
}

//=================================================
// 柱の移動設定
//=================================================
void CMeteoPillar::MovePillar(void)
{
	//if (m_Type != TYPE_HASIRA)return;

	// 位置、移動量を取得
	auto pos = GetPosition();
	auto move = GetMove();

	if (pos.x >= fLimitPos)m_bChange[0] = true;
	if (pos.x <= -fLimitPos)m_bChange[1] = true;

	// 0秒じゃなかったら
	if (m_nMoveCntTime > NULL)
	{
		m_nMoveCntTime--;
	}
	
	// 0秒以下だったら
	if (m_nMoveCntTime <= NULL)
	{
		// ビルボードの破棄
		CBillboardManager::Instance()->Uninit();

		// 右から左 or みだりから右
		if (m_bChange[0] == true)
		{
			move.x -= (MAX_SPEED * 2.5f);

			if (pos.x <= -fLimitPos)
			{
				m_bDeath = true;
			}
		}
		if (m_bChange[1] == true)
		{
			move.x += (MAX_SPEED * 2.5f);

			if (pos.x >= 2100.0f)
			{
				m_bDeath = true;
			}
		}
	}

	// 位置を前回の位置に保存
	m_posOld = pos;

	// 位置を設定
	SetPosition(pos);

	// 移動量を設定
	SetMove(move);
}
