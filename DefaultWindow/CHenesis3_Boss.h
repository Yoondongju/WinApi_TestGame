#pragma once
#include "Monster.h"

enum BOSS_STATE
{
	STAND,
	WALK,
	ATTACK,
	ATTACK2,

	BOSS_STATEEND
};

class CHenesis3_Boss : public CMonster
{
public:
	CHenesis3_Boss();
	~CHenesis3_Boss();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	
private:
	void FindTargetPlayer();
	void StartAttack();
	void ExitAttack();



public:
	float GetAttackInfo() { return m_fAttackInfo;}
	float GetAttack2Info() { return m_fAttack2Info; }

 	BOSS_STATE GetBossState() { return m_eState; }


private:
	CObj*		m_pTarget;
	Vec2		m_FindRange;
	BOSS_STATE	m_eState;
	int			m_iDir;  // 1이면 오른쪽  -1 이면 왼쪽

	bool		m_bAttacking;

	float		m_fAttackInfo;
	float		m_fAttack2Info;
};

