//////////////////////////////////////////////////////////////////////////
//��ͼ�ࣺ���ص�ͼtmx
//////////////////////////////////////////////////////////////////////////
#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_

#include "GlobalDefine.h"
#include "SimpleDPad.h"

class CMapPlayer;
class IActionSprite;
class CMapLayer : public CCLayer,public SimpleDPadDelegate
{
	//��ͼ��
public:
	CMapLayer();
	~CMapLayer();

	static CMapLayer * createWithTmxName(const char *  szFileName);

	bool	initWithFileName(const char* szFileName);

	virtual	void update(float dt);

	//��ȡ�����ߵĸ߶ȺͿ��
	float	GetWalkWidth();

	float	GetWalkHeight();

	
	//����
	float	GetTotalWidth();
	float	GetTotalHeight();

	//��ʼ������
	bool	initCharacter();

	//������
	void FixPosition(IActionSprite * pSprite);


	//ִ�� ���߶���
	virtual void didChangeDirectorTo(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//��סһֱ��
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//����������������õĺ���
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDpad);


	CCTMXTiledMap* m_pMap;			//��ǰ��ͼ
	CMapPlayer *   m_pCharacter;	//����
};
#endif