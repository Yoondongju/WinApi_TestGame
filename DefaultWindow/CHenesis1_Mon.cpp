#include "stdafx.h"
#include "CHenesis1_Mon.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CHenesis1_Mon::CHenesis1_Mon()
	:m_iType(0), m_dwTime(0), m_bPlayerCol(false), m_iDirection(1)
{
	ZeroMemory(&m_tRectBoundary, sizeof(RECT));
}
CHenesis1_Mon::CHenesis1_Mon(int _iType)
	: m_iType(_iType), m_dwTime(0), m_bPlayerCol(false), m_iDirection(1)
{

	ZeroMemory(&m_tRectBoundary, sizeof(RECT));
}
CHenesis1_Mon::~CHenesis1_Mon()
{
}

void CHenesis1_Mon::Initialize()
{
	

	switch (m_iType)
	{
	case 3:
		m_tInfo.fCX = 300.f;
		m_tInfo.fCY = 300.f;
		m_fMaxHp = 200.f;
		break;
	default:
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_fMaxHp = 100.f;
		break;
	}

	CMonster::Initialize();   // HP UI세팅

	m_fSpeed = 1.f;
	m_fHp = m_fMaxHp;
	m_eObjType = OBJID::OBJ_MONSTER;


	//동적 할당후 텍스쳐 로드
	m_pTex.push_back(new CTexture);
	m_pTex.back()->Load(L"../BmpImage/Henesis1_Monster.bmp");

	//필수
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Monster_walk_left", m_pTex[0], Vec2(0.f, 0.f), Vec2(112.3f, 102.f), Vec2(112.3f, 0.f), 1.f, 8);
	//키값				,0번째로 사용하겠다?, (x,y 구조체)시작할 좌상단 위치, 슬라이드 할 사이즈, 애니메이션 진행시 얼마나 넘어갈지, 그냥 1, 프레임 카운트

	GetAnimator()->CreateAnimation(L"Monster_dead", m_pTex[0], Vec2(0.f, 102.f), Vec2(150.f, 176.f), Vec2(150.f, 0.f), 1.f, 5);
	GetAnimator()->Play(L"Monster_walk_left");
}

int CHenesis1_Mon::Update()
{
	if (m_bDead)
	{
		GetAnimator()->Play(L"Monster_dead");

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

void CHenesis1_Mon::Late_Update()
{
	float pY = 0.f;

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_LineMonster(this, m_tInfo.fX, m_tInfo.fY, &pY, &m_fTargetX);

	if (bLineCol)
	{
		m_tInfo.fY = pY - m_tInfo.fCX / 2;
		m_fTime = 0.f;
	}
	else
	{
		m_tInfo.fY -= 10.f * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
		m_fTime += 0.2f;
	}

	//플레이어 충돌 검사를 위한 RECT 조정
	Set_Boudary();

	RECT	rcRect{};

	m_bPlayerCol = IntersectRect(&rcRect, &m_tRectBoundary, &(m_pTarget->Get_Rect()));

	switch (m_iType)
	{
	case 1:
		Follow_Player();
		break;
	case 2:
		Move_LeftRight(bLineCol, 100);
		break;
	case 3:
		if (m_bPlayerCol)
		{
			SizeDown();
			m_fSpeed = 15.f;
			Move_LeftRight(bLineCol, 200);
		}
		else
		{
			SizeUp();
		}
		break;
	default:
		break;
	}


	GetAnimator()->Update();
}

void CHenesis1_Mon::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CHenesis1_Mon::Release()
{
}

void CHenesis1_Mon::Set_Boudary()
{
	if (m_iType == 3)
	{
		m_tRectBoundary.left = long(m_tRect.left - 300.f);
		m_tRectBoundary.right = long(m_tRect.right + 300.f);
		m_tRectBoundary.top = m_tRect.top;
		m_tRectBoundary.bottom = m_tRect.bottom;
	}
	else
	{
		m_tRectBoundary.left = long(m_tRect.left - 200.f);
		m_tRectBoundary.right = long(m_tRect.right + 200.f);
		m_tRectBoundary.top = m_tRect.top;
		m_tRectBoundary.bottom = m_tRect.bottom;
	}
}

void CHenesis1_Mon::Follow_Player()
{
	if (m_bPlayerCol)
	{
		if (m_tInfo.fX < m_pTarget->Get_Info().fX)
			m_tInfo.fX += 1.f;
		else
			m_tInfo.fX -= 1.f;
	}
}

void CHenesis1_Mon::Move_LeftRight(bool _bLineCol, float _fArrange)
{
	if (m_fOriginX < 0 || m_fOriginX > 2880)
	{
		m_fOriginX = m_tInfo.fX;
	}
	if (_bLineCol)
	{
		//좌우 이동 코드
		if (m_tInfo.fX >= m_fOriginX - _fArrange && m_tInfo.fX <= m_fOriginX + _fArrange)
			m_tInfo.fX += m_fSpeed * m_iDirection;
		else
		{
			m_iDirection *= -1;
			m_tInfo.fX += m_fSpeed * m_iDirection;
		}
	}
	else
	{
		m_tInfo.fY -= 10.f * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
		m_fTime += 0.2f;
	}
}

void CHenesis1_Mon::SizeDown()
{
	if (m_tInfo.fCX > 50.f)
	{
		m_tInfo.fCX -= 3.f;
		m_tInfo.fCY -= 3.f;
	}
}

void CHenesis1_Mon::SizeUp()
{
	if (m_tInfo.fCX < 300.f)
	{
		m_tInfo.fCX += 3.f;
		m_tInfo.fCY += 3.f;
	}
}
