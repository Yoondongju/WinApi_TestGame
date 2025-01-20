#pragma once
#include "Monster.h"

class CLine;

class CHenesis3_Mon : public CMonster
{
public:
	CHenesis3_Mon();
	virtual ~CHenesis3_Mon();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	
public:
	void	hitGroudAttack();

public:
	void SetPreLine(CLine* _p) { m_pPreLine = _p; }
	CLine* GetPreLine() { return m_pPreLine; }

private:
	DWORD		m_dwTime;
	DWORD		m_dwAttackDelay;
	bool		m_bLineCol;

	float		m_fLadningTime;

	CLine* m_pPreLine;
};

