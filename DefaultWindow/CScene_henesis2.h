#pragma once
#include "CScene.h"
class CScene_henesis2 :
    public CScene
{
public:
	CScene_henesis2();
	~CScene_henesis2();

public:
	virtual	void		Initialize();
	virtual void		Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);

	virtual void		Enter();
	virtual void		Exit();


};

