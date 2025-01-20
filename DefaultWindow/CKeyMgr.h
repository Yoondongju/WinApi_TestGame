#pragma once

#include "Define.h"


enum class KEY_STATE
{
	NONE, // 이전에도 안눌렸고 지금도 안눌린 상태
	TAP,  // 이전에 안눌렸고 지금 누른상태
	HOLD, // 이전에도 눌럿꼬 지금고 누른상태
	AWAY, // 이전엔 눌렀고 지금 뗀 상태

	END
};

struct tKeyInfo
{
	KEY_STATE eKeyState;
	bool	bPrePush;
};


enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,
	Y,U,I,O,P,
	A,S,D,F,G,
	Z,X,C,V,B,

	LBUTTON,
	RBUTTON,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	END
};


class CKeyMgr
{
	SINGLE(CKeyMgr)


public:
	KEY_STATE GetKeyState(KEY _e) { return m_vecKey[(UINT)_e].eKeyState; }

public:
	void init();
	void Update();


private:
	vector<tKeyInfo> m_vecKey;


};

