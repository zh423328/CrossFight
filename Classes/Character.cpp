#include "Character.h"

CCharacter::CCharacter()
{

}

CCharacter::~CCharacter()
{
	CC_SAFE_RELEASE(m_pIdle);
	CC_SAFE_RELEASE(m_pWalk);
	CC_SAFE_RELEASE(m_pAttack);
	CC_SAFE_RELEASE(m_pHurt);
	CC_SAFE_RELEASE(m_pDead);
}

bool CCharacter::init()
{
	if (!IActionSprite::initWithSpriteFrameName("hero_idle_00.png"))
		return false;
	else
	{
		m_nHalfHeight = getContentSize().height/2;
		m_nHalfWidth = getContentSize().width/2;

		//速度
		m_fWalkSpeed = 100.0f;

		CreateAction();

		Idle();	//闲置动作
	}

	return true;
}

//添加动作
void CCharacter::CreateAction()
{
	//闲置动作
	CCArray * pIdleAry  = CCArray::create();

	int i = 0;
	for(i = 0; ; ++i)
	{
		CCSpriteFrame*pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_idle_%02d.png",i)->getCString());
		if (pSpriteFrame)
		{
			pIdleAry->addObject(pSpriteFrame);
		}
		else
			break;
	}

	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pIdleAry,0.3f);
	m_pIdle = CCRepeatForever::create(CCAnimate::create(pAnimation));
	CC_SAFE_RETAIN(m_pIdle);

	//行走
	CCArray * pWalkAry  = CCArray::create();

	i = 0;
	for(i = 0; ; ++i)
	{
		CCSpriteFrame*pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_walk_%02d.png",i)->getCString());
		if (pSpriteFrame)
		{
			pWalkAry->addObject(pSpriteFrame);
		}
		else
			break;
	}

	CCAnimation *pWalk = CCAnimation::createWithSpriteFrames(pWalkAry,0.3f);
	m_pWalk = CCRepeatForever::create(CCAnimate::create(pWalk));
	CC_SAFE_RETAIN(m_pWalk);

	//攻击
	CCArray * pAtkAry  = CCArray::create();

	i = 0;
	for(i = 0; ; ++i)
	{
		CCSpriteFrame*pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_attack_00_%02d.png",i)->getCString());
		if (pSpriteFrame)
		{
			pAtkAry->addObject(pSpriteFrame);
		}
		else
			break;
	}

	CCAnimation *pAtk = CCAnimation::createWithSpriteFrames(pAtkAry,0.3f);
	m_pAttack = CCSequence::create(CCAnimate::create(pAtk),CCCallFunc::create(this,callfunc_selector(IActionSprite::Idle)),NULL);
	CC_SAFE_RETAIN(m_pAttack);

	//受击
	CCArray * pHurtAry  = CCArray::create();

	i = 0;
	for(i = 0; ; ++i)
	{
		CCSpriteFrame*pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_hurt_%02d.png",i)->getCString());
		if (pSpriteFrame)
		{
			pHurtAry->addObject(pSpriteFrame);
		}
		else
			break;
	}

	CCAnimation *pHurt = CCAnimation::createWithSpriteFrames(pHurtAry,0.3f);
	m_pHurt = CCSequence::create(CCAnimate::create(pHurt),CCCallFunc::create(this,callfunc_selector(IActionSprite::Idle)),NULL);
	CC_SAFE_RETAIN(m_pHurt);
	
	//死亡
	CCArray * pDeadAry  = CCArray::create();

	i = 0;
	for(i = 0; ; ++i)
	{
		CCSpriteFrame*pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_dead_%02d.png",i)->getCString());
		if (pSpriteFrame)
		{
			pDeadAry->addObject(pSpriteFrame);
		}
		else
			break;
	}

	CCAnimation *pDead = CCAnimation::createWithSpriteFrames(pDeadAry,0.3f);
	m_pDead = CCAnimate::create(pDead);
	CC_SAFE_RETAIN(m_pDead);
}

