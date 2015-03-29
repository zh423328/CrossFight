#include "GameLayer.h"
#include "MapLayer.h"
#include "Character.h"
#include "HudLayer.h"

CGameLayer::CGameLayer()
{
	m_pMapLayer = NULL;
	m_pHudLayer = NULL;
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

	
		//添加触控
		initHud();

		setTouchEnabled(true);

		//scheduleUpdate();	//更新坐标

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



bool CGameLayer::initHud()
{
	m_pHudLayer = CHudLayer::CreateWithDelegate(m_pMapLayer);
	if (m_pHudLayer)
	{
		this->addChild(m_pHudLayer,2);

		return true;
	}

	return false;
}


