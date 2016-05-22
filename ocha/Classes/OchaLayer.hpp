//
//  OchaLayer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/22.
//
//

#ifndef OchaLayer_hpp
#define OchaLayer_hpp

#include "cocos2d.h"
#include "Hero.h"

class OchaLayer : public cocos2d::Layer
{
public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Size winSize;
    cocos2d::Sprite* hero;
    cocos2d::Sprite* maccha;
    cocos2d::Sprite* yunomi1;
    cocos2d::Sprite* yunomi2;
protected:
    int swingCnt;
    bool isSwing;
    bool isSwingStart;
    
    void initGame();
    
    void createHero();  //自機の生成
    void swingAnimation(bool isSwing);
    void moveHero();

protected:
    OchaLayer();
    virtual ~OchaLayer();

public:
    static cocos2d::Scene * createScene();
    CREATE_FUNC(OchaLayer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExitTransitionDidStart() override;
    virtual void onExit() override;


protected:
    virtual void update(float delta) override;


//public:
    CC_SYNTHESIZE_READONLY(int, _stepIndex, StepIndex);

    //Step4 お茶まわし確認用
    CC_SYNTHESIZE_READONLY(float, _rotateLastStep, RotateLastStep); //一つ前
    CC_SYNTHESIZE_READONLY(float, _rotateFirstStep, RotateFirstStep); //最初の値(回転確認用)
    CC_SYNTHESIZE_READONLY(float, _rotateStep, RotateStep); //集計用

    //Step6 お茶飲み確認用
    CC_SYNTHESIZE_READONLY(bool, _accCheck, AccCheck);      //お茶のみ確認用 (一旦角度がついてから水平に戻ったら)
    CC_SYNTHESIZE_READONLY(bool, _accCheck2, AccCheck2);    //お茶のみ確認用 (一度はグイッと飲むこと)


protected:
    void step1();
    void step2();
    void step3();
    void step4();
    void step5();
    void step6();
    void step7();
    void step8();
};
#endif
