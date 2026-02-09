//=================================================
//
// [meteorock.cpp]	隕石(塵)の処理全般
// 
// Author:chikada shouya
//
//=================================================
#include "cmeteorock.h"
#include "playerManager.h"
#include "easing.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "particle.h"
#include "meshtrajectory.h"
#include "explosionManager.h"
#include "cursor.h"
#include "scoremanager.h"
#include "billboardmanager.h"

namespace
{
	float MaxSpeedValue = 17.5f;	// 回転スピード
	float fColor = 0.3f;			// カラーの引数代入用変数
	float fLimitX = 1000.0f;		// X軸移動制限用変数
	float fLimitZ = 900.0f;			// Y軸移動制限用変数
	int nCntTime = 300;				// 時間を代入用変数
	float fHalf = 0.5f;				// 様々な段階で使うハーフ変数
}

//=================================================
// コンストラクタ
//=================================================
CMeteoRock::CMeteoRock()
{
	m_posOld = VEC3_NULL;
	m_Nextpos = VEC3_NULL;

	m_nSpornTime = NULL;
	m_nCntValueTime = NULL;
	
	m_fPos = NULL;
	m_fMove = NULL;
	m_fDiffX = NULL;
	m_fDiffZ = NULL;
	m_fDistance = NULL;
	m_fRotValue = NULL;
	m_fAddValue = NULL;
	m_fDistanceValue = NULL;

	m_bDeath = false;
	m_bSign1 = false;
	m_bSign0 = false;
	m_bCheck0 = false;
	m_bCheck1 = false;
	m_bCheck2 = false;
	m_bsDeath = false;
	m_bTimeOut = false;
	m_bCollision = false;
	m_bReleaseMove = false;
	m_bBillboardDeath = false;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_bRelease[nCnt] = false;
	}
}

//=================================================
// デストラクタ
//=================================================
CMeteoRock::~CMeteoRock()
{
	
}

