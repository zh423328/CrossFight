///////////////////////////////////////////////////////////////////////////
//遥感点触
//////////////////////////////////////////////////////////////////////////
#ifndef _SIMPLEDPAD_H_
#define _SIMPLEDPAD_H_

#include "GlobalDefine.h"

class SimpleDPad;

//作抽象基类，代理的都是动作
class SimpleDPadDelegate
{
public:
	//执行 行走动作
	virtual void didChangeDirectorTo(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)=0;  //纯虚函数

	//这个一般是玩家按住遥感不放
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)=0;

	//触摸方向键结束调用的函数
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDpad)=0;
};

class SimpleDPad : public CCSprite,public CCTargetedTouchDelegate
{
public:
	SimpleDPad(void);
	~SimpleDPad(void);

	//创建遥感
	static SimpleDPad* CreateWithFile(const char * szFileName,float radius,SimpleDPadDelegate *pDelegate);

	bool initWithFile(const char * szFileName,float radius);

	void onEnterTransitionDidFinish();
	void onExit();

	void update(float dt);

	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);

	void updateDirectionForTouchLocation(CCPoint location);  //坐标算方向

	SimpleDPadDelegate* m_pDelegate; //委托

	bool m_bHold;					//是否按住

	float m_fradius; //半径
	CCPoint m_ptDirection;  //方向 向量
};

#endif