#include "stdafx.h"
#include "Henesis0Mon12.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

// ���Ϸ� ���� �Ķ� ����

CHenesis0Mon12::CHenesis0Mon12()
	: m_dwTime(0)
	, m_fStartX(1200.f), m_fStartY(1200.f)
	, m_fT(0.f)
{
}

CHenesis0Mon12::~CHenesis0Mon12()
{
	Release();
}

void CHenesis0Mon12::Initialize()
{
	

	m_tInfo = { m_fStartX, m_fStartY, 80.f, 100.f }; // 100.f~300.f~500.f
	CMonster::Initialize();   // HP UI����
	m_fSpeed = -3.f;

	m_fMaxHp = 20.f;
	m_fHp = m_fMaxHp;

	m_eObjType = OBJID::OBJ_MONSTER;


	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/henesis0mon1.bmp"); // ������ ���� �̹���

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/henesis0mon1_dead.bmp"); // ������ ���� �̹���

	CreateAnimator();
	// Ű(�����̸��̶� �����ϰ� �ض�), ���° �ؽ���, ��ǥ(�»����ġ), ��ǥ(�ڸ� ���μ��� ����), ��ǥ(���� �̹��������� �Ÿ�), 1.f, �����Ӱ���(���伥���� ���ٷ� ��ġ�ض�))  
	GetAnimator()->CreateAnimation(L"henesis0mon1", m_pTex[0], Vec2(0.f, 0.f), Vec2(80.f, 100.f), Vec2(80.f, 0.f), 1.f, 2);
	GetAnimator()->CreateAnimation(L"henesis0mon1_dead", m_pTex[1], Vec2(0.f, 0.f), Vec2(80.f, 100.f), Vec2(80.f, 0.f), 1.f, 2);
	GetAnimator()->Play(L"henesis0mon1");

}

int CHenesis0Mon12::Update()
{
	// ���� �̵� �� ���� ��ȯ

	m_fT += 0.01f;
	m_tInfo.fX = m_fStartX + (100.f * sin(3.f * m_fT + (PI * 0.5)));
	m_tInfo.fY = m_fStartY + (200.f * sin(4.f * m_fT ));


	if (m_bDead)
	{
		GetAnimator()->Play(L"henesis0mon1_dead");

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

void CHenesis0Mon12::Late_Update()
{
}

void CHenesis0Mon12::Render(HDC hDC)
{
	//HBRUSH hNewBrush = CreateSolidBrush(RGB(255, 0, 0));
	//HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//SelectObject(hDC, hOldBrush); // ������ ����ϴ���(Newpen)�� ������  
	//DeleteObject(hNewBrush);

	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CHenesis0Mon12::Release()
{
}