//=================================================
// 生成
//=================================================
CMeteoRock* CMeteoRock::Create(D3DXVECTOR3 pos)
{
	CMeteoRock* pMeteoRock = nullptr;
	pMeteoRock = new CMeteoRock;

	if (pMeteoRock != nullptr)
	{
		pMeteoRock->SetPosition(pos);
		pMeteoRock->SetIdx("data\\MODEL\\inseki.x");	// inseki.x || earth000.x
		pMeteoRock->SetRotaiton(ROT::ROT_OFF);
		pMeteoRock->Init();

		return pMeteoRock;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CMeteoRock::Init(void)
{
	// 基底クラスの初期化
	CRock::Init();

	auto pos = GetPosition();

	// 軌跡の生成
	m_pTrajectory = CMeshTrajectory::Create(pos, VEC3_NULL, D3DXCOLOR(fColor, fColor, fColor, 1.0f));
	
	// 矢印の生成
	//m_pCursor = CCursor::Create(pos, VEC3_NULL, 25.0f);
	
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//CBillboardManager::Instance()->Init(D3DXVECTOR3(pos.x, pos.y, 350.0f), D3DXVECTOR2(1.0f, 1.0f), 60.0f, 60.0f, "data\\TEXTURE\\mark.png", CBillboard::TYPE_SBLINKING);

	m_fAddValue = 0.3f;			// 0.3f
	m_fMove = MAX_SPEED;

	m_nSpornTime = (rand() % 240 + 0);

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CMeteoRock::Uninit(void)
{
	// 規定クラスの破棄
	CRock::Uninit();

	// 軌跡の破棄
	if (m_pTrajectory != nullptr)
	{
		m_pTrajectory->Uninit();
		m_pTrajectory = nullptr;
	}

	//// 矢印の破棄
	//if (m_pCursor != nullptr)
	//{
	//	m_pCursor->Uninit();
	//	m_pCursor = nullptr;
	//}

	// 爆発のインスタンスを破棄
	CExplosionManager::Instance()->Uninit();

	// ビルボードマネージャーの破棄
	//CBillboardManager::Instance()->Uninit();
}

//=================================================
// 更新
//=================================================
void CMeteoRock::Update(void)
{
	auto pos = GetPosition();
	auto move = GetMove();
	// プレイヤー座標の取得
	auto PlayerPos = CPlayerManager::Instance()->GetPlayer()->GetPosition();

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	m_nSpornTime--;

	if (m_nSpornTime < 0)
	{
		if (m_bBillboardDeath == false)
		{
 			//CBillboardManager::Instance()->GetBillboard()->Uninit();
			m_bBillboardDeath = true;
		}

		// 消滅していなかったら
		if (m_bDeath == false)
		{
			// オブジェクト回転
			UpdateObjectPos(pos, move);

			// 回転をしていなかったら
			if (m_bSign0 == false && m_bSign1 == false)
			{
				move.z -= m_fMove;

				// 位置、移動量を保存
				SetPosition(pos);
				SetMove(move);

				// プレイヤーと隕石の差分
				m_fDiffX = pos.x - PlayerPos.x;
				m_fDiffZ = pos.z - PlayerPos.z;

				// 角度を決める
				m_fPos = atan2f(m_fDiffX, m_fDiffZ);

				// プレイヤーと隕石の角度を軸に回る
				m_fRotValue = m_fPos;

				// 角度の正規化
				m_fRotValue = RotNormalize(m_fRotValue);
			}

			// 規定クラスの更新
			CRock::Update();
		}

		// 画面外に行ったら消す
		if (pos.x > fLimitX || pos.x < -fLimitX ||
			pos.z > fLimitZ || pos.z < -fLimitZ)
		{
			m_bRelease[0] = false;
			m_bRelease[1] = false;
			m_bDeath = true;
			m_bsDeath = true;

			// 爆発を生成
			CExplosionManager::Instance()->Init(pos, D3DXVECTOR2(0.125f, 1.0f), 60.0f, 60.0f, "data\\TEXTURE\\explosion000.png", CBillboard::TYPE_NONE);
		}

		// 軌跡の設定
		m_pTrajectory->SetTrajectory(pos, m_bCheck0, m_bCheck1, m_fRotValue);

	}
}

//=================================================
// 描画
//=================================================
void CMeteoRock::Draw(void)
{
	// 規定クラスの描画
	CRock::Draw();
}

//=================================================
// オブジェクト回転
//=================================================
void CMeteoRock::UpdateObjectPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// プレイヤー座標の取得
	auto PlayerPos = CPlayerManager::Instance()->GetPlayer()->GetPosition();

	// 向きを取得
	auto rot = GetRot();
	//m_pCursor->SetRot(rot);

	// プレイヤーから隕石の差分を計算
	auto Diff = PlayerPos - pos;
	float fAngleY = atan2f(Diff.x, Diff.z);

	// 回転量の加算用変数 & 回転する距離
	float fAddValue = 0.0000001f;
	float fDistance = 7.5f;

	// キーボードポインタ
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// 距離の計算
	m_fDistance = sqrtf((pos.x - PlayerPos.x) * (pos.x - PlayerPos.x) + (pos.y - PlayerPos.y) * (pos.y - PlayerPos.y) + (pos.z - PlayerPos.z) * (pos.z - PlayerPos.z));

	// 回転をしていなかったら
	if (m_bTimeOut == false && m_bRelease[0] == false && m_bRelease[1] == false)
	{
		// 時計回り
		if ((m_bCheck2 == true && m_bCheck1 == true) && pInputKeyboard->GetPress(DIK_SPACE) == true)
		{
			//m_pCursor->SetLook(true);

			CPlayerManager::Instance()->GetPlayer()->SetCTstaina(0);
			CPlayerManager::Instance()->GetPlayer()->SetSutamina(1);

			m_bSign0 = true;

			if (m_nCntValueTime < nCntTime)
			{// 溜めている間は遠心力で伸ばす
				m_fAddValue += fAddValue;
			}
			else
			{// 五秒立つと強制射出
				m_bTimeOut = true;
			}

			// 回転軸に加算
			m_fRotValue += m_fAddValue;

			// 角度の正規化
			m_fRotValue = RotNormalize(m_fRotValue);
			fAngleY = RotNormalize(fAngleY);

			rot.y = fAngleY;

			// 向きに保存
			SetRot(D3DXVECTOR3(rot.x, rot.y + (D3DX_PI * 0.5f), rot.z));

			pos.x = PlayerPos.x + sinf(m_fRotValue) * m_fDistance;
			pos.z = PlayerPos.z + cosf(m_fRotValue) * m_fDistance;

			CRock::SetPosition(pos);

			// 規定の距離に届いていなかったら
			if (m_fDistanceValue <= fDistance)
			{
				m_fDistanceValue += 0.05f;
			}

			// 回転する時間の加算
			m_nCntValueTime++;

			//m_pCursor->SetPosition(pos);
		}

		// 反時計回り
		if ((m_bCheck2 == true && m_bCheck0 == true) && pInputKeyboard->GetPress(DIK_SPACE) == true)
		{
			//m_pCursor->SetLook(true);

			CPlayerManager::Instance()->GetPlayer()->SetCTstaina(0);
			CPlayerManager::Instance()->GetPlayer()->SetSutamina(1);

			m_bSign1 = true;
			
			if (m_nCntValueTime < nCntTime)
			{// 溜めている間は遠心力で伸ばす
				m_fAddValue += fAddValue;
			}
			else
			{// 五秒立つと強制射出
				m_bTimeOut = true;
			}

			// 回転軸に加算
			m_fRotValue -= m_fAddValue;

			// 角度の正規化
			m_fRotValue = RotNormalize(m_fRotValue);
			fAngleY = RotNormalize(fAngleY);

			rot.y = fAngleY;

			// 向きに保存
			SetRot(D3DXVECTOR3(rot.x, rot.y + (D3DX_PI * 0.5f), rot.z));

			pos.x = PlayerPos.x + sinf(m_fRotValue) * m_fDistance;
			pos.z = PlayerPos.z + cosf(m_fRotValue) * m_fDistance;

			CRock::SetPosition(pos);

			// 規定の距離に届いていなかったら
			if (m_fDistanceValue <= fDistance)
			{
				m_fDistanceValue += 0.05f;
			}

			// 回転する時間の加算
			m_nCntValueTime++;

			//m_pCursor->SetPosition(pos);
		}

	}

	// 時計回りがtrueで反時計回りがfalse または 時計回りがtrueでSPACEが離されていたら　または　時計回りがfalseで強制射出なら
	if ((m_bSign0 == true && m_bCheck2 == false) || (m_bSign0 == true && pInputKeyboard->GetRelease(DIK_SPACE) == true) || (m_bSign0 == true && m_bTimeOut == true))
	{
		// 時計回りの判定をtrueに
		m_bRelease[0] = true;
		m_bCheck1 = false;
		m_bCheck0 = false;
	}
	// 反時計回りがtrueで時計回りがfalse または　反時計回りがtrueでSPACEが離されていたら　または　反時計回りがfalseで強制射出なら
	if ((m_bSign1 == true && m_bCheck2 == false) || (m_bSign1 == true && pInputKeyboard->GetRelease(DIK_SPACE) == true) || (m_bSign1 == true && m_bTimeOut == true))
	{
		// 反時計回りの判定をtrueに
		m_bRelease[1] = true;
		m_bCheck0 = false;
		m_bCheck1 = false;
	}

	// 時計回りの判定がtrueで反時計回りの判定がfalseなら
	if (m_bRelease[0] == true)
	{
		//m_pCursor->SetLook(false);

		// 移動量に代入
		move.x = sinf(m_fRotValue + (D3DX_PI * fHalf)) * (m_fMove * (m_fAddValue * MaxSpeedValue));
		move.z = cosf(m_fRotValue + (D3DX_PI * fHalf)) * (m_fMove * (m_fAddValue * MaxSpeedValue));

		// 移動量を保存
		CRock::SetMove(move);
	}
	// 反時計回りの判定がtrueで時計回りの判定がfalseなら
	if (m_bRelease[1] == true)
	{
		//m_pCursor->SetLook(false);

		// 移動量に代入
		move.x = sinf(m_fRotValue - (D3DX_PI * fHalf)) * (m_fMove * (m_fAddValue * MaxSpeedValue));
		move.z = cosf(m_fRotValue - (D3DX_PI * fHalf)) * (m_fMove * (m_fAddValue * MaxSpeedValue));

		// 移動量を保存
		CRock::SetMove(move);
	}
}

//=================================================
// 塵の隕石同士の破壊処理
//=================================================
bool CMeteoRock::CollisionMeteo(D3DXVECTOR3 pos)
{
	if (m_bRelease[0] == true || m_bRelease[1] == true)
	{
		// 自分の位置を取得 & ローカル変数の初期化
		auto Mypos = GetPosition();
		auto DestPos = VEC3_NULL;

		// 自分と対象オブジェクトとの位置の差分を計算
		DestPos = pos - Mypos;

		// オブジェクト同士の間の距離を計算
		float fLength = D3DXVec3Length(&DestPos);

		// 計算結果
 		if (fLength < 60.0f)
		{
			// 爆発を生成
			CExplosionManager::Instance()->Init(pos, D3DXVECTOR2(0.125f, 1.0f), 60.0f, 60.0f, "data\\TEXTURE\\explosion000.png", CBillboard::TYPE_NONE);
			
			if (m_nSpornTime < 0)
			{
				// スコアを加算
				CScoreManager::Instance()->GetScore()->AddScore(300);
			}

			m_bCollision = true;
			return m_bCollision;
		}
	}

	return m_bCollision;
}