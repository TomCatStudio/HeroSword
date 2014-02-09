#ifndef _ACTION_BUTTON_H_
#define _ACTION_BUTTON_H_

#include "cocos2d.h"

USING_NS_CC;

class CHudLayer;	// ��HudLayer����attackButtonClick(nAttackType)
// ������ť
class CActionButton : public CCNode, public CCTouchDelegate
{
public:
	CActionButton();
	virtual ~CActionButton();

	virtual bool init(const char *szImage);
	void click();
	void clickUp();
	virtual bool IsCanClick() { return true;}

	// get & set
	CCRect GetRect();
	int GetAttackType() { return m_nAttackType;}
	
	void SetAttackType(int nAttackType) { m_nAttackType = nAttackType;}
	void SetHudLayer(CHudLayer *pHudLayer) { m_pHudLayer = pHudLayer;}
protected:
	virtual void onEnter();
	virtual void onExit();

	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	virtual void beganAnimation() {}
	virtual void endedAnimation() {}

	CCSprite		*m_pSprite;	
	int				m_nAttackType;
	CHudLayer		*m_pHudLayer;
};


// ������ť
// ��ͨ������ť��Ч������ʼ������ͼƬ�ز�
class CAttackButton : public CActionButton
{
public:
	~CAttackButton();
	virtual bool init(const char *szImage);
	static CAttackButton* create(const char *szImage);

	virtual bool IsCanClick();
private:
	CAttackButton();

	virtual void beganAnimation();
	virtual void endedAnimation();

	CCSprite		*m_pNormal;

	float			m_fDefaultScale;
	float			m_fMaxScale;
	CCAction		*m_pInAction;
	CCAction		*m_pOutAction;

	float			m_fClickTime;
};

// ������Ч
// ��Ч�����и���ȴЧ����������һ��ʱ�䷶Χ������������ʹ��һ�� ��ת�� Progress ���ﵽ������Ч��
class CAttackEffect : public CActionButton
{
public:
	~CAttackEffect();
	static CAttackEffect* create(const char *szImage);

	virtual bool IsCanClick();
private:
	CAttackEffect();

	virtual void beganAnimation();
	virtual void endedAnimation();
	void endColdTime();

	CCProgressTimer		*m_pNormal;
	CCAction			*m_pInAction;
	bool				m_bCanClick;
};

#endif  // _ACTION_BUTTON_H_