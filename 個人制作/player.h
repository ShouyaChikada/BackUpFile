//=================================================
//
// [player.h]
// Author:chikada shouya
//
//=================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "object.h"
#include "objectx.h"
#include "model.h"
#include "motion.h"

class CPlayer :public CObject
{
public:
	typedef enum
	{
		TYPE_MONE = 0,
		TYPE_EXPROSION,
		TYPE_THUMDER,
		TYPE_WINDOW,
		TYPE_WATER,
		TYPE_MAX,
	}TYPE;

	CPlayer(int nPriority = 3);
	~CPlayer();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Sutamina(void);

	/// <summary>
	/// // プレイヤーを生成する関数
	/// </summary>
	/// <param name="pos = 現在の位置"></param>
	/// <param name="rot = 角度"></param>
	/// <returns></returns>
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	// 移動処理
	void MoveInput(void);

	/// <summary>
	/// プレイヤーをカメラ外に出さないようにする関数
	/// </summary>
	/// <param name="playerPos = プレイヤーの現在/次フレームの座標"></param>
	/// <param name="matView = カメラのビュー行列"></param>
	/// <param name="matProj = カメラの投影行列"></param>
	/// <returns></returns>		 
	void LimitPlayerToCamera(D3DXVECTOR3* playerPos, D3DXMATRIX* pMatView, D3DXMATRIX* pMatProj);

	/// <summary>
	/// 移動の設定
	/// </summary>
	/// <param name="pViewMatrix = カメラーのビュー行列"></param>
	/// <param name="speed = 移動速度"></param>
	void MoveBasedOnCamera(D3DXMATRIX* pViewMatrix, float peed);

	// 右左の範囲
	void VectorJudgeR(void);
	void VectorJudgeL(void);
	void VectorJudge(void);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetNumber(int nNumber) { m_nNumber = nNumber; }
	void SetCTstaina(int nCTStamina) { m_nCTstamina = nCTStamina; }
	void SetSutamina(int nStamina) { m_nStamina -= nStamina; }

	// ゲッター
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

	int GetLife(void) { return m_nLife; }
	int GetNumber(void) { return m_nNumber; }
	int GetStamina(void) { return m_nStamina; }

private:
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_posOld;			// 目的の位置
	D3DXVECTOR3 m_move;				// 移動
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	D3DXVECTOR3 m_size;				// サイズ
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス

	CModel* m_apModel[MAX_PMODEL];	// モデルのポインタ
	CMotion* m_pMotion;				// モーションポインタ
	float m_fAddMove;				// 移動量の加算用変数
	float m_fAddLR;					// 左右の加算用変数
	float m_fAddUD;					// 前後の加算用変数
	float m_Diff;					// 差分の計算用変数

	int m_nLife;					// 命
	int m_nNumber;					// 回転してる塵の配列番号記録用の変数
	int m_nStamina;					// スタミナ(使用制限)
	int m_nLifeTime;				// 無敵時間
	int m_nCTstamina;				// スタミナを回復させるクールタイム

	bool m_bLeave;					// 生存フラグ
	bool m_bDamege;					// ダメージをくらってる判定
};

#endif