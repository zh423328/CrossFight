#include "SimpleDPad.h"


SimpleDPad::SimpleDPad( void )
{
	m_pDelegate = NULL;
}

SimpleDPad::~SimpleDPad( void )
{

}

SimpleDPad* SimpleDPad::CreateWithFile( const char * szFileName,float radius,SimpleDPadDelegate *pDelegate )
{
	SimpleDPad *pSimpleDPad = new SimpleDPad();
	if (pSimpleDPad && pSimpleDPad->initWithFile(szFileName,radius))
	{
		pSimpleDPad->m_pDelegate = pDelegate;
	}
	else
	{
		CC_SAFE_DELETE(pSimpleDPad);
	}

	return pSimpleDPad;
}

bool SimpleDPad::initWithFile( const char * szFileName,float radius )
{
	if(!CCSprite::initWithFile(szFileName))
		return false;

	m_fradius = radius;
	m_ptDirection = CCPointZero;
	m_bHold = false;

	//刷新
	scheduleUpdate();

	return true;
}

void SimpleDPad::onEnterTransitionDidFinish()
{
	//注册触摸事件
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void SimpleDPad::onExit()
{
	//取消触摸时间
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SimpleDPad::update( float dt )
{
	if (m_bHold)
	{
		//更新动作
		if (m_pDelegate)
			m_pDelegate->isHoldingDirector(this,m_ptDirection);
	}
}

bool SimpleDPad::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	//计算是否在区域内
	float fDistance = ccpDistanceSQ(pTouch->getLocation(),getPosition());

	//在圆盘内
	if (fDistance <= m_fradius * m_fradius)
	{
		//更新朝向
		updateDirectionForTouchLocation(pTouch->getLocation());
		m_bHold = true;

		return true;
	}

	return false;
}

//移动
void SimpleDPad::ccTouchMoved( CCTouch *pTouch,CCEvent *pEvent )
{
	updateDirectionForTouchLocation(pTouch->getLocation());
}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
	m_ptDirection = CCPointZero;	//朝向
	m_bHold = false;

	//移动代理,停止
	if (m_pDelegate)
		m_pDelegate->simpleDPadTouchEnded(this);
}

//更加点计算角度
void SimpleDPad::updateDirectionForTouchLocation( CCPoint location )
{
	float radius = ccpToAngle(ccpSub(location,getPosition()));		//计算弧度
	float degress = CC_RADIANS_TO_DEGREES(radius);					//计算角度

	//8方向
	if (degress >= -22.5f && degress < 22.5f)
		m_ptDirection = ccp(1,0);
	else if (degress >= 22.5 && degress < 67.5f)
		m_ptDirection = ccp(1,1);
	else if (degress >= 67.5f && degress < 112.5f)
		m_ptDirection = ccp(0,1);
	else if (degress >= 112.5 && degress < 157.5f)
		m_ptDirection = ccp(-1,1);
	else  if ((degress >= 157.f && degress <= 180.0f) ||(degress <= -157.0f && degress >= -180.0f))
		m_ptDirection = ccp(-1,0);
	else if (degress >= -157.0f && degress < -112.5f)
		m_ptDirection = ccp(-1,-1);
	else if (degress >= -112.f && degress < -67.5 )
	{
		m_ptDirection = ccp(0,-1);
	}
	else if (degress >= -67.5f && degress < -22.5f)
		m_ptDirection = ccp(1,-1);

	//代理出发
	if (m_pDelegate)
		m_pDelegate->didChangeDirectorTo(this,m_ptDirection);
}
