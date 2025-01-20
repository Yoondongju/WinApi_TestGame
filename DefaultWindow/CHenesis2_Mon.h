#pragma once
#include "Monster.h"
class CHenesis2_Mon :
    public CMonster
{
public:
	CHenesis2_Mon();
	virtual ~CHenesis2_Mon();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:

};

