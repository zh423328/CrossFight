#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
//////////////////////////////////////////////////////////////////////////
//游戏主类，存放地图类和ui类和人物
//////////////////////////////////////////////////////////////////////////
#include "GlobalDefine.h"
#include "SimpleDPad.h"

class IActionSprite;
class CMapLayer;
class CCharacter;
class CHudLayer;
//触摸代理
class CGameLayer : public CCLayer,public SimpleDPadDelegate
{
public:
	CGameLayer();
	~CGameLayer();

	virtual bool init();

	bool initMap(const char *szMapName);
	bool initCharacter();
	bool initHud();

	virtual void update(float delta);

	//修坐标
	void FixPosition(IActionSprite * pSprite);


	//执行 行走动作
	virtual void didChangeDirectorTo(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//按住一直走
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//触摸方向键结束调用的函数
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDpad);



	CREATE_FUNC(CGameLayer);

	CCharacter*	m_pCharacter;	//主角
	CMapLayer * m_pMapLayer;	//当前地图类
	CHudLayer * m_pHudLayer;
};


#endif