#include "stdafx.h"
#include "CHenesis3_Mon.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "LineMgr.h"




CHenesis3_Mon::CHenesis3_Mon()
	: m_dwTime(0)
	, m_dwAttackDelay(GetTickCount())
	, m_bLineCol(false)
	, m_pPreLine(nullptr)
	, m_fLadningTime(0.f)
{
}

CHenesis3_Mon::~CHenesis3_Mon()
{
}

void CHenesis3_Mon::Initialize()
{
	m_tInfo = { 900.f, 1100.f, 100.f, 100.f };
	CMonster::Initialize();   // HP UI¼¼ÆÃ


	m_fSpeed = 1.f;
	m_fMaxHp = 100.f;
	m_fHp = m_fMaxHp;

	


	
	
	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Monster.bmp");
		
	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Monster_dead.bmp");
		
	
	
	m_eObjType = OBJID::OBJ_MONSTER;
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Monster_walk_left", m_pTex[0], Vec2(0.f, 74.f), Vec2(67.5f, 74.f), Vec2(67.5f, 0.f), 1.f, 4);

	GetAnimator()->CreateAnimation(L"Monster_dead", m_pTex[1], Vec2(0.f, 0.f), Vec2(66.f, 70.3f), Vec2(0.f, 70.3f), 1.f, 3);
	GetAnimator()->Play(L"Monster_walk_left");

}

int CHenesis3_Mon::Update()
{
	if (m_bDead)
	{
		GetAnimator()->Play(L"Monster_dead");

		if( m_dwTime == 0 )
			m_dwTime = GetTickCount();

		if (m_dwTime + 1000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			return OBJ_DEAD;
		}
	}

	if (m_dwAttackDelay + 10000 < GetTickCount())
	{
		hitGroudAttack();
		m_dwAttackDelay = GetTickCount();
	}



	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CHenesis3_Mon::Late_Update()
{
	float pY = 0.f;

	m_bLineCol = CLineMgr::Get_Instance()->Collision_LineMonster(this, m_tInfo.fX, m_tInfo.fY, &pY, &m_fTargetX);

	if (m_bLineCol)
	{
		if (5 > abs(m_fTargetX - m_tInfo.fX))
		{
			m_bArrival = true;
		}
		else
			m_bArrival = false;

		if (m_fTargetX > m_tInfo.fX)
			m_tInfo.fX += m_fSpeed;

		else if (m_fTargetX < m_tInfo.fX)
			m_tInfo.fX -= m_fSpeed;



		m_tInfo.fY = pY - m_tInfo.fCX / 2;
		m_fTime = 0.f;
	}
	else
	{
		m_tInfo.fY -= 10.f * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
		m_fTime += 0.2f;
	}


	GetAnimator()->Update();
}


void CHenesis3_Mon::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}


void CHenesis3_Mon::Release()
{
	                  
}


void CHenesis3_Mon::hitGroudAttack()
{
	m_tInfo.fY -= 20 * m_fLadningTime - ((9.8f * m_fLadningTime * m_fLadningTime) * 0.5f);
	m_fLadningTime += 0.2f;

	
	


	//m_fTime = 0.f;
	//m_tInfo.fY = pY - m_tInfo.fCX / 2;
}
