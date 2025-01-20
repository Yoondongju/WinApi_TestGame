#include "stdafx.h"
#include "CScene.h"

#include "ObjMgr.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "CHenesis3_Boss.h"

#include "LineMgr.h"


CScene::CScene()
{

}

CScene::~CScene()
{
}

void CScene::Update()
{
	
}

void CScene::Late_Update()
{

}

void CScene::Render(HDC hDC)
{

}

void CScene::Exit()
{
	list<CObj*>& MonList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MONSTER);
	list<CObj*>& BulletList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BULLET);


	for (auto& iter : MonList)
	{
		Safe_Delete<CObj*>(iter);
	}
	MonList.clear();


	for (auto& iter : BulletList)
	{
		Safe_Delete<CObj*>(iter);
	}
	BulletList.clear();


	list<CLine*>& lineList = CLineMgr::Get_Instance()->GetLineList();
	
	for (auto& iter : lineList)
	{
		Safe_Delete<CLine*>(iter);
	}
	lineList.clear();

}
