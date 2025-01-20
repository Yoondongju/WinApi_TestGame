#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"

#include "CKeyMgr.h"
#include "CScrollMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CMonUI.h"


CPlayer::CPlayer()
	: m_fDistance(0.f), m_bJump(false), m_fTime(0.f), m_fPower(0.f), m_bRope(false)
	, m_bLineride(false)
	, m_PreState(PLAYER_STATE::STATE_END)
	, m_CurState(PLAYER_STATE::IDLE)	
	, m_dwTime(GetTickCount())
	, m_dwHitdelay(0)
	, fOffSetminX (0.f)
	, fOffSetmaxX (0.f)
	, fOffSetminY (0.f)
	, fOffSetmaxY (0.f)

{
	ZeroMemory(&m_tPosin, sizeof(POINT));
	
	m_fMaxHp = 300.f;
	m_fHp = m_fMaxHp;

	// �ؽ��� �Ҵ�

	m_eObjType = OBJID::OBJ_PLAYER;
	CreateAnimator();					// �׻� �ִϸ����� ��������� ObjType ���������!!!!!!!!!!1

	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Test/stand_left.bmp");   // �̹��� ���
	GetAnimator()->CreateAnimation(L"stand_left", m_vecTexture.back(), Vec2(0.f, 0.f), Vec2(62.f, 77.f), Vec2(0.f, 77.f), 1.f, 9);
	
	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Test/stand_right.bmp");
	GetAnimator()->CreateAnimation(L"stand_right", m_vecTexture.back(), Vec2(0.f, 0.f), Vec2(62.f, 77.f), Vec2(0.f, 77.f), 1.f, 9);
	
	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Test/walk_left.bmp");
	GetAnimator()->CreateAnimation(L"walk_left", m_vecTexture.back(), Vec2(0.f, 0.f), Vec2(62.5f, 72.f), Vec2(62.5f, 0.f), 1.f, 4);
	
	m_vecTexture.push_back(new CTexture);
	m_vecTexture.back()->Load(L"../Test/walk_right.bmp");
	GetAnimator()->CreateAnimation(L"walk_right", m_vecTexture.back(), Vec2(0.f, 0.f), Vec2(62.5f, 72.f), Vec2(62.5f, 0.f), 1.f, 4);

}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo		= { 300.f, WINCY - 150.f , 60.f,60.f};
	m_fSpeed	= 5.f;
	m_fDistance = 100.f;
	m_fPower = 15.f;

	m_fAngle = 0.f;
	m_eObjType = OBJID::OBJ_PLAYER;

	CMonUI* pUI = new CMonUI;
	pUI->SetOwner(this);
	pUI->Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{				

	if (!m_bRope)
		Jump();

	CLineMgr::Get_Instance()->Collision_Wall(this);

	Offset();
	GetAnimator()->Update();
}

void CPlayer::Render(HDC hDC)
{	
	GetAnimator()->GetCurAnimation()->Render(hDC);

	//BitBlt(hDC,						// �������� �׸��� �׸� dc
	//	m_tRect.left + iScrollX,	// ���� ���� ��ġ�� left
	//	m_tRect.top,				// ���� ���� ��ġ�� top
	//	m_tInfo.fCX,				// ���� ���� ���� ����
	//	m_tInfo.fCY,				// ���� ���� ���� ����
	//	m_Texture->GetDC(),			// ��Ʈ���� ������ �ִ� dc
	//	0,							// ����� ��Ʈ���� ���� x��ǥ
	//	0,							// ����� ��Ʈ���� ���� y��ǥ		
	//	SRCCOPY);


	// GdiTransparentBlt �Լ�: Ư�������� �����ϰ����
}

void CPlayer::Release()
{
	for (auto& iter : m_vecTexture)
	{
		Safe_Delete<CTexture*>(iter);
	}
	m_vecTexture.clear();
}

void CPlayer::Wall_Check()
{
	float f_deltaX(0.f);
	float f_deltaY(0.f);

	float m_f_Recently_FX = m_tInfo.fX;
	float m_f_Recently_FY = m_tInfo.fY;
	//float m_f_Recently_FX_left = m_tInfo.fX - m_tInfo.fCX * 0.5f;
	//float m_f_Recently_FX_right = m_tInfo.fX + m_tInfo.fCX * 0.5f;


	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line_WALL(m_f_Recently_FX, m_f_Recently_FY, &f_deltaX, &f_deltaY);  //���⼭ fx,fY update



	if (bLineCol) //�浹������ �÷��̾��� X����ǥ  
	{
		m_tInfo.fX = f_deltaX;
		if (m_f_Recently_FX <= f_deltaX)  //
		{
			m_tInfo.fX = f_deltaX - m_tInfo.fCX * 0.5f;
			//m_tInfo.fX = f_deltaX - m_tInfo.fCX * 2.f;
		}
		else
		{
			m_tInfo.fX = f_deltaX + m_tInfo.fCX * 0.5f;
		}
	}
}

