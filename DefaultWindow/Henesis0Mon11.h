#pragma once
#include "Monster.h"
#include <Windows.h> // HDC에 빨간줄 떠서 임시로 포함함

// 상하로 나는 파란 몬스터

class CHenesis0Mon11 : public CMonster
{
public:
	CHenesis0Mon11();
	virtual ~CHenesis0Mon11();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD		m_dwTime;
	
	float		m_fStartX;
	float		m_fStartY;

	// Lissajous Curve
	// asin(bt+@), csin(dt)
	float m_fT;

};