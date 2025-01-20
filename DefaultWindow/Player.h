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

	void		Wall_Check();  // ���ؽ�

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

	float	fOffSetminX;       // �츮 Ŭ���̾�Ʈ 800 x 600   
	float	fOffSetmaxX;
						
	float	fOffSetminY;
	float	fOffSetmaxY;

	// y = �Ŀ�(��) * sin(90) * �ð� - (9.8f * �ð� * �ð�) / 2

};

// 1. �÷��̾� �߽����� �����ϴ� ��ü �����ϱ�
// 2. ��ũ�� �̻��� �����ϱ�
// 3. �÷��̾ ����ٴϴ� ���� �����ϱ