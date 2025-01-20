#pragma once
#include "Monster.h"
#include <Windows.h> // HDC�� ������ ���� �ӽ÷� ������

// �׸�� ���� ���� ����

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