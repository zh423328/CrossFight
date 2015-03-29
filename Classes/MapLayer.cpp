#include "MapLayer.h"

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

			return true;
		}
	}
	return false;
}

float CMapLayer::GetWidth()
{
	if (m_pMap)
	{
		return m_pMap->getTileSize().width*m_pMap->getMapSize().width;
	}
	else
		return 0.0f;
}

float CMapLayer::GetHeight()
{
	if (m_pMap)
	{
		return 3*m_pMap->getTileSize().height;
	}

	return 0.0f;
}



