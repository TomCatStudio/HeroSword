#include "JoyPad.h"
#include "GameLayer.h"

CJoypad::CJoypad()
{
	m_szWinSize = CCDirector::sharedDirector()->getWinSize();
	m_ptCenter = ccp(m_szWinSize.width/2, m_szWinSize.height/2);
	m_pControlSprite = NULL;
	m_fDefaultRotation = m_fRotation = 0.0f;

	m_pGameLayer = NULL;
	m_bKeydown = false;
}

CJoypad::~CJoypad()
{

}

bool CJoypad::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		// 控制杆所在位置
		m_ptDefaultPoint = ccp(110, 110);
		// 默认旋转角度，以使开口正对右侧
		m_fDefaultRotation = 26;
		// 实际旋转角度
		m_fRotation = 0;

		setPosition(m_ptDefaultPoint);

		// 添加显示精灵
		addChild(CCSprite::create("Joypad1.png"));
		addChild(CCSprite::create("Joypad2.png"));
		m_pControlSprite = CCSprite::create("Joypad3.png");
		addChild(m_pControlSprite);
		addChild(CCSprite::create("Joypad4.png"));

		UpdateRotation();

		bRet = true;
	} while (0);
	
	return bRet;
}

void CJoypad::keyStart( float degrees )
{
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadStart(m_fRotation);
}

void CJoypad::keyUpdate( float degrees )
{
	m_fRotation = degrees;
	UpdateRotation();
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadUpdate(m_fRotation);
}

void CJoypad::keyEnded( float degrees )
{
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadEnded(m_fRotation);
}

void CJoypad::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void CJoypad::onExit()
{

}

bool CJoypad::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	// 点击点的范围判断
	CCPoint curPoint = touch->getLocation();
	if (curPoint.x > m_szWinSize.width / 2 || curPoint.y > m_szWinSize.height / 2)
		return false;

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	CCAssert(m_pGameLayer, "m_pGameLayer is null");
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadStart(m_fRotation);

	return true;
}

void CJoypad::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	UpdateTouchRotation(touch, event);
	UpdateRotation();

	CCAssert(m_pGameLayer, "m_pGameLayer is null");
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadUpdate(m_fRotation);	
}

void CJoypad::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	UpdateTouchRotation(touch, event);
	UpdateRotation();
	
	CCAssert(m_pGameLayer, "m_pGameLayer is null");
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadEnded(m_fRotation);
}

void CJoypad::UpdateRotation()
{
	m_pControlSprite->setRotation(m_fDefaultRotation + m_fRotation);
}

void CJoypad::UpdateTouchRotation( CCTouch* touch, CCEvent* event )
{
	CCPoint curPoint = touch->getLocation();
	CCPoint sp = ccpSub(curPoint, m_ptDefaultPoint);
	float angle = ccpToAngle(sp);
	angle *= -57.29577951;			// ...
	angle = (angle < 0) ? 360 + angle : angle;
	m_fRotation = angle;
}
