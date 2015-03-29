#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

//////////////////////////////////////////////////////////////////////////
//模型基础类
//////////////////////////////////////////////////////////////////////////

#include "GlobalDefine.h"

//状态
 enum ActionState
 {
	 kActionStateNone = 0,		//无状态
	 kActionStateIdle,			//闲置
	 kActionStateWalk,			//行走
	 kActionStateAttack,		//攻击 
	 kActionStateHurt,			//受到攻击
	 kActionStateDead,			//死亡
 };

 class IActionSprite : public CCSprite
 {
 public:
	 IActionSprite();
	 virtual ~IActionSprite();

	 //创建动作
	 virtual void CreateAction() = 0;

	 //闲置
	 virtual void Idle();

	 //行走方向
	 virtual void Walk(CCPoint direction);

	 //攻击
	 virtual void Attack();

	 //受击
	 virtual void Hurt();

	 //死亡
	 virtual void Dead();

	 virtual void UpdatePosition(float dt);

	 ActionState m_nCurState;			//当前状态
	 
	 //动作
	 CCAction*	m_pIdle;				//闲置
	 CCAction*	m_pWalk;				//攻击
	 CCAction*	m_pAttack;				//攻击
	 CCAction*	m_pHurt;				//受击
	 CCAction*	m_pDead;				//死亡

	 //移动速度
	 float		m_fWalkSpeed;				//移动速度
	 CCPoint	m_ptVerSpeed;				//向量速度和朝向结合
	 CCPoint	m_designPt;					//目标点,在下一帧显示

	 float	m_nHalfWidth;				//一半宽度
	 float	m_nHalfHeight;				//一般高度
 };

#endif