//
//  Step2Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step2Layer_hpp
#define Step2Layer_hpp

#include "cocos2d.h"
#include "Hero.h"

class Step2Layer : public cocos2d::Layer
{
public:
    CREATE_FUNC(Step2Layer);
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Size winSize;
    cocos2d::Sprite* hero;  //自機
    
    cocos2d::Sprite* yunomi1;
    cocos2d::Sprite* yunomi2;
    
    
    static cocos2d::Scene* createScene();
    
protected:
    Step2Layer();
    virtual ~Step2Layer();
    
    int swingCnt;
    bool isSwing;

    void initGame();
    
    void createHero();  //自機の生成
    void swingAnimation(bool isSwing);
    void moveHero();

    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
