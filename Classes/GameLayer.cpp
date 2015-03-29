#include "GameLayer.h"
#include "MapLayer.h"
#include "Character.h"
#include "HudLayer.h"

CGameLayer::CGameLayer()
{
	m_pMapLayer = NULL;
	m_pCharacter = NULL;
}

CGameLayer::~CGameLayer()
{

}


bool CGameLayer::init()
{
	if (CCLayer::init())
	{
		//添加地图
		initMap("pd_tilemap.tmx");

		//添加主角
		initCharacter();

		//添加触控
		initHud();

		setTouchEnabled(true);

		scheduleUpdate();	//更新坐标

		return true;
	}

	return false;
}

bool CGameLayer::initMap( const char *szMapName )
{
	m_pMapLayer = CMapLayer::createWithTmxName(szMapName);
	if (m_pMapLayer)
	{
		m_pMapLayer->setPosition(CCPointZero);
		this->addChild(m_pMapLayer);
	}

	return true;
}

bool CGameLayer::initCharacter()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	m_pCharacter = CCharacter::create();
	if (m_pCharacter)
	{
		m_pCharacter->setPosition(ccp(m_pCharacter->m_nHalfWidth,m_pMapLayer->GetHeight()/2));

		m_pCharacter->m_designPt = m_pCharacter->getPosition();

		this->addChild(m_pCharacter,1);
	}

	return true;
}

void CGameLayer::FixPosition( IActionSprite * pSprite )
{
	if (pSprite == NULL)
		return;

	float minX = pSprite->m_nHalfWidth;
	float maxX = m_pMapLayer->GetWidth() - minX;

	if (pSprite->m_designPt.x <= minX)
		pSprite->m_designPt.x = minX;
	if (pSprite->m_designPt.x >= maxX)
		pSprite->m_designPt.x = maxX;

	float minY = pSprite->m_nHalfHeight;
	float maxY = m_pMapLayer->GetHeight() + minY;

	if (pSprite->m_designPt.y <= minY)
		pSprite->m_designPt.y = minY;
	if (pSprite->m_designPt.y >= maxY)
		pSprite->m_designPt.y = maxY;

	pSprite->setPosition(pSprite->m_designPt);
}

void CGameLayer::update( float delta )
{
	//更新坐标
	if (m_pCharacter)
	{
		//刷新前进目标
		m_pCharacter->UpdatePosition(delta);
		FixPosition(m_pCharacter);
	}
}

//执行行走
void CGameLayer::didChangeDirectorTo( SimpleDPad* simpleDPad,cocos2d::CCPoint direction )
{
	if (m_pCharacter)
	{
		m_pCharacter->Walk(direction);		//行走
	}
}

void CGameLayer::isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)
{
	if (m_pCharacter)
		m_pCharacter->Walk(direction);
}

void CGameLayer::simpleDPadTouchEnded( SimpleDPad* simpleDpad )
{
	//玩家停止 移动
	if (m_pCharacter && m_pCharacter->m_nCurState == kActionStateWalk)
		m_pCharacter->Idle();
}

bool CGameLayer::initHud()
{
	m_pHudLayer = CHudLayer::CreateWithDelegate(this);
	if (m_pHudLayer)
	{
		this->addChild(m_pHudLayer,2);

		return true;
	}

	return false;
}


