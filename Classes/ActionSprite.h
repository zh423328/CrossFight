#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

//////////////////////////////////////////////////////////////////////////
//ģ�ͻ�����
//////////////////////////////////////////////////////////////////////////

#include "GlobalDefine.h"

//״̬
 enum ActionState
 {
	 kActionStateNone = 0,		//��״̬
	 kActionStateIdle,			//����
	 kActionStateWalk,			//����
	 kActionStateAttack,		//���� 
	 kActionStateHurt,			//�ܵ�����
	 kActionStateDead,			//����
 };

 class IActionSprite : public CCSprite
 {
 public:
	 IActionSprite();
	 virtual ~IActionSprite();

	 //��������
	 virtual void CreateAction() = 0;

	 //����
	 virtual void Idle();

	 //���߷���
	 virtual void Walk(CCPoint direction);

	 //����
	 virtual void Attack();

	 //�ܻ�
	 virtual void Hurt();

	 //����
	 virtual void Dead();

	 virtual void UpdatePosition(float dt);

	 ActionState m_nCurState;			//��ǰ״̬
	 
	 //����
	 CCAction*	m_pIdle;				//����
	 CCAction*	m_pWalk;				//����
	 CCAction*	m_pAttack;				//����
	 CCAction*	m_pHurt;				//�ܻ�
	 CCAction*	m_pDead;				//����

	 //�ƶ��ٶ�
	 float		m_fWalkSpeed;				//�ƶ��ٶ�
	 CCPoint	m_ptVerSpeed;				//�����ٶȺͳ�����
	 CCPoint	m_designPt;					//Ŀ���,����һ֡��ʾ

	 float	m_nHalfWidth;				//һ����
	 float	m_nHalfHeight;				//һ��߶�
 };

#endif