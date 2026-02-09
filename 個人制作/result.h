//=================================================
//
//	result.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "resultmanager.h"

class CResult : public CScene
{
public:
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	// セッター
	static void SetDeath(bool bDeath) { m_bDeath = bDeath; }

	// ゲッター
	static bool GetCheck(void) { return m_bCheck; }

private:
	CResultManager* m_pResultManager;
	static bool m_bCheck;
	static bool m_bDeath;

};

#endif

