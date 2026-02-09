//=================================================
//
// [player.cpp]
// Author:chikada shouya
//
//=================================================
#include "player.h"
#include "rock.h"
#include "game.h"
#include "input.h"
#include "easing.h"
#include "result.h"
#include "camera.h"
#include "manager.h"
#include "collider.h"
#include "debugproc.h"
#include "lifemanager.h"

#include "meteomanager.h"
#include "pausemanager.h"
#include "pillermanager.h"

namespace 
{
	float fRotHalf = 0.5f;		// 移動した方向に向かせるときに使用する変数
	float fInput = 0.0001f;		// 移動処理に使うキーが入力されてるか比較する用の変数
	float nMaxSpeed = 15.0f;	// プレイヤーのマックススピード
	int nMaxStamina = 545;		// スタミナのマックス数
	int nCntTime = 120;			// クールタイムが120秒を過ぎていたら

}
//=================================================
// コンストラクタ
//=================================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
	m_pMotion = nullptr;

	m_pos = VEC3_NULL;
	m_rot = VEC3_NULL;
	m_move = VEC3_NULL;
	m_size = VEC3_NULL;
	m_posOld = VEC3_NULL;
	m_rotDest = VEC3_NULL;

	m_Diff = NULL;
	m_fAddLR = NULL;
	m_fAddUD = NULL;
	m_fAddMove = NULL;
	
	m_nLife = NULL;
	m_nNumber = NULL;
	m_nStamina = NULL;
	m_nLifeTime = NULL;
	m_nCTstamina = NULL;

	m_bLeave = true;
	m_bDamege = false;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=================================================
// デストラクタ
//=================================================
CPlayer::~CPlayer()
{

}

