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

	//ˢ��
	scheduleUpdate();

	return true;
}

void SimpleDPad::onEnterTransitionDidFinish()
{
	//ע�ᴥ���¼�
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void SimpleDPad::onExit()
{
	//ȡ������ʱ��
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SimpleDPad::update( float dt )
{
	if (m_bHold)
	{
		//���¶���
		if (m_pDelegate)
			m_pDelegate->isHoldingDirector(this,m_ptDirection);
	}
}

bool SimpleDPad::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	//�����Ƿ���������
	float fDistance = ccpDistanceSQ(pTouch->getLocation(),getPosition());

	//��Բ����
	if (fDistance <= m_fradius * m_fradius)
	{
		//���³���
		updateDirectionForTouchLocation(pTouch->getLocation());
		m_bHold = true;

		return true;
	}

	return false;
}

//�ƶ�
void SimpleDPad::ccTouchMoved( CCTouch *pTouch,CCEvent *pEvent )
{
	updateDirectionForTouchLocation(pTouch->getLocation());
}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
	m_ptDirection = CCPointZero;	//����
	m_bHold = false;

	//�ƶ�����,ֹͣ
	if (m_pDelegate)
		m_pDelegate->simpleDPadTouchEnded(this);
}

//���ӵ����Ƕ�
void SimpleDPad::updateDirectionForTouchLocation( CCPoint location )
{
	float radius = ccpToAngle(ccpSub(location,getPosition()));		//���㻡��
	float degress = CC_RADIANS_TO_DEGREES(radius);					//����Ƕ�

	//8����
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

	//�������
	if (m_pDelegate)
		m_pDelegate->didChangeDirectorTo(this,m_ptDirection);
}
