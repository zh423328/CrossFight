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
		//��ӵ�ͼ
		initMap("pd_tilemap.tmx");

	
		//��Ӵ���
		initHud();

		setTouchEnabled(true);

		//scheduleUpdate();	//��������

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


