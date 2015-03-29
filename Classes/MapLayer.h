//////////////////////////////////////////////////////////////////////////
//地图类：加载地图tmx
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include "GlobalDefine.h"
#include "SimpleDPad.h"

class CMapPlayer;
class IActionSprite;
class CMapLayer : public CCLayer,public SimpleDPadDelegate
{
	//地图类
public:
	CMapLayer();
	~CMapLayer();

	static CMapLayer * createWithTmxName(const char *  szFileName);

	bool	initWithFileName(const char* szFileName);

	virtual	void update(float dt);

	//获取可行走的高度和宽度
	float	GetWalkWidth();

	float	GetWalkHeight();

	
	//可视
	float	GetTotalWidth();
	float	GetTotalHeight();

	//初始化主角
	bool	initCharacter();

	//修坐标
	void FixPosition(IActionSprite * pSprite);


	//执行 行走动作
	virtual void didChangeDirectorTo(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//按住一直走
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//触摸方向键结束调用的函数
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDpad);


	CCTMXTiledMap* m_pMap;			//当前地图
	CMapPlayer *   m_pCharacter;	//主角
};
#endif