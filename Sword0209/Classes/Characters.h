#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_

#include "cocos2d.h"
#include "cocos-ext.h"  

USING_NS_CC;
USING_NS_CC_EXT;


// ��ɫ����״̬
enum eCharState
{
	csStand,
	csRunning,
	csAttack
};

// ��ɫ������֯
class CActionSprite : public CCNode
{
public:
	virtual ~CActionSprite();

	virtual bool init();
	virtual void update(float delta);

	// ����
	void acceptAttack(CCObject* pObject);
	// �Ƿ�ת��ͼƬ�����ҡ��߶�
	bool isFlip() { return m_bFlipX;}
	bool isAttack() { return (m_nState == csAttack);}
	// ��ʼ�ܶ� �������򣬷�����һ��С�� 360 �ĽǶ�
	void runWithDegrees(float degrees);
	 // �ܶ�
	virtual void hRunning();
	// �ܶ����ı䷽��
	void moveWithDegrees(float degrees);
	// ֹͣ�ܶ�
	void idle();
	 // վ��
	virtual void hStand();
	// �� ai ʵ��
	virtual void ai() {}
	// ��Ļ��⣬���ﲻ���߳���Ļ֮�� ����ֻ�����·�
	void checkLocation();
	void postAttack();

	// get & set
	float getZLocation() { return (getPositionY() + m_fZLocation);}
	float getBloodPercent() { return (m_fBlood / m_fBloodMax);}
	int getRoleType() { return m_nRoleType;}

	void setZLocation(float z) { m_fZLocation = z;}
	void setSprite(const char *szImage, const CCPoint &pos);
	void setAttackRect();		// ���ô����Χ
	void setRoleType(int nType) { m_nRoleType = nType;}
protected:
	CActionSprite();

	virtual void onEnter();
	virtual void onExit();

	void blood();		// ��Ѫ

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

	float			m_fZLocation;		// ������ռ��λ�ã�y ���꣬�����ж� ǰ���ι�ϵ
	bool			m_bFlipX;
	bool			m_bImageFlipX;		// Ĭ��ͼƬ�Ƿ�������
	float			m_fAttackRange;		// �������

	float			m_fBlood;
	float			m_fBloodMax;
	CCLabelTTF		*m_pLossBlood;
	int				m_nRoleType;
};

// Ӣ����
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

// ��������
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
