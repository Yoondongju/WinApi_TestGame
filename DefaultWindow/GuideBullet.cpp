#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"


CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();
}

void CGuideBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CGuideBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

	if (m_pTarget)
	{
		float	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight); // 타겟을 찾고난뒤 그 타겟의 거리

		float	fRadian = acos(fWidth / fDiagonal); // 역함수는 내가 가고자하는 방향 (라디안)을 얻기위함  // 범위가 0 ~ 180임 그래서 그런거다

 		m_fAngle = fRadian * 180.f / PI; // 디그리 각도로 변환 

		if (m_tInfo.fY < m_pTarget->Get_Info().fY) 
			m_fAngle *= -1.f;

		
	}
	
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}


void CGuideBullet::Late_Update()
{
}

void CGuideBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CGuideBullet::Release()
{
}
