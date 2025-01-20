#include "stdafx.h"
#include "CHenesis2_Mon.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "LineMgr.h"
#include "ObjMgr.h"
#include "CMonUI.h"

CHenesis2_Mon::CHenesis2_Mon()
{
}

CHenesis2_Mon::~CHenesis2_Mon()
{
}

void CHenesis2_Mon::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;
	CMonster::Initialize();   // HP UI¼¼ÆÃ


	
	m_fSpeed = 1.f;
	m_fMaxHp = 100.f;
	m_fHp = m_fMaxHp;

	m_eObjType = OBJID::OBJ_MONSTER;


	CreateAnimator();

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Monster_stage02_pig_walk.bmp");
	GetAnimator()->CreateAnimation(L"Monster_stage02_00_pig_walk",
		m_pTex.back(), //X 10Ä­ 1Ä­´ç 119.1 y 5Ä­ 1Ä­´ç 194.6
		Vec2(0.f, 0.f),  //½ÃÀÛÀ§Ä¡
		Vec2(74.33f, 63.f),//½½¶óÀÌ½º»çÀÌÁî
		Vec2(74.33f, 0.f), //½ºÅÇ
		1.f,
		3);


	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Monster_stage02_pig_dead.bmp");
	GetAnimator()->CreateAnimation(L"Monster_stage02_00_pig_dead",
		m_pTex.back(),
		Vec2(0.f, 0.f),
		Vec2(75.f, 66.f),
		Vec2(75.f, 0.f),
		1.f, 3);


	GetAnimator()->Play(L"Monster_stage02_00_pig_walk");
}

int CHenesis2_Mon::Update()
{
	if (m_bDead)
	{
		static DWORD m_dwTime = GetTickCount();

		GetAnimator()->Play(L"Monster_stage02_00_pig_dead");

		if (m_dwTime + 1000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			return OBJ_DEAD;
		}

	}



	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CHenesis2_Mon::Late_Update()
{
	float pY = 0.f;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_LineMonster(this, m_tInfo.fX, m_tInfo.fY, &pY, &m_fTargetX);


	if (bLineCol)
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

void CHenesis2_Mon::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CHenesis2_Mon::Release()
{
}
