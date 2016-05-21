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


class OchaLayer : public cocos2d::Layer
{
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

protected:
    void step1();
    void step2();
    void step3();
    void step4();
    void step5();
    void step6();
    void step7();
};
#endif
