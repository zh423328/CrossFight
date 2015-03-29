#include "MapLayer.h"
#include "Character.h"

CMapLayer::CMapLayer()
{
	m_pMap  = NULL;
}


CMapLayer::~CMapLayer()
{

}

//����tmx�ļ�������ͼ
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
			//���ÿ����
			CCObject *pObj = NULL;
			CCARRAY_FOREACH(m_pMap->getChildren(),pObj)
			{
				CCTMXLayer * pTmxLayer = dynamic_cast<CCTMXLayer*>(pObj);
				if (pTmxLayer)
				{
					pTmxLayer->getTexture()->setAliasTexParameters();		//�����
				}
			}	
			m_pMap->setPosition(CCPointZero);
			this->addChild(m_pMap);
		}

		//�������
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
	//��������
	if (m_pCharacter)
	{
		//ˢ��ǰ��Ŀ��
		m_pCharacter->UpdatePosition(delta);
		FixPosition(m_pCharacter);

	}

	//2d��Ϸ���ﴦ����Ϸ�����ģ���ʵ��������layer���¹���������û��ƺã��´��ٸ�
	if (m_pCharacter)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//���ĵ�
		CCPoint ptCenter  = ccp(size.width/2,size.height/2);

		float x = MAX(m_pCharacter->getPositionX(),size.width/2);
		float y = MAX(m_pCharacter->getPositionY(),size.height/2);

		x = MIN(x,GetTotalWidth() - size.width/2);
		y = MIN(y,GetTotalHeight() - size.height/2);

		CCPoint viewPoint = ccpSub(ptCenter,ccp(x,y));

		setPosition(viewPoint);
	}

}

//ִ������
void CMapLayer::didChangeDirectorTo( SimpleDPad* simpleDPad,cocos2d::CCPoint direction )
{
	if (m_pCharacter)
	{
		m_pCharacter->Walk(direction);		//����
	}
}

void CMapLayer::isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)
{
	if (m_pCharacter)
		m_pCharacter->Walk(direction);
}

void CMapLayer::simpleDPadTouchEnded( SimpleDPad* simpleDpad )
{
	//���ֹͣ �ƶ�
	if (m_pCharacter && m_pCharacter->m_nCurState == kActionStateWalk)
		m_pCharacter->Idle();
}