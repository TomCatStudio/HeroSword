#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_

#include "cocos2d.h"
#include "cocos-ext.h"  

USING_NS_CC;
USING_NS_CC_EXT;


// 角色动作状态
enum eCharState
{
	csStand,
	csRunning,
	csAttack
};

// 角色动作组织
class CActionSprite : public CCNode
{
public:
	virtual ~CActionSprite();

	virtual bool init();
	virtual void update(float delta);

	// 攻击
	void acceptAttack(CCObject* pObject);
	// 是否翻转，图片“左右”走动
	bool isFlip() { return m_bFlipX;}
	bool isAttack() { return (m_nState == csAttack);}
	// 开始跑动 附带方向，方向是一个小于 360 的角度
	void runWithDegrees(float degrees);
	 // 跑动
	virtual void hRunning();
	// 跑动，改变方向
	void moveWithDegrees(float degrees);
	// 停止跑动
	void idle();
	 // 站立
	virtual void hStand();
	// 简单 ai 实现
	virtual void ai() {}
	// 屏幕检测，人物不能走出屏幕之外 并且只能在下方
	void checkLocation();
	void postAttack();

	// get & set
	float getZLocation() { return (getPositionY() + m_fZLocation);}
	float getBloodPercent() { return (m_fBlood / m_fBloodMax);}
	int getRoleType() { return m_nRoleType;}

	void setZLocation(float z) { m_fZLocation = z;}
	void setSprite(const char *szImage, const CCPoint &pos);
	void setAttackRect();		// 设置打击范围
	void setRoleType(int nType) { m_nRoleType = nType;}
protected:
	CActionSprite();

	virtual void onEnter();
	virtual void onExit();

	void blood();		// 掉血

	CCNode			*m_pSprite;
	int				m_nState;

	bool			m_bIsRun;
	float			m_fRunDegrees;
	float			m_fSpeed;

	CCFiniteTimeAction		*m_pActionStand;
	CCFiniteTimeAction		*m_pActionRunning;
	CCFiniteTimeAction		*m_pActionAttack;
	CCFiniteTimeAction		*m_pActionAttackJump;
	CCFiniteTimeAction		*m_pActionAttackT;

	float			m_fZLocation;		// 脚下所占的位置，y 坐标，用以判断 前后层次关系
	bool			m_bFlipX;
	bool			m_bImageFlipX;		// 默认图片是否面向右
	float			m_fAttackRange;		// 打击距离

	float			m_fBlood;
	float			m_fBloodMax;
	CCLabelTTF		*m_pLossBlood;
	int				m_nRoleType;
};

// 英雄类
class CHero : public CActionSprite
{
public:
	virtual bool init();
	CREATE_FUNC(CHero);

	void attack(int nAttackType);
private:
	void initAction();
	void hAttack(int nAttackType);	
	void attackEnded();
};

// 机器人类
class CRobot : public CActionSprite
{
public:
	virtual bool init();
	CREATE_FUNC(CRobot);

	void setSprite(CCNode *pArmature, const CCPoint &pos);
	void attack();
private:
	void hAttack();	
	virtual void hStand();
	virtual void hRunning();
	void attackEnded(CCArmature *pArmature, MovementEventType movementType, const char *movementID);
	virtual void ai();
	
	float			m_fStartTime;
};

#endif  // _CHARACTERS_H_
