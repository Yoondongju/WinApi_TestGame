#pragma once
#include "Monster.h"
#include <Windows.h> // HDC�� ������ ���� �ӽ÷� ������

// ���Ϸ� ���� �Ķ� ����

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