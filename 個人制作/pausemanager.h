//=================================================
//
//	pausemanager.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _PAUSEMANAGER_H_
#define _PAUSEMANAGER_H_

#include "main.h"
#include "pause.h"

// マクロ
#define MAX_PAUSE (4)
class CPauseManager
{
public:

	//ポーズメニュー
	typedef enum
	{
		MENU_CONTINUE = 0,	//ゲームに戻る
		MENU_RETRY,			//ゲームをやり直す
		MENU_QUIT,			//タイトル画面に戻る
		MENU_MAX
	}MENU;

	CPauseManager();
	~CPauseManager();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetEnablePause(bool bPause) { m_bPause = bPause; }
	void SetEnablePause(void);
	
	// セッター(静的)
	static void SetEnable(bool bEnable) { m_bEnable = bEnable; }

	// ゲッター(静的)
	static bool GetPause(void) { return m_bPause; }
	static bool GetCheck(void) { return m_bCheck; }
	static bool GetEnable(void) { return m_bEnable; }

private:
	CPause* m_pPause[MAX_PAUSE];
	int m_SelectIdx;

	static bool m_bPause;
	static bool m_bCheck;
	static bool m_bEnable;

};

#endif