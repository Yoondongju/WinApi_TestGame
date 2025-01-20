#pragma once

#include "Obj.h"

class CTexture;

class CBullet :	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	
public:
	float GetAttackInfo() { return m_fAttackInfo; }

private:
	CTexture*		m_pTex;
	float			m_fAttackInfo;

};

