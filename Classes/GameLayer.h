#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
//////////////////////////////////////////////////////////////////////////
//��Ϸ���࣬��ŵ�ͼ���ui�������
//////////////////////////////////////////////////////////////////////////
#include "GlobalDefine.h"
#include "SimpleDPad.h"

class IActionSprite;
class CMapLayer;
class CCharacter;
class CHudLayer;
//��������
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

	//������
	void FixPosition(IActionSprite * pSprite);


	//ִ�� ���߶���
	virtual void didChangeDirectorTo(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//��סһֱ��
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);

	//����������������õĺ���
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDpad);



	CREATE_FUNC(CGameLayer);

	CCharacter*	m_pCharacter;	//����
	CMapLayer * m_pMapLayer;	//��ǰ��ͼ��
	CHudLayer * m_pHudLayer;
};


#endif