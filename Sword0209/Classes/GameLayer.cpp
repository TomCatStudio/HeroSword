#include "GameLayer.h"
#include "HudLayer.h"
#include "Characters.h"

bool CGameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_szWinSize = CCDirector::sharedDirector()->getWinSize();
		m_ptCenter = ccp(m_szWinSize.width / 2, m_szWinSize.height / 2);

		CCSprite *pBackGround = CCSprite::create("BackGround.png");
        pBackGround->setScaleX(1.25f);
        pBackGround->setScaleY(1.067f);
        
        
		pBackGround->setPosition(m_ptCenter);
		addChild(pBackGround);
		
        m_pHero = CHero::create();
		m_pRobot = CRobot::create();

		CCNode *characters = CCNode::create();
		characters->addChild(m_pHero);
		characters->addChild(m_pRobot);
		addChild(characters);
        
		CHudLayer *pHudLayer = CHudLayer::create();
		pHudLayer->setDelegate(this);
		addChild(pHudLayer);

		scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

void CGameLayer::update( float delta )
{
	float z = m_pHero->getZLocation() > m_pRobot->getZLocation() ? 0 : 1;
	m_pHero->setZOrder(z);
	m_pRobot->setZOrder(1 - z);
}

void CGameLayer::actionJoypadStart( float degrees )
{
	m_pHero->runWithDegrees(degrees);
}

void CGameLayer::actionJoypadUpdate( float degrees )
{
	m_pHero->moveWithDegrees(degrees);
}

void CGameLayer::actionJoypadEnded( float degrees )
{
	m_pHero->idle();
}

void CGameLayer::attackButtonClick( int nAttackType )
{
	m_pHero->attack(nAttackType);
}
