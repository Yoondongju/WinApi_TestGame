#include "stdafx.h"
#include "CollisionMgr.h"


#include "Monster.h"
#include "Bullet.h"
#include "Player.h"

#include "CHenesis3_Boss.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rcRect{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{

				if (Dst->GetObjType() == OBJID::OBJ_MONSTER 
					|| Dst->GetObjType() == OBJID::OBJ_BOSS)
				{				
					if (Src->GetObjType() == OBJID::OBJ_BULLET)
					{		
						CMonster* pMon = static_cast<CMonster*>(Dst);
						float fMonHp = pMon->GetHp();


						CBullet* pBullet = static_cast<CBullet*>(Src);
						float fAttack = pBullet->GetAttackInfo();
						
						if (0.f < fMonHp - fAttack)
							pMon->SetHp(fMonHp - fAttack);
						else
						{
							pMon->SetHp(0.f);
							pMon->Set_Dead();
						}
						Src->Set_Dead();

					}

					if (Src->GetObjType() == OBJID::OBJ_PLAYER)
					{
						CHenesis3_Boss* pBoss = dynamic_cast<CHenesis3_Boss*>(Dst);
						float pBossAttack(0.f);

						if (pBoss->GetBossState() == BOSS_STATE::ATTACK)
							pBossAttack = pBoss->GetAttackInfo();
						else if (pBoss->GetBossState() == BOSS_STATE::ATTACK2)
							pBossAttack = pBoss->GetAttack2Info();


						CPlayer* pPlayer = static_cast<CPlayer*>(Src);

						float fPlayerHp = pPlayer->GetHp();

						
						if ( 0.f < fPlayerHp - pBossAttack )
						{
							if (0 == pPlayer->GetHitdelay())
							{
 								pPlayer->SetHp(fPlayerHp - pBossAttack);
								pPlayer->SetHitdelay(GetTickCount());			
							}
							else if (pPlayer->GetHitdelay() + 300 < GetTickCount())
							{			
								pPlayer->SetHp(fPlayerHp - pBossAttack);
								pPlayer->SetHitdelay(GetTickCount());
							}
								
						}
							
						else
						{
							Src->Set_Dead();
						}
						
					}


				}


				// if (fX > fY) // 상하 충돌
				// {
				// 	// 상 충돌
				// 	if (Dst->Get_Info().fY < Src->Get_Info().fY)
				// 	{
				// 		Dst->Set_PosY(-fY);
				// 	}
				// 	// 하 충돌
				// 	else 
				// 	{
				// 		Dst->Set_PosY(fY);
				// 	}
				// }
				// 
				// else 		// 좌우 충돌
				// {
				// 	// 좌 충돌
				// 	if (Dst->Get_Info().fX < Src->Get_Info().fX)
				// 	{
				// 		Dst->Set_PosX(-fX);
				// 	}
				// 	// 우 충돌
				// 	else
				// 	{
				// 		Dst->Set_PosX(fX);
				// 	}
				// }

			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj * pDst, CObj * pSrc, float * pX, float * pY)
{

	float	fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float	fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float	fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float	fHeight	= abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight  * fHeight);

	float	fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
		
	return fRadius >= fDiagonal;
}
