#pragma once
#include "CScene.h"
class CScene_henesis1 :
    public CScene
{
public:
	CScene_henesis1();
	~CScene_henesis1();

public:
	virtual	void		Initialize();
	virtual void		Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);

	virtual void		Enter();
	virtual void		Exit();

private:


};

