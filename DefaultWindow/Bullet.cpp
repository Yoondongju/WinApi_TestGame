#include "stdafx.h"
#include "Bullet.h"

#include "CScrollMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"

#include "CScene.h"
#include "CSceneMgr.h"

CBullet::CBullet()
	: m_pTex(nullptr)
{

}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 10.f;
	m_fAttackInfo = 10.f;

	m_eObjType = OBJID::OBJ_BULLET;
	CreateAnimator();

	m_pTex = new CTexture;
	m_pTex->Load(L"../BmpImage/Meso_1.bmp");
	GetAnimator()->CreateAnimation(L"Meso", m_pTex, Vec2(0.f, 27.f), Vec2(26.5f, 27.f), Vec2(26.5f, 0.f), 1, 4);
	GetAnimator()->Play(L"Meso");

}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}


void CBullet::Late_Update()
{
	CScene* pCurScene = CSceneMgr::CreateSingleTonInst()->GetCurScene();

	if (0 >= m_tRect.left || pCurScene->Width() <= m_tRect.right ||
		0 >= m_tRect.top || pCurScene->Height() <= m_tRect.bottom)
		m_bDead = true;

	GetAnimator()->Update();
}

void CBullet::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GetAnimator()->GetCurAnimation()->Render(hDC);

}

void CBullet::Release()
{
}
