#include "stdafx.h"
#include "CSceneMgr.h"

#include "CScene.h"

#include "CScene_henesis0.h"
#include "CScene_henesis1.h"
#include "CScene_henesis2.h"
#include "CScene_henesis3.h"


CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_pPreScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	for (auto& iter : m_vecGameScene)
	{
		Safe_Delete<CScene*>(iter);
	}
	
}

void CSceneMgr::init()
{
	m_vecGameScene.push_back(new CScene_henesis0);
	m_vecGameScene.push_back(new CScene_henesis1);
	m_vecGameScene.push_back(new CScene_henesis2);
	m_vecGameScene.push_back(new CScene_henesis3);


	m_pCurScene = m_vecGameScene[SCENETYPE::HENESIS2];  // ¾À ÀüÈ¯¼ø¼­   2->1->0->3
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pCurScene->Late_Update();
	
	
}

void CSceneMgr::Render(HDC hDC)
{
	m_pCurScene->Render(hDC);
}


void CSceneMgr::SceneChange(SCENETYPE _e)
{
	m_pCurScene->Exit();

	m_pPreScene = m_pCurScene;

	m_pCurScene = m_vecGameScene[_e];
	m_pCurScene->Enter();
}
