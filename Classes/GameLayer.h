#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
//////////////////////////////////////////////////////////////////////////
//��Ϸ���࣬��ŵ�ͼ���ui�������
//////////////////////////////////////////////////////////////////////////
#include "GlobalDefine.h"

class IActionSprite;
class CMapLayer;
class CMapPlayer;
class CHudLayer;
//��������
class CGameLayer : public CCLayer
{
public:
	CGameLayer();
	~CGameLayer();

	virtual bool init();

	bool initMap(const char *szMapName);
	bool initHud();


	CREATE_FUNC(CGameLayer);

	CMapPlayer*	m_pCharacter;	//����
	CMapLayer * m_pMapLayer;	//��ǰ��ͼ��
	CHudLayer *		m_pHudLayer;			//���ز�
};


#endif