//=================================================
//  生成処理
//=================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = nullptr;
	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->Init();
		return pPlayer;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CPlayer::Init(void)
{
	m_pMotion = CMotion::Create("data\\MOTION\\Human.txt", &m_apModel[0], CModel::QUAT_NONE);	//whichMotion.txt || motion2.txt
	
	// ライフマネージャーの初期化
	CLifeManager::Instance()->Init();
	
	m_size = CModel::GetSize();
	m_nLife = 3;
	m_nNumber = 1;
	m_nLifeTime = 0;
	m_nStamina = nMaxStamina;

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CPlayer::Uninit(void)
{
	m_bLeave = false;

	// モデルの破棄
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}

	// モーションの破棄
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ライフマネージャーの破棄
	CLifeManager::Instance()->Uninit();

	//　破棄
	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CPlayer::Update(void)
{
	// モーションの更新
	m_pMotion->Update(&m_apModel[0]);

	CCamera* pCamera = CManager::GetCamera();
	auto matView = pCamera->GetMtxView();
	auto matProj = pCamera->GetMtxProj();

	//移動とモーションのセット
	MoveInput();

	// スタミナの処理
	Sutamina();

	m_nLifeTime--;

	if (m_nLifeTime > 0)
	{
		if (m_bDamege == false)
		{
			m_bDamege = true;
		}
		else if (m_bDamege == true)
		{
			m_bDamege = false;
		}

		for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
		{
			// ロックのポインタを取得
			CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

			pRock->SetCheck0(false);
			pRock->SetCheck1(false);
			pRock->SetCheck2(false);
		}
	}
	else
	{
		m_bDamege = false;
	}

	// フェード
	CFade* pFade = CManager::GetFade();

	//角度の正規化
	m_rot.y = RotNormalize(m_rot.y);

	//角度の調整
	m_Diff = m_rotDest.y - m_rot.y;

	m_Diff = RotNormalize(m_Diff);

	// 左右
	if (m_rotDest.y >= -1.0f && m_rotDest.y <= 1.0f)
	{
		m_fAddLR = 50.0f;
		m_fAddUD = 0.0f;
	}
	else if (m_rotDest.y >= 3.13f && m_rotDest.y <= 3.15f)
	{
		m_fAddLR = -50.0f;
		m_fAddUD = 0.0f;
	}
	else if ((m_rotDest.y >= 1.56f && m_rotDest.y <= 1.58f))
	{
		m_fAddLR = 0.0f;
		m_fAddUD = -50.0f;
	}
	else if ((m_rotDest.y <= -1.56f && m_rotDest.y >= -1.58f))
	{
		m_fAddLR = 0.0f;
		m_fAddUD = 50.0f;
	}

	if (CPauseManager::GetEnable())
	{
		for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
		{
			// ロックのポインタを取得
			CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

			pRock->SetCheck0(false);
			pRock->SetCheck1(false);
			pRock->SetCheck2(false);
		}

		CPauseManager::SetEnable(false);
	}

	//プレイヤーの向き
	m_rot.y += m_Diff * 0.25f;

	// 移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.09f;
	m_move.z += (0.0f - m_move.z) * 0.09f;

	// 位置を更新
	m_pos += m_move;

	// 画面外に行かないように制限
	LimitPlayerToCamera(&m_pos,&matView,&matProj);

	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		// 隕石(塵)取得
		CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

		if (pRock == nullptr)break;
		
		CCollider::SetCollisionSource(pRock->GetPosition(),pRock->GetPosOld(),pRock->GetSize());

		// 塵との当たり判定
		if (CCollider::Collision(&m_pos, &m_posOld, &m_move, &m_size))
		{
			// 無敵時間が終わっていたら
			if (m_nLifeTime <= 0)
			{
				m_nLife--;

				CLifeManager::Instance()->GetLife(m_nLife)->Uninit();

				m_nLifeTime = 180;

				// ライフがゼロになったとき
				if (m_nLife <= 0)
				{
					CResult::SetDeath(true);
					pFade->SetFade(new CResult());
				}
			}
		}
	}

	for (int nCnt = 0; nCnt < MaxPillar; nCnt++)
	{
		// 柱の隕石を取得
		CMeteoPillar* pPillar = CPillarManager::Instance()->GetPillar(nCnt);

		if (pPillar == nullptr)break;
	
		// 当たり判定される側の設定
		CCollider::SetCollisionSource(pPillar->GetPosition(), pPillar->GetPosOld(), pPillar->GetSize());

		// 柱との当たり判定
		if (CCollider::Collision(&m_pos, &m_posOld, &m_move, &m_size))
		{
			// 無敵時間が終わっていたら
			if (m_nLifeTime <= 0)
			{
				m_nLife -= 1;

				CLifeManager::Instance()->GetLife(m_nLife)->Uninit();

				m_nLifeTime = 180;

				// ライフがゼロになったとき
				if (m_nLife <= 0)
				{
					CResult::SetDeath(true);
					pFade->SetFade(new CResult());
				}
			}
			
		}

	}
	//前回の位置を保存	位置更新の上で書く
	m_posOld = m_pos;
		
	// 位置の設定
	SetPosition(m_pos);
}

//=================================================
// 描画処理
//=================================================
void CPlayer::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	if (m_bDamege == false)
	{
		//モデルパーツを描画
		for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
		{
			m_apModel[nCnt]->Draw();
		}
	}

	// 保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);

	// デバッグフォントの表示
	CDebugProc::Print("-----------{ プレイヤー }-----------\n");
	CDebugProc::Print("座標{ %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("目的の座標:{ %.2f,%.2f,%.2f }\n", m_rotDest.x, m_rotDest.y, m_rotDest.z);
	CDebugProc::Print("命:{ %d }\n", m_nLife);

}

//=================================================
// 移動処理
//=================================================
void CPlayer::MoveInput(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	//カメラの情報取得
	CCamera* pCamera = CManager::GetCamera();

	auto matView = pCamera->GetMtxView();

	if (m_fAddMove <= 10.0f)
	{
		m_fAddMove += 0.1f;
	}

	MoveBasedOnCamera(&matView,m_fAddMove);

	// 動いてないときはニュートラルに
	if (pInputKeyboard->GetPress(DIK_W) == false &&
		pInputKeyboard->GetPress(DIK_S) == false &&
		pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_D) == false)
	{
		m_pMotion->Set(CMotion::MOTIONTYPE_NEUTRAL);
		
		m_fAddMove = 0.0f;
	}

	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		// ロックのポインタを取得
		CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

		if (pRock->GetSign0())break;
		if (pRock->GetSign1())break;
		if (pInputKeyboard->GetPress(DIK_LSHIFT) != false)break;
		
		// スタミナクールタイムの回復
		m_nCTstamina++;
		

	}

}

