//
//  OchaLayer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/22.
//
//

#include "OchaLayer.hpp"

#include "PrivateConfig.h"

#include "CommonFunction.hpp"
#include "NativeInterface.h"
#include "InputLayer.hpp"


USING_NS_CC;


#pragma mark -
OchaLayer::OchaLayer()
{
}
OchaLayer::~OchaLayer()
{
}


#pragma mark -
Scene * OchaLayer::createScene()
{
    auto scene = Scene::create();

    if (auto layer = OchaLayer::create())
    {
        scene->addChild(layer);
    }

    return scene;
}


bool OchaLayer::init()
{
    auto result = false;

    do
    {
        if (! Layer::init())
        {
            break;
        }

        result = true;
    } while (0);

    return result;
}


#pragma mark -
void OchaLayer::onEnter()
{
    Layer::onEnter();
}


void OchaLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();

    //MARK: スタート
    this->step1();
}


void OchaLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}


void OchaLayer::onExit()
{
    Layer::onExit();
}


#pragma mark -
void OchaLayer::update(float delta)
{
}


#pragma mark - ### 茶道の工程 ###
void OchaLayer::step1()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("こな入れて〜の");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step2, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step2()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お湯入れて〜の");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step3, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step3()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お茶立てて〜の");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step4, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step4()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お茶まわし〜の");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step5, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step5()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お茶渡し〜の");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step6, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step6()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("グイグイっ");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step7, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step7()
{
    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("けっこうなお手前を頂戴しました。");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step1, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}
