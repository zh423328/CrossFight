//////////////////////////////////////////////////////////////////////////
//地图类：加载地图tmx
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include "GlobalDefine.h"

class CMapLayer : public CCLayer
{
	//地图类
public:
	CMapLayer();
	~CMapLayer();

	static CMapLayer * createWithTmxName(const char *  szFileName);

	bool	initWithFileName(const char* szFileName);

	//获取可行走的高度和宽度
	float	GetWidth();

	float	GetHeight();	

	CCTMXTiledMap* m_pMap;	//当前地图
};
#endif