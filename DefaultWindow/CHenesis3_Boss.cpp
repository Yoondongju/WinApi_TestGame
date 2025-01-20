#include "stdafx.h"
#include "CHenesis3_Boss.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "LineMgr.h"

#include "ObjMgr.h"


CHenesis3_Boss::CHenesis3_Boss()
	: m_pTarget(nullptr)
	, m_eState(BOSS_STATE::STAND)
	, m_iDir(1)
	, m_bAttacking(false)
	, m_fAttackInfo(10.f)
	, m_fAttack2Info(20.f)
{
}

CHenesis3_Boss::~CHenesis3_Boss()
{
}

void CHenesis3_Boss::Initialize()
{
	m_tInfo = { 1300.f, 750.f, 300.f, 400.f };
	CMonster::Initialize();   // HP UI¼¼ÆÃ



	m_fSpeed = 3.f;
	m_fMaxHp = 1000.f;
	m_fHp = m_fMaxHp;
	m_eObjType = OBJID::OBJ_BOSS;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	m_FindRange.fX = 400.f;
	m_FindRange.fY = m_tInfo.fCY;

	
	CreateAnimator();

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_stand_left.bmp");
	GetAnimator()->CreateAnimation(L"Boss_stand_left", m_pTex.back(), Vec2(0.f, 0.f), Vec2(139.f, 181.f), Vec2(139.f, 0.f), 1.f, 8);

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_stand_right.bmp");
	GetAnimator()->CreateAnimation(L"Boss_stand_right", m_pTex.back(), Vec2(0.f, 0.f), Vec2(139.f, 181.f), Vec2(139.f, 0.f), 1.f, 8);

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_walk_left.bmp");
	GetAnimator()->CreateAnimation(L"Boss_walk_left", m_pTex.back(), Vec2(0.f, 0.f), Vec2(133.f, 179.f), Vec2(133.f, 0.f), 1.f, 8);

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_walk_right.bmp");
	GetAnimator()->CreateAnimation(L"Boss_walk_right", m_pTex.back(), Vec2(0.f, 0.f), Vec2(133.f, 179.f), Vec2(133.f, 0.f), 1.f, 8);



	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_Attack_left.bmp");
	GetAnimator()->CreateAnimation(L"Boss_Attack_left", m_pTex.back(), Vec2(0.f, 0.f), Vec2(1065.f, 828.f), Vec2(0.f, 828.f), 1.f, 4);

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_Attack_right.bmp");
	GetAnimator()->CreateAnimation(L"Boss_Attack_right", m_pTex.back(), Vec2(0.f, 0.f), Vec2(1065.f, 828.f), Vec2(0.f, 828.f), 1.f, 4);

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_Attack2_left.bmp");
	GetAnimator()->CreateAnimation(L"Boss_Attack2_left", m_pTex.back(), Vec2(0.f, 0.f), Vec2(774.f, 336.f), Vec2(0.f, 336.f), 1.f, 7);

	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Boss/Boss_Attack2_right.bmp");
	GetAnimator()->CreateAnimation(L"Boss_Attack2_right", m_pTex.back(), Vec2(0.f, 0.f), Vec2(774.f, 336.f), Vec2(0.f, 336.f), 1.f, 7);


	GetAnimator()->Play(L"Boss_stand_left");
}

int CHenesis3_Boss::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	if(m_pTarget)
		FindTargetPlayer();


	switch (m_eState)
	{
	case STAND:
	{
		if (1 == m_iDir)
			GetAnimator()->Play(L"Boss_stand_right");
		else
			GetAnimator()->Play(L"Boss_stand_left");
	}	
		break;

	case WALK:
	{
		if (1 == m_iDir)
			GetAnimator()->Play(L"Boss_walk_right");
		else
			GetAnimator()->Play(L"Boss_walk_left");
	}
		break;

	case ATTACK:
	{
		if (1 == m_iDir)
			GetAnimator()->Play(L"Boss_Attack_right");
		else
			GetAnimator()->Play(L"Boss_Attack_left");
	}

		break;

	case ATTACK2:
	{
		if (1 == m_iDir)
			GetAnimator()->Play(L"Boss_Attack2_right");
		else
			GetAnimator()->Play(L"Boss_Attack2_left");
	}
		break;

	case END:
		break;

	default:
		break;
	}



	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CHenesis3_Boss::Late_Update()
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
		{
			m_iDir = 1;
			m_tInfo.fX += m_fSpeed;
		}
			
		else if (m_fTargetX < m_tInfo.fX)
		{
			m_iDir = -1;
			m_tInfo.fX -= m_fSpeed;
		}

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


void CHenesis3_Boss::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CHenesis3_Boss::Release()
{
}

void CHenesis3_Boss::FindTargetPlayer()
{
	INFO targetInfo = m_pTarget->Get_Info();

	if( m_FindRange.fX > abs(targetInfo.fX - m_tInfo.fX) 
		&& m_FindRange.fY > abs(targetInfo.fY - m_tInfo.fY) )
	{
		StartAttack();
	}
	else
	{
		ExitAttack();
	}
	
	
}

void CHenesis3_Boss::StartAttack()
{
	m_bAttacking = true;

	if (GetAnimator()->GetCurAnimation()->GetFinish())
	{
		m_eState = (BOSS_STATE)(rand() % BOSS_STATE::ATTACK2 / 2.f + BOSS_STATE::ATTACK);
	}			
}


void CHenesis3_Boss::ExitAttack()
{
	m_bAttacking = false;
	m_eState = BOSS_STATE::STAND;
}
