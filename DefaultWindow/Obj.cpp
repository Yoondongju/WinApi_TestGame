#include "stdafx.h"
#include "Obj.h"

#include "CAnimator.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END),
m_bDead(false), m_fAngle(0.f), m_pAnimator(nullptr)

{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::~CObj()
{
	if (nullptr != m_pAnimator)
		Safe_Delete<CAnimator*>(m_pAnimator);

}



void CObj::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;

}


void CObj::Update_Rect()
{
	m_tRect.left	= long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
