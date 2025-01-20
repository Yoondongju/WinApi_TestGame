#pragma once
#include "Obj.h"
class CBox : public CObj
{
public:
	CBox();
	~CBox();

public:

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

