#pragma once

#include "CScene.h"

class CScene_henesis3 : public CScene
{
public:
	CScene_henesis3();
	virtual ~CScene_henesis3();

public:
	virtual	void		Initialize();
	virtual void		Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);


	virtual void		Enter();
	virtual void		Exit();

private:


};

