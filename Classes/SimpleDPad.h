///////////////////////////////////////////////////////////////////////////
//ң�е㴥
//////////////////////////////////////////////////////////////////////////
#ifndef _SIMPLEDPAD_H_
#define _SIMPLEDPAD_H_

#include "GlobalDefine.h"

class SimpleDPad;

//��������࣬����Ķ��Ƕ���
class SimpleDPadDelegate
{
public:
	//ִ�� ���߶���
	virtual void didChangeDirectorTo(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)=0;  //���麯��

	//���һ������Ұ�סң�в���
	virtual void isHoldingDirector(SimpleDPad* simpleDPad,cocos2d::CCPoint direction)=0;

	//����������������õĺ���
	virtual void simpleDPadTouchEnded(SimpleDPad* simpleDpad)=0;
};

class SimpleDPad : public CCSprite,public CCTargetedTouchDelegate
{
public:
	SimpleDPad(void);
	~SimpleDPad(void);

	//����ң��
	static SimpleDPad* CreateWithFile(const char * szFileName,float radius,SimpleDPadDelegate *pDelegate);

	bool initWithFile(const char * szFileName,float radius);

	void onEnterTransitionDidFinish();
	void onExit();

	void update(float dt);

	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);

	void updateDirectionForTouchLocation(CCPoint location);  //�����㷽��

	SimpleDPadDelegate* m_pDelegate; //ί��

	bool m_bHold;					//�Ƿ�ס

	float m_fradius; //�뾶
	CCPoint m_ptDirection;  //���� ����
};

#endif