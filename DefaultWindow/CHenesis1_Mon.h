#pragma once
#include "Monster.h"
class CHenesis1_Mon :
    public CMonster
{
public:
    CHenesis1_Mon();
    CHenesis1_Mon(int   _iType);
    virtual ~CHenesis1_Mon();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void Set_Boudary();
    void Follow_Player();
    void Move_LeftRight(bool _bLineCol, float _fArrange);
    void SizeDown();
    void SizeUp();

private:
    int m_iType;
    bool m_bPlayerCol;
    float m_fOriginX;
    int m_iDirection;

    RECT m_tRectBoundary;

    DWORD		m_dwTime;
};

