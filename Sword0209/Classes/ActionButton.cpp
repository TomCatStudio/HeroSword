#include "ActionButton.h"
#include "HudLayer.h"

CActionButton::CActionButton()
{
	m_pSprite = NULL;
	m_pHudLayer = NULL;
}

CActionButton::~CActionButton()
{

}

bool CActionButton::init(const char *szImage)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCNode::init());

		m_pSprite = CCSprite::create(szImage);
		addChild(m_pSprite);

		bRet = true;
	} while (0);
	return bRet;
}

void CActionButton::click()
{
	if (IsCanClick() && m_pHudLayer)
	{
		m_pHudLayer->attackButtonClick(GetAttackType());
		beganAnimation();
	}
}

void CActionButton::clickUp()
{
	endedAnimation();
}

cocos2d::CCRect CActionButton::GetRect()
{
	CCSize size = m_pSprite->getContentSize();
	return CCRect(-size.width/2, -size.height/2, size.width, size.height);
}

void CActionButton::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCNode::onEnter();
}

void CActionButton::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

bool CActionButton::containsTouchLocation( CCTouch* touch )
{
	return GetRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool CActionButton::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	// 区域判断
	if (!this->containsTouchLocation(touch))
		return false;

	// 播放点击动画
	click();

	return true;
}

void CActionButton::ccTouchMoved( CCTouch* touch, CCEvent* event )
{

}

void CActionButton::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	endedAnimation();
}

CAttackButton::CAttackButton()
{
	m_fDefaultScale = 0.35;
	m_fMaxScale = 0.5;

	m_pNormal = CCSprite::create("AttackO.png");
	m_pNormal->retain();

	CCFiniteTimeAction *pScale = CCScaleTo::create(0.1, m_fDefaultScale);
	CCFiniteTimeAction *pFadeIn = CCFadeIn::create(0.1);
	m_pInAction = CCSpawn::create(pScale, pFadeIn, NULL);
	m_pInAction->retain();

	pScale = CCScaleTo::create(0.2f, m_fMaxScale);
	CCFiniteTimeAction *pFade = CCFadeOut::create(0.2);
	m_pOutAction = CCSpawn::create(pScale, pFade, NULL);
	m_pOutAction->retain();

	m_fClickTime = 0.0f;
}

CAttackButton::~CAttackButton()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
	CC_SAFE_RELEASE(m_pOutAction);
}

bool CAttackButton::init( const char *szImage )
{
	bool bRet = CActionButton::init(szImage);
	if (m_pNormal)
		m_pNormal->setScale(m_fMaxScale);
	return bRet;
}

CAttackButton* CAttackButton::create( const char *szImage )
{
	CAttackButton *pAttackButton = new CAttackButton();
	if (pAttackButton && pAttackButton->init(szImage))
	{
		pAttackButton->autorelease();
		return pAttackButton;
	}
	else
	{
		delete pAttackButton;
		return NULL;
	}
}

void CAttackButton::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction((CCAction*)m_pInAction->copy());
	
	cc_timeval timeVal;
	CCTime::gettimeofdayCocos2d(&timeVal, 0);
	m_fClickTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
}

void CAttackButton::endedAnimation()
{
	m_pNormal->stopAllActions();
	m_pNormal->runAction((CCAction*)m_pOutAction->copy());
}

bool CAttackButton::IsCanClick()
{
	cc_timeval timeVal;
	CCTime::gettimeofdayCocos2d(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
	return (curTime - m_fClickTime > 600);
}

CAttackEffect::CAttackEffect()
{
	CCSprite *pCold = CCSprite::create("AttackFreeze.png");
	m_pNormal = CCProgressTimer::create(pCold);
	m_pNormal->setType(kCCProgressTimerTypeRadial);
	m_pNormal->setReverseDirection(true);
	m_pNormal->setScale(0.43);
	m_pNormal->retain();

	CCFiniteTimeAction *to = CCProgressTo::create(0, 99.999);
	CCFiniteTimeAction *to1 = CCProgressTo::create(2, 0);
	CCFiniteTimeAction *callback = CCCallFunc::create(this, callfunc_selector(CAttackEffect::endColdTime));
	m_pInAction = CCSequence::create(to, to1, callback, NULL);
	m_pInAction->retain();
	m_bCanClick = true;
}

CAttackEffect::~CAttackEffect()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
}


CAttackEffect* CAttackEffect::create( const char *szImage )
{
	CAttackEffect *pAttackEffect = new CAttackEffect();
	if (pAttackEffect && pAttackEffect->init(szImage))
	{
		pAttackEffect->autorelease();
		return pAttackEffect;
	}
	else
	{
		delete pAttackEffect;
		return NULL;
	}
}

void CAttackEffect::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction((CCAction*)m_pInAction->copy());
	m_bCanClick = false;
}

void CAttackEffect::endedAnimation()
{
	
}

bool CAttackEffect::IsCanClick()
{
	return m_bCanClick;
}

void CAttackEffect::endColdTime()
{
	m_bCanClick = true;
}