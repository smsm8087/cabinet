#pragma once
class cPlayer;
class cMap;
class cItem;
class cImage;

class cMainPlay
{
private:
	cPlayer*	m_pPlayer;
	cPlayer*	m_pPlayer2;
	cMap*		m_pMap;
	cImage*		m_pTree13;
	cImage*		m_pPlayerMark;
	cImage*		m_pSecondMark;
	cImage*		m_pPlayerWin;
	cImage*		m_pSecondPlayerWin;
	float		m_fWinTime;
	vector<cItem*>	m_vecItem;
	bool		m_isitem;

	//die
	bool		m_isBeforeDiePlayer;
	bool		m_isBeforeDieSecondPlayer;
	GETSET(bool, m_isPlayerDie, isPlayerDie);
	GETSET(bool, m_isSecondPlayerDie, isSecondPlayerDie);
	GETSET(bool, m_isWantExit, isWantExit);

	//sound
	FMOD_SYSTEM*	m_pSystem;
	FMOD_BOOL       isplay;
	FMOD_BOOL       issecondplay;

	FMOD_BOOL       ispopplay;
	FMOD_BOOL       isitemplay;
	FMOD_BOOL       isseconditemplay;
	FMOD_BOOL       ispopbombplay;
	FMOD_BOOL       issecondpopbombplay;
	vector<FMOD_SOUND*>		m_vecSound;
	vector<FMOD_CHANNEL*>	m_vecChannel;


	//z-ordering
	bool			m_isPlayerfirst;

public:
	cMainPlay();
	~cMainPlay();

	void Init(CHARNAME player, CHARNAME secondplayer);
	void Update();
	void Render(HDC hdc);
	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void FirstPlayer();
	void SecondPlayer();
	void BombToBombPlayer();
	void BombToBombSecondPlayer();
	void PlayerBombToSecondPlayer();
	void SecondBombPlayerToPlayer();
	void PlayerToSecondPlayer();
	void CreateItem(int col, int row);
	void PlayerToItemCollision();
	void SecondPlayerToItemCollision();
	void ItemStatus(int num);
	void SecondItemStatus(int num);
	void ItemToBombCollision();
	void KeyDownPlayer();
	void KeyDownSecondPlayer();
};

