#include "stdafx.h"
#include "Henesis0Mon20.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

// 좌우로 나는 빨간 몬스터

CHenesis0Mon20::CHenesis0Mon20()
	: m_dwTime(0)
	, m_fStartX(2500.f), m_fStartY(1200.f)
	, m_fT(0.f)
{
}

CHenesis0Mon20::~CHenesis0Mon20()
{
	Release();
}

void CHenesis0Mon20::Initialize()
{
	

	m_tInfo = { m_fStartX, m_fStartY, 80.f, 100.f }; // 100.f~300.f~500.f
	CMonster::Initialize();   // HP UI세팅
	m_fSpeed = 2.f;

	m_fMaxHp = 50.f;
	m_fHp = m_fMaxHp;

	m_eObjType = OBJID::OBJ_MONSTER;


	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/henesis0mon2.bmp"); // 입히고 싶은 이미지

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/henesis0mon2_dead.bmp"); // 입히고 싶은 이미지

	CreateAnimator();
	// 키(사진이름이랑 동일하게 해라), 몇번째 텍스쳐, 좌표(좌상단위치), 좌표(자를 가로세로 길이), 좌표(다음 이미지까지의 거리), 1.f, 프레임개수(포토샵으로 한줄로 배치해라))  
	GetAnimator()->CreateAnimation(L"henesis0mon2", m_pTex[0], Vec2(0.f, 0.f), Vec2(80.f, 100.f), Vec2(80.f, 0.f), 1.f, 2);
	GetAnimator()->CreateAnimation(L"henesis0mon2_dead", m_pTex[1], Vec2(0.f, 0.f), Vec2(80.f, 100.f), Vec2(80.f, 0.f), 1.f, 2);
	GetAnimator()->Play(L"henesis0mon2");

}

int CHenesis0Mon20::Update()
{
	// 몬스터 이동 및 방향 전환

	m_fT += 0.01f;
	m_tInfo.fX = m_fStartX + (300.f * cos(3.f * m_fT) * cos(m_fT));
	m_tInfo.fY = m_fStartY + (300.f * cos(3.f * m_fT) * sin(m_fT));


	if (m_bDead)
	{
		GetAnimator()->Play(L"henesis0mon2_dead");

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

void CHenesis0Mon20::Late_Update()
{
}

void CHenesis0Mon20::Render(HDC hDC)
{
	//HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
	//HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//SelectObject(hDC, hOldBrush); // 기존에 사용하던것(Newpen)을 리턴함  
	//DeleteObject(hNewBrush);

	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CHenesis0Mon20::Release()
{
}
