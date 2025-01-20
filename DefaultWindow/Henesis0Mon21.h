#pragma once
#include "Monster.h"
#include <Windows.h> // HDC�� ������ ���� �ӽ÷� ������

// �¿�� ���� ���� ����

class CHenesis0Mon21 : public CMonster
{
public:
	CHenesis0Mon21();
	virtual ~CHenesis0Mon21();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	DWORD		m_dwTime;

	float		m_fStartX;
	float		m_fStartY;

	// Rose Curve
	// Acos(kt)cos(t), Acos(kt)sin(t)
	float		m_fT;

};