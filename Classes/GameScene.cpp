#include "GameScene.h"
#include "GameLayer.h"
#include "MapLayer.h"

CGameScene::CGameScene()
{
	m_pGameLayer = NULL;
}

CGameScene::~CGameScene()
{

}

bool CGameScene::init()
{
	if (CCScene::init())
	{
		//¼ÓÔØ×ÊÔ´
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprites.plist");


		m_pGameLayer = CGameLayer::create();
		if (m_pGameLayer)
		{
			m_pGameLayer->setPosition(CCPointZero);
			this->addChild(m_pGameLayer);
		}
		return true;
	}

	return false;
}


