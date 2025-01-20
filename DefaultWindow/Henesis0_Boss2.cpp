#include "stdafx.h"
#include "Henesis0_Boss2.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

// ���Ϸ� ���� �Ķ� ����

CHenesis0_Boss2::CHenesis0_Boss2()
	: m_dwTime(0)
	, m_fRootX(4700.f), m_fRootY(1100.f)
	, m_fRangeX(200.f), m_fRangeY(200.f)
	, m_fAngle(120.f), m_fDistance(200.f)
{
}

CHenesis0_Boss2::~CHenesis0_Boss2()
{
	Release();
}

void CHenesis0_Boss2::Initialize()
{
	
	m_tInfo = { 0.f, 0.f, 225.f, 250.f }; // 100.f~300.f~500.f
	CMonster::Initialize();   // HP UI����

	m_fSpeed = 1.f;

	m_fMaxHp = 40.f;
	m_fHp = m_fMaxHp;

	m_eObjType = OBJID::OBJ_MONSTER;


	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/henesis0Boss.bmp"); // ������ ���� �̹���

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/henesis0Boss_dead.bmp"); // ������ ���� �̹���

	CreateAnimator();
	// Ű(�����̸��̶� �����ϰ� �ض�), ���° �ؽ���, ��ǥ(�»����ġ), ��ǥ(�ڸ� ���μ��� ����), ��ǥ(���� �̹��������� �Ÿ�), 1.f, �����Ӱ���(���伥���� ���ٷ� ��ġ�ض�))  
	GetAnimator()->CreateAnimation(L"henesis0Boss", m_pTex[0], Vec2(0.f, 0.f), Vec2(225.f, 250.f), Vec2(225.f, 0.f), 1.f, 2);
	GetAnimator()->CreateAnimation(L"henesis0Boss_dead", m_pTex[1], Vec2(0.f, 0.f), Vec2(225.f, 250.f), Vec2(225.f, 0.f), 1.f, 2);
	GetAnimator()->Play(L"henesis0Boss");

}

int CHenesis0_Boss2::Update()
{
	// ���� �̵� �� ���� ��ȯ

	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_fRootX + 3.f * m_fDistance * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_fRootY - m_fDistance * sin(m_fAngle * (PI / 180.f));

	if (m_bDead)
	{
		GetAnimator()->Play(L"henesis0Boss_dead");

		if (m_dwTime == 0)
			m_dwTime = GetTickCount();

		if (m_dwTime + 1000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			return OBJ_DEAD;
		}

	}


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CHenesis0_Boss2::Late_Update()
{
}

void CHenesis0_Boss2::Render(HDC hDC)
{
	//HBRUSH hNewBrush = CreateSolidBrush(RGB(255, 0, 0));
	//HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//SelectObject(hDC, hOldBrush); // ������ ����ϴ���(Newpen)�� ������  
	//DeleteObject(hNewBrush);

	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CHenesis0_Boss2::Release()
{
}
