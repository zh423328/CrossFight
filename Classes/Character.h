#ifndef CHARACTER_H_
#define CHARACTER_H_
//////////////////////////////////////////////////////////////////////////
//��ɫ��
//////////////////////////////////////////////////////////////////////////
#include "ActionSprite.h"

class CCharacter : public IActionSprite
{
public:
	CCharacter();
	~CCharacter();

	virtual void CreateAction();

	virtual bool init();

	CREATE_FUNC(CCharacter);
};
#endif