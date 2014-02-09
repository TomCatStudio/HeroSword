#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "cocos2d.h"

USING_NS_CC;

class CGameLayer;	// ��CGameLayer����actionJoypadStart/Update/Ended
// ҡ��
// ��ʵ������ccTouchBegan����Ӧ�¼��е���CCGameLayer�Ĵ������õ��������ﲻ��ֱ����CGameLayer
// ���ǽ�CGameLayer�е���Щ������д��һ���ӿ��У�Ȼ����CGameLayer�̳У��������Ǹ��ӿ��༴��
class CJoypad : public CCLayer
{
public:
	~CJoypad();

	virtual bool init();
	CREATE_FUNC(CJoypad);

	void keyStart(float degrees);
	void keyUpdate(float degrees);
	void keyEnded(float degrees);

	void setGameLayer(CGameLayer* pGameLayer) { m_pGameLayer = pGameLayer;}
private:
	CJoypad();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	inline void UpdateRotation();
	inline void UpdateTouchRotation(CCTouch* touch, CCEvent* event);

	CCSize		m_szWinSize;
	CCPoint		m_ptCenter;
	CCSprite	*m_pControlSprite;
	CCPoint		m_ptDefaultPoint;

	float		m_fDefaultRotation;
	float		m_fRotation;

	CGameLayer	*m_pGameLayer;
	bool		m_bKeydown;
};


#endif  // _ACTION_BUTTON_H_