//=================================================
// 右＆後ろの判定
//=================================================
void CPlayer::VectorJudgeR(void)
{
	//半径の算出変数
	float PRadius = {};
	float RRadius = {};

	float fDisX = {};
	float fDisY = {};
	float fDisZ = {};

	float fRadX = {};

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 RockPos = {};

	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		// ロックのポインタを取得
		CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

		if (CMeteoManager::Instance()->GetRock(nCnt)->GetCheck1() == false)
		{
			if (pRock != nullptr)
			{
				PRadius = 45.0f;
				RRadius = 15.0f;

				//岩の位置の取得
				RockPos = pRock->GetPosition();

				//範囲計算
				fDisX = (RockPos.x - m_fAddLR) - m_pos.x;
				fDisY = RockPos.y - m_pos.y;
				fDisZ = (RockPos.z - m_fAddUD) - m_pos.z;

				//二つの半径を求める
				fRadX = PRadius + RRadius;

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					
					if (CMeteoManager::Instance()->GetRock(m_nNumber)->GetCheck0() == false && CMeteoManager::Instance()->GetRock(m_nNumber)->GetCheck1() == false)
					{
						m_nNumber = nCnt;
						pRock->SetCheck0(true);
					}

					break;
				}
			}

		}
	}
}

//=================================================
// 左＆前の判定
//=================================================
void CPlayer::VectorJudgeL(void)
{
	//半径の算出変数
	float PRadius = {};
	float RRadius = {};

	float fDisX = {};
	float fDisY = {};
	float fDisZ = {};

	float fRadX = {};

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 RockPos = {};

	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		// ロックのポインタを取得
		CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

		if (CMeteoManager::Instance()->GetRock(nCnt)->GetCheck0() == false)
		{
			if (pRock != nullptr)
			{
				PRadius = 45.0f;
				RRadius = 15.0f;

				//岩の位置の取得
				RockPos = pRock->GetPosition();

				//範囲計算
				fDisX = (RockPos.x + m_fAddLR) - m_pos.x;
				fDisY = RockPos.y - m_pos.y;
				fDisZ = (RockPos.z + m_fAddUD) - m_pos.z;

				//二つの半径を求める
				fRadX = PRadius + RRadius;

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					if (CMeteoManager::Instance()->GetRock(m_nNumber)->GetCheck0() == false && 
						CMeteoManager::Instance()->GetRock(m_nNumber)->GetCheck1() == false)
					{
						m_nNumber = nCnt;
						pRock->SetCheck1(true);
					}

					break;
				}
			}

		}
	}
}

//=================================================
// プレイヤー周りの判定
//=================================================
void CPlayer::VectorJudge(void)
{
	//半径の算出変数
	float PRadius = {};
	float RRadius = {};

	float fDisX = {};
	float fDisY = {};
	float fDisZ = {};

	float fRadX = {};

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 RockPos = {};


	for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
	{
		// ロックのポインタを取得
		CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

		if (pRock != nullptr)
		{
			PRadius = 200.0f;
			RRadius = 15.0f;

			//岩の位置の取得
			RockPos = pRock->GetPosition();

			//範囲計算
			fDisX = RockPos.x - m_pos.x;
			fDisY = RockPos.y - m_pos.y;
			fDisZ = RockPos.z - m_pos.z;

			//二つの半径を求める
			fRadX = PRadius + RRadius;

			if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				pRock->SetCheck2(true);
				break;
			}
			else
			{
				pRock->SetCheck2(false);
			}
		}

	}
	
}

