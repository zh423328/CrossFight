//////////////////////////////////////////////////////////////////////////
//Ò¡¸Ë
//////////////////////////////////////////////////////////////////////////
#ifndef _HUDLAYER_H_
#define _HUDLAYER_H_

#include "GlobalDefine.h"

class SimpleDPad;
class SimpleDPadDelegate;

class CHudLayer : public CCLayer
{
public:
	CHudLayer();
	~CHudLayer();

	static CHudLayer * CreateWithDelegate(SimpleDPadDelegate *pDelegate);

	bool initWithDelegate(SimpleDPadDelegate *pDelegate);


	SimpleDPad * m_pDPad;
};
#endif