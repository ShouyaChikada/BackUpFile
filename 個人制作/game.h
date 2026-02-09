//=================================================
//
//	game.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "object3D.h"
#include "objectx.h"
#include "meshfield.h"
#include "object.h"

#include "scene.h"
#include "fade.h"
#include "jimen.h"
#include "pausemanager.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	static CObject3D* GetObj3D(void) { return m_pObj3D; }
	static CObjectX* GetObjX(void) { return m_pObjX; }
	static CMeshField* GetMeshField(void) { return m_pMeshField; }
	static CGrand* GetGrand(void) { return m_pGrand; }
	static CPauseManager* GetPauseManager(void) {return m_pPauseManager; }
	static bool GetCheck(void) { return m_bCheck; }

private:
	static CObject3D* m_pObj3D;					// オブジェクト3Dのポインタ
	static CObjectX* m_pObjX;					// オブジェクトXのポインタ
	static CMeshField* m_pMeshField;			// メッシュフィールドのポインタ
	static CGrand* m_pGrand;					// 地面へのポインタ
	static CPauseManager* m_pPauseManager;		// ポーズマネージャーのポインタ
	static bool m_bCheck;						// ゴール判定
};

#endif

