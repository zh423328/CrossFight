#ifndef CHARACTER_H_
#define CHARACTER_H_
//////////////////////////////////////////////////////////////////////////
//��ɫ��
//////////////////////////////////////////////////////////////////////////
#include "ActionSprite.h"

class CMapPlayer : public IActionSprite
{
public:
	CMapPlayer();
	~CMapPlayer();

	virtual void CreateAction();

	virtual bool init();

	CREATE_FUNC(CMapPlayer);
};
#endif