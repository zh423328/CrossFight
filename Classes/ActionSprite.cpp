#include "ActionSprite.h"

IActionSprite::IActionSprite()
{
	m_nCurState = kActionStateNone;
	m_nHalfHeight = 0.0f;
	m_nHalfWidth = 0.0f;
	
	m_pIdle = NULL;
	m_pAttack = NULL;
	m_pHurt = NULL;
	m_pWalk = NULL;
	m_pDead = NULL;

	m_fWalkSpeed = 0.0f;
	m_ptVerSpeed = CCPointZero;
}

IActionSprite::~IActionSprite()
{
	
}

//闲置
void IActionSprite::Idle()
{
	if (m_nCurState != kActionStateIdle && m_nCurState != kActionStateDead)
	{
		//停止之前所有的动作
		stopAllActions();

		if (m_pIdle)
			runAction(m_pIdle);

		m_nCurState  = kActionStateIdle;

		//不让移动
		m_ptVerSpeed = CCPointZero;
	}
}


//移动
void IActionSprite::Walk( CCPoint direction )
{
	//闲置的时候才能移动
	if (m_nCurState == kActionStateIdle)
	{
		stopAllActions();

		if (m_pWalk)
			runAction(m_pWalk);

		m_nCurState = kActionStateWalk;		//移动

		m_ptVerSpeed = ccp(direction.x * m_fWalkSpeed,direction.y*m_fWalkSpeed);		//移动矢量

		if (m_ptVerSpeed.x >= 0)
			setFlipX(false);
		else
			setFlipX(true);			//翻转
	}
}

void IActionSprite::Attack()
{
	//闲置
	if(m_nCurState == kActionStateWalk || m_nCurState == kActionStateIdle)
	{
		stopAllActions();
		if (m_pAttack)
			runAction(m_pAttack);

		m_nCurState = kActionStateAttack; //攻击
	}
}

void IActionSprite::Hurt()
{
	if (m_nCurState != kActionStateDead && m_nCurState != kActionStateHurt)
	{
		stopAllActions();

		if (m_pHurt)
			runAction(m_pHurt);

		m_nCurState = kActionStateHurt;
	}
}

void IActionSprite::Dead()
{
	if (m_nCurState != kActionStateDead)
	{
		stopAllActions();
		
		if (m_pDead)
			runAction(m_pDead);

		m_nCurState = kActionStateDead;
	}
}

//不断的更新坐标
void IActionSprite::UpdatePosition( float dt )
{
	if (m_nCurState == kActionStateWalk)
		m_designPt = ccpAdd(this->getPosition(),ccpMult(m_ptVerSpeed,dt));
}



