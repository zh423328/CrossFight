//////////////////////////////////////////////////////////////////////////
//”Œœ∑:∫·∞Ê¥≥πÿ”Œœ∑
/////////////////////////////////////////////////////////////////////////
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "GlobalDefine.h"

class CGameLayer;
class CGameScene : public CCScene
{
public:
	CGameScene();
	~CGameScene();

	virtual bool init();

	CREATE_FUNC(CGameScene);

	CGameLayer *	m_pGameLayer;
};

#endif