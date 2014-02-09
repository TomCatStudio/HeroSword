#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class CHero;
class CRobot;
// 游戏管理层
// 统一的控制管理
class CGameLayer : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(CGameLayer);

	virtual void update(float delta);
	
	void actionJoypadStart(float degrees);
	void actionJoypadUpdate(float degrees);
	void actionJoypadEnded(float degrees);
	void attackButtonClick(int nAttackType);
private:
	CCSize		m_szWinSize;
	CCPoint		m_ptCenter;
	CHero		*m_pHero;
	CRobot		*m_pRobot;
};

#endif  // _GAME_LAYER_H_