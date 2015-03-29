#include "HudLayer.h"
#include "SimpleDPad.h"

CHudLayer::CHudLayer()
{
	m_pDPad = NULL;
}

CHudLayer::~CHudLayer()
{

}

CHudLayer * CHudLayer::CreateWithDelegate( SimpleDPadDelegate *pDelegate )
{
	CHudLayer *pHudLayer = new CHudLayer();
	if (pHudLayer &&pHudLayer->initWithDelegate(pDelegate))
	{
		pHudLayer->autorelease();

		return pHudLayer;
	}
	else
	{
		CC_SAFE_DELETE(pHudLayer);
	}

	return pHudLayer;
}

bool CHudLayer::initWithDelegate( SimpleDPadDelegate *pDelegate )
{
	if (CCLayer::init())
	{
		m_pDPad = SimpleDPad::CreateWithFile("pd_dpad.png",64.0f,pDelegate);
		if (m_pDPad)
		{
			m_pDPad->setPosition(ccp(64,64));
			this->addChild(m_pDPad);
		}
		return true;
	}

	return false;
}


