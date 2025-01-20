#pragma once

#include "Obj.h"

#include "LineMgr.h"


class CTexture;


enum class PLAYER_STATE
{
	IDLE,
	WALK,
	STATE_END
};

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		Wall_Check();  // 이준식

public:
	void SetHitdelay(DWORD _dw) { m_dwHitdelay = _dw; }
	DWORD	GetHitdelay() { return m_dwHitdelay; }


public:
	friend bool CLineMgr::Collision_Line(float& fX, float& fY, float* pY, float* pX);

private:
	void		Key_Input();
	CObj*		Create_Bullet(DIRECTION eDir);
	CObj*		Create_Shield();
	void		Jump();
	void		Offset();

private:
	void		Calculate_Angle(POINT _pt);



private:
	POINT				m_tPosin;
	float				m_fDistance;

	bool				m_bJump;
	bool				m_bRope;
	bool				m_bLineride;

	float				m_fPower;
	float				m_fTime;

	vector<CTexture*>	m_vecTexture;

	PLAYER_STATE		m_CurState;
	PLAYER_STATE		m_PreState;

	DWORD				m_dwTime;

	DWORD				m_dwHitdelay;

	float	fOffSetminX;       // 우리 클라이언트 800 x 600   
	float	fOffSetmaxX;
						
	float	fOffSetminY;
	float	fOffSetmaxY;

	// y = 파워(힘) * sin(90) * 시간 - (9.8f * 시간 * 시간) / 2

};

// 1. 플레이어 중심으로 공전하는 물체 구현하기
// 2. 스크류 미사일 구현하기
// 3. 플레이어를 따라다니는 몬스터 구현하기