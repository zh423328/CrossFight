//////////////////////////////////////////////////////////////////////////
//��ͼ�ࣺ���ص�ͼtmx
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include "GlobalDefine.h"

class CMapLayer : public CCLayer
{
	//��ͼ��
public:
	CMapLayer();
	~CMapLayer();

	static CMapLayer * createWithTmxName(const char *  szFileName);

	bool	initWithFileName(const char* szFileName);

	//��ȡ�����ߵĸ߶ȺͿ��
	float	GetWidth();

	float	GetHeight();	

	CCTMXTiledMap* m_pMap;	//��ǰ��ͼ
};
#endif