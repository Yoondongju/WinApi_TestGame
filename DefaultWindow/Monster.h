#pragma once
#include "Obj.h"

class CTexture;

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;


public:
	void SetArrival(bool _b) { m_bArrival = _b; }
	bool GetArrival() { return m_bArrival; }






protected:
	vector<CTexture*>	m_pTex;

	float				m_fTime;

	bool				m_bArrival;

	float				m_fTargetX;

};

