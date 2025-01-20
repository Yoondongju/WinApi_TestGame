#pragma once

#include "Define.h"

class CAnimator;

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void			Set_Dir(DIRECTION eDir)
	{
		m_eDir = eDir;
	}

	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }	  // ¹¹³Ä ÀÌ°Å ¿Ö ÁßÃ¸´ï (Rect Ãæµ¹¿¡¼­ ¾²³×)
	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }	  // ¹¹³Ä ÀÌ°Å ¿Ö ÁßÃ¸´ï (Rect Ãæµ¹¿¡¼­ ¾²³×)


	RECT			Get_Rect() { return m_tRect; }
	INFO			Get_Info() { return m_tInfo; }
	bool			Get_Dead() { return m_bDead; }
	void			Set_Dead() { m_bDead = true;  }
	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void			Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;


public:
	void CreateAnimator();
	CAnimator* GetAnimator() { return m_pAnimator; }


public:
	void SetObjType(OBJID _e) { m_eObjType = _e; }
	OBJID GetObjType() { return m_eObjType; }

public:
	float GetMaxHp() { return m_fMaxHp; }
	float GetHp() { return m_fHp; }

	void SetMaxHP(float _f) { m_fMaxHp = _f; }
	void SetHp(float _f) { m_fHp = _f; }

public:
	void Set_CXY(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}


protected:
	void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;

	float		m_fSpeed;
	bool		m_bDead;

	float		m_fAngle;

	CObj*		m_pTarget;


	CAnimator* m_pAnimator;

	OBJID	m_eObjType;

	float				m_fMaxHp;
	float				m_fHp;

};

