#pragma once

#include "Define.h"

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

public:
	void		init();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);

	
public:
	void		SceneChange(SCENETYPE _e);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	vector<CScene*> m_vecGameScene;

	CScene*			m_pCurScene;
	CScene*			m_pPreScene;

};