//=================================================
// カメラ範囲内の行動制限
//=================================================
void CPlayer::LimitPlayerToCamera(D3DXVECTOR3* playerPos, D3DXMATRIX* pMatView, D3DXMATRIX* pMatProj)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DVIEWPORT9 vp;

	pDevice->GetViewport(&vp); // 現在のビューポート取得

	// 画面のビューポート領域（2D）
	float minX = 50.0f;
	float minY = 75.0f;
	float maxX = (float)vp.Width - 50.0f;
	float maxY = (float)vp.Height;

	// 1. ワールド座標 -> スクリーン座標への変換
	D3DXVECTOR3 screenPos;
	D3DXVec3Project(&screenPos, playerPos, &vp, pMatProj, pMatView, NULL);

	// 2. 画面外に出ていないかチェックし、クランプ（範囲内に固定）
	bool changed = false;
	if (screenPos.x < minX) { screenPos.x = minX; changed = true; }
	if (screenPos.x > maxX) { screenPos.x = maxX; changed = true; }
	if (screenPos.y < minY) { screenPos.y = minY; changed = true; }
	if (screenPos.y > maxY) { screenPos.y = maxY; changed = true; }

	// 3. 画面外に行っていた場合、新しいスクリーン座標を元に、
	//    3Dのワールド座標に逆投影する（斜めのカメラでも正しく制限される）
	if (changed) {
		D3DXVECTOR3 newWorldPos;
		D3DXVec3Unproject(&newWorldPos, &screenPos, &vp, pMatProj, pMatView, NULL);

		// y高さは制限しない（地面に沿わせる場合）
		playerPos->x = newWorldPos.x;
		playerPos->z = newWorldPos.z;
	}
}


//=================================================
// プレイヤー移動処理
//=================================================
void CPlayer::MoveBasedOnCamera(D3DXMATRIX* pViewMatrix, float speed)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	// 1. ビュー行列の逆行列を計算（カメラのワールド姿勢行列）
	D3DXMATRIX invViewMat;
	D3DXMatrixInverse(&invViewMat, NULL, pViewMatrix);

	// 2. 逆行列からカメラの方向ベクトルを抽出 (row-major)
	// 3行目がForward、1行目がRight
	D3DXVECTOR3 camForward = D3DXVECTOR3(invViewMat._31, invViewMat._32, invViewMat._33);
	D3DXVECTOR3 camRight = D3DXVECTOR3(invViewMat._11, invViewMat._12, invViewMat._13);

	// XZ平面の移動にするため、Y成分を0にする
	camForward.y = 0.0f;
	camRight.y = 0.0f;
	D3DXVec3Normalize(&camForward, &camForward);
	D3DXVec3Normalize(&camRight, &camRight);

	// 3. 移動方向の計算
	D3DXVECTOR3 moveDir = D3DXVECTOR3(0, 0, 0);

	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		moveDir += camForward;
		m_rotDest.y = rot.y + D3DX_PI;
	}
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		moveDir -= camForward;
		m_rotDest.y = rot.y;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		moveDir += camRight;
		m_rotDest.y = rot.y - D3DX_PI * fRotHalf;
	}
	if (pInputKeyboard->GetPress(DIK_A) == true) 
	{
		moveDir -= camRight; 
		m_rotDest.y = rot.y + D3DX_PI * fRotHalf;
	}

	// 移動入力がある場合
	if (D3DXVec3LengthSq(&moveDir) > fInput)
	{
		// 移動の正規化
		D3DXVec3Normalize(&moveDir, &moveDir);

		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);
		
		// 4. 位置の更新
		m_move = moveDir * speed;
	}
}

//=================================================
// プレイヤースタミナ処理全般
//=================================================
void CPlayer::Sutamina(void)
{
	if (m_nStamina > NULL)
	{// スタミナがあれば
		VectorJudgeL();	// 小さな隕石がプレイヤーの左と前の範囲に入ったとき
		VectorJudgeR();	// 小さな隕石がプレイヤーの右と後ろの範囲に入ったとき
		VectorJudge();	// 小さな隕石がプレイヤーの全体周りの範囲に入ったとき
	}
	else
	{
		for (int nCnt = 0; nCnt < MAX_METEO; nCnt++)
		{
			// ロックのポインタを取得
			CMeteoRock* pRock = CMeteoManager::Instance()->GetRock(nCnt);

			pRock->SetCheck0(false);
			pRock->SetCheck1(false);
			pRock->SetCheck2(false);
		}
	}

	if (m_nCTstamina > nCntTime && m_nStamina < nMaxStamina)
	{
		m_nStamina++;
	}

}