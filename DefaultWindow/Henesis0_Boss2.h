#pragma once
#include "Monster.h"
#include <Windows.h> // HDC에 빨간줄 떠서 임시로 포함함

// 네모로 나는 보스 몬스터

class CHenesis0_Boss2 : public CMonster
{
public:
	CHenesis0_Boss2();
	virtual ~CHenesis0_Boss2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD		m_dwTime;

	float		m_fRootX;
	float		m_fRootY;

	float		m_fRangeX;
	float		m_fRangeY;

	float		m_fAngle;
	float		m_fDistance;
};