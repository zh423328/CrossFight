#include "MapLayer.h"
#include "Character.h"

CMapLayer::CMapLayer()
{
	m_pMap  = NULL;
}


CMapLayer::~CMapLayer()
{

}

//利用tmx文件创建地图
CMapLayer * CMapLayer::createWithTmxName( const char * szFileName )
{
	CMapLayer *pMapLayer = new CMapLayer();
	if (pMapLayer && pMapLayer->initWithFileName(szFileName))
	{
		pMapLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pMapLayer);
		pMapLayer = NULL;
	}

	return pMapLayer;
}

bool CMapLayer::initWithFileName( const char* szFileName )
{
	if (CCLayer::init())
	{
		m_pMap = CCTMXTiledMap::create(szFileName);
		if (m_pMap)
		{
			//设置抗锯齿
			CCObject *pObj = NULL;
			CCARRAY_FOREACH(m_pMap->getChildren(),pObj)
			{
				CCTMXLayer * pTmxLayer = dynamic_cast<CCTMXLayer*>(pObj);
				if (pTmxLayer)
				{
					pTmxLayer->getTexture()->setAliasTexParameters();		//抗锯齿
				}
			}	
			m_pMap->setPosition(CCPointZero);
			this->addChild(m_pMap);
		}

		//添加主角
		initCharacter();

		scheduleUpdate();

		return true;
	}
	return false;
}

float CMapLayer::GetWalkWidth()
{
	if (m_pMap)
	{
		return m_pMap->getTileSize().width*m_pMap->getMapSize().width;
	}
	else
		return 0.0f;
}

float CMapLayer::GetWalkHeight()
{
	if (m_pMap)
	{
		return 3*m_pMap->getTileSize().height;
	}

	return 0.0f;
}

float CMapLayer::GetTotalWidth()
{
	if (m_pMap)
	{
		return m_pMap->getTileSize().width*m_pMap->getMapSize().width;
	}
	else
		return 0.0f;
}

float CMapLayer::GetTotalHeight()
{
	if (m_pMap)
	{
		return m_pMap->getTileSize().height*m_pMap->getMapSize().height;
	}
	else
		return 0.0f;
}




bool CMapLayer::initCharacter()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	m_pCharacter = CMapPlayer::create();
	if (m_pCharacter)
	{
		m_pCharacter->setPosition(ccp(m_pCharacter->m_nHalfWidth,GetWalkHeight()/2));

		m_pCharacter->m_designPt = m_pCharacter->getPosition();

		this->addChild(m_pCharacter,1);
	}

	return true;
}

void CMapLayer::FixPosition( IActionSprite * pSprite )
{
	if (pSprite == NULL)
		return;

	float minX = pSprite->m_nHalfWidth;
	float maxX = GetWalkWidth() - minX;

	if (pSprite->m_designPt.x <= minX)
		pSprite->m_designPt.x = minX;
	if (pSprite->m_designPt.x >= maxX)
		pSprite->m_designPt.x = maxX;

	float minY = pSprite->m_nHalfHeight;
	float maxY = GetWalkHeight() + minY;

	if (pSprite->m_designPt.y <= minY)
		pSprite->m_designPt.y = minY;
	if (pSprite->m_designPt.y >= maxY)
		pSprite->m_designPt.y = maxY;

	pSprite->setPosition(pSprite->m_designPt);
}

void CMapLayer::update( float delta )
{
	//更新坐标
	if (m_pCharacter)
	{
		//刷新前进目标
		m_pCharacter->UpdatePosition(delta);
		FixPosition(m_pCharacter);

	}

	//2d游戏人物处在游戏最中心，其实就是整个layer向下滚动，这里没设计好，下次再改
	if (m_pCharacter)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//中心点
		CCPoint ptCenter  = ccp(size.width/2,size.height/2);

		float x = MAX(m_pCharacter->getPositionX(),size.width/2);
		float y = MAX(m_pCharacter->getPositionY(),size.height/2);

		x = MIN(x,GetTotalWidth() - size.width/2);
		y = MIN(y,GetTotalHeight() - size.height/2);

		CCPoint viewPoint = ccpSub(ptCenter,ccp(x,y));

		setPosition(viewPoint);
	}

}

//执行行走
void CMapLayer::didChangeDirectorTo( SimpleDPad* simpleDPad,cocos2d::CCPoint direction )
{
	if (m_pCharacter)
	{
		m_pCharacter->Walk(direction);		//行走
	}
}

void CMapLayer::isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)
{
	if (m_pCharacter)
		m_pCharacter->Walk(direction);
}

void CMapLayer::simpleDPadTouchEnded( SimpleDPad* simpleDpad )
{
	//玩家停止 移动
	if (m_pCharacter && m_pCharacter->m_nCurState == kActionStateWalk)
		m_pCharacter->Idle();
}