#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class CGameLayer;
class CJoypad;
class CAttackButton;
class CAttackEffect;

// 攻击按钮类型
enum eAttackButtonType
{
	abtNone,
	abtAttack,
	abtAttackA,
	abtAttackB,
	abtAttackMax,
};

// 人物类型
enum eRoleType
{
	rtHero,
	rtRobot,
};

// 人物状态
class CState : public CCNode
{
public:
	virtual bool init();
	CREATE_FUNC(CState);

	static CState* createHero();
	static CState* createRobot();
	
	// get & set
	void setBloodSprite(CCSprite *pSprite) { m_pBloodSprite = pSprite;}
	void setBlood(int value);
	void setRoleType(int nType) { m_nRoleType = nType;}
private:
	virtual void onEnter();
	virtual void onExit();

	void notifyChangeStatus(CCObject *pObject);

	CCSprite		*m_pBloodSprite;
	int				m_nRoleType;
};

// 包含了三个攻击按钮和一个摇杆控件
class CHudLayer : public CCLayer
{
public:	
	~CHudLayer();

	virtual bool init();
	CREATE_FUNC(CHudLayer);

	void attackButtonClick(int nAttackType);

	void keyAttack(int nButtonType);
	void keyAttackUp(int nButtonType);

	// get & set
	void setDelegate(CGameLayer *pGameLayer);
private:
	CHudLayer();

	CCSize			m_szWinSize;
	CCPoint			m_ptCenter;
	
	CGameLayer		*m_pGameLayer;
	CJoypad			*m_pJoypad;
	CAttackButton	*m_pAttackButton;
	CAttackEffect	*m_pAttackButtonA;
	CAttackEffect	*m_pAttackButtonB;

	CState			*m_pHero;
	CState			*m_pRobot;
};

#endif  // _HUD_LAYER_H_