#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
//////////////////////////////////////////////////////////////////////////
//游戏主类，存放地图类和ui类和人物
//////////////////////////////////////////////////////////////////////////
#include "GlobalDefine.h"

class IActionSprite;
class CMapLayer;
class CMapPlayer;
class CHudLayer;
//触摸代理
class CGameLayer : public CCLayer
{
public:
	CGameLayer();
	~CGameLayer();

	virtual bool init();

	bool initMap(const char *szMapName);
	bool initHud();


	CREATE_FUNC(CGameLayer);

	CMapPlayer*	m_pCharacter;	//主角
	CMapLayer * m_pMapLayer;	//当前地图类
	CHudLayer *		m_pHudLayer;			//触控层
};


#endif