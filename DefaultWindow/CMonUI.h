#pragma once
#include "Obj.h"

class CMonster;

class CMonUI : public CObj
{
public:
    CMonUI();
    ~CMonUI();

public:
    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    void SetOwner(CObj* _pMon) { m_pOwner = _pMon; }

private:
    float m_fCount;
    CObj* m_pOwner;

    Vec2    m_vOffset;

};

