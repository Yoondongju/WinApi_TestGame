#pragma once
#include "Monster.h"
class CHenesis2_Boss :
    public CMonster
{
public:
	CHenesis2_Boss();
	virtual ~CHenesis2_Boss();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:

};