void CPlayer::Key_Input()
{
	float	fY(0.f);
	GetAnimator()->Play(L"stand_right");

	CScene* pCurScene = CSceneMgr::CreateSingleTonInst()->GetCurScene();


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::TAP)
	{
		
		POINT	pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		
		Calculate_Angle(pt);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		if (m_tInfo.fX >= 200)
		{
			if (!m_bRope && m_bLineride)
			{
				m_tInfo.fX -= m_fSpeed;
				Wall_Check();
			}

		}

		GetAnimator()->Play(L"walk_left");
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		if (m_tInfo.fX < pCurScene->Width() - 200)
		{
			if (!m_bRope && m_bLineride)
			{
				m_tInfo.fX += m_fSpeed;
				Wall_Check();
			}
				
		}

		GetAnimator()->Play(L"walk_right");
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::SPACE) == KEY_STATE::HOLD)
	{
		if (!m_bJump) // �������� ����
		{
			m_fPower += 0.2f;
		}
	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		m_bJump = true;

		if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD
			|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
		{
			m_bRope = false;
		}
	}


	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		if (m_tInfo.fY > 200)
		{
			m_tInfo.fY -= m_fSpeed;
		}
		
		float fY = 0.f;
		
		if (CLineMgr::Get_Instance()->Collisiong_UpRopeLine(this, &fY))
		{
			m_bRope = true;
		
			m_tInfo.fY -= m_fSpeed;
			if (m_tInfo.fY <= fY)
			{
				m_tInfo.fY = fY - 5;
				m_bRope = false;
			}
				
		}
		else
			m_bRope = false;

	}

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		if (m_tInfo.fY < pCurScene->Height() - 200)
		{
			m_tInfo.fY += m_fSpeed;
		}
		
		float fY = 0.f;
		
		if (CLineMgr::Get_Instance()->Collisiong_DownRopeLine(this, &fY))
		{
			m_bRope = true;
		
			m_tInfo.fY += m_fSpeed;
			if (m_tInfo.fY >= fY)
			{
				m_tInfo.fY = fY;
		
			}
				
		}
		else
			m_bRope = false;
	}



	// if (GetAsyncKeyState(VK_F1))
	// {
	// 	CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, Create_Shield());
	// }

}

CObj * CPlayer::Create_Bullet(DIRECTION eDir)
{

	CObj*		pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Dir(eDir);

	return pBullet;
}

CObj * CPlayer::Create_Shield()
{
	CObj*		pShield = CAbstractFactory<CShield>::Create();
	pShield->Set_Target(this);

	return pShield;
}

void CPlayer::Jump()
{
	float pY = 0.f;
	float pX = 0.f;


	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &pY, &pX);



	m_bLineride = bLineCol;  // Ÿ�ٶ����� ������ �Ʒ��� ������

	if (!m_bLineride)
	{
		m_tInfo.fY -= m_fPower * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
 		m_fTime += 0.2f;
	}
	
	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
		m_fTime += 0.2f;

		if (bLineCol && m_tInfo.fY > pY) // �����ϴ� ����
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = pY - m_tInfo.fCX / 2;
			m_fPower = 15.f;
		}
		else if (!bLineCol) 
			m_tInfo.fY = pY - m_tInfo.fCX / 2;
	}
	else if (!m_bJump && bLineCol)
	{
		m_tInfo.fY = pY - m_tInfo.fCX / 2; 	
	}
	
	

}

void CPlayer::Offset()
{
	// ��ũ���� 

	//int		iOffSetX = WINCX >> 1;
	//int		iOffSetY = WINCY >> 1;
	//
	//float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	//float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	//
	//if ((float)iOffSetX > m_tInfo.fX + fScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
	//
	//if ((float)iOffSetX < m_tInfo.fX + fScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	//
	//if ((float)iOffSetY > m_tInfo.fY + fScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
	//
	//if ((float)iOffSetY < m_tInfo.fY + fScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);


	fOffSetminX = 200.f;
	fOffSetmaxX = 600;
	
	fOffSetminY = 200.f;
	fOffSetmaxY = 400.f;

	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	

	if (fOffSetminX > m_tInfo.fX + fScrollX) // ���ؼ����� �������� ����
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
	
	if (fOffSetmaxX < m_tInfo.fX + fScrollX) // ���ؼ����� ���������� ����
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	
	if (fOffSetminY > m_tInfo.fY + fScrollY) // ���ؼ����� �Ʒ��� ����
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
	
	if (fOffSetmaxY < m_tInfo.fY + fScrollY) // ���ؼ����� ���� ����
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);



	//�÷��̾��� ��ġ�� fOffSetmax��ġ�� ���̰� ���������
	//X��ũ���� ���ش�
	//
	//
	//�÷��̾��� ��ġ�� fOffSetminx��ġ�� ���̰� ���������
	//X��ũ���� �����ش�

}

void CPlayer::Calculate_Angle(POINT _pt)
{
	if (_pt.x != 0 && _pt.y != 0)
	{
		float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		float RenderX = m_tInfo.fX + fScrollX;
		float RenderY = m_tInfo.fY + fScrollY;


		float	fWidth = _pt.x - RenderX;
		float	fHeight = _pt.y - RenderY;

		float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acos(fWidth / fDiagonal);

		m_fAngle = fRadian * 180.f / PI;

		if (RenderY < _pt.y)
			m_fAngle *= -1.f;
	}
}
