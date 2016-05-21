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
: _stepIndex(0)
, _rotateStep(0.0f)
, _rotateFirstStep(0.0f)
, _rotateLastStep(0.0f)
, _accCheck(false)
, _accCheck2(false)
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

        auto visibleRect = Rect::ZERO;
        {
            visibleRect.origin = Director::getInstance()->getVisibleOrigin();
            visibleRect.size   = Director::getInstance()->getVisibleSize();
        }


        //傾き検知用
        if (auto input = InputLayer::create())
        {
            input->setName("input");
            this->addChild(input);
        }



        //DEBUG 1
        if (auto label = Label::createWithSystemFont("debug_label_guigui", "", 16.0f))
        {
            label->setName("debug_label_guigui");

            const auto pos = Point(visibleRect.getMinX(), visibleRect.getMaxY() - 10.0f);
            label->setPosition(pos);

            label->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
            label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

            this->addChild(label);
        }

        //DEBUG 2
        if (auto label = Label::createWithSystemFont("debug_label_guru x 2", "", 16.0f))
        {
            label->setName("debug_label_guru x 2");

            const auto pos = Point(visibleRect.getMinX(), visibleRect.getMaxY() - 30.0f);
            label->setPosition(pos);

            label->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
            label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

            this->addChild(label);
        }


        //DEBUG 3 (仮ボタン)
        if (auto label = Label::createWithSystemFont("douzo", "", 32.0f))
        {
            auto callback = [this](Ref * pSender) {
                if (this->getStepIndex() == 5)
                {
                    cocos2dExt::NativeInterface::getTextFromWatch("DOUZO");
                }
            };

            if (auto item = MenuItemLabel::create(label, callback))
            {
                if (auto menu = Menu::createWithItem(item))
                {
                    const auto pos = visibleRect.origin + Point(visibleRect.size.width * 0.1f,
                                                                visibleRect.size.height * 0.25f);
                    menu->setPosition(pos);

                    this->addChild(menu);
                }
            }
        }


        result = true;
    } while (0);

    return result;
}


#pragma mark -
void OchaLayer::onEnter()
{
    Layer::onEnter();


    //グイグイっ
    {
        auto callback = [this] (EventCustom * event) {

            if (this->getStepIndex() == 6)
            {
                //MEMO: 傾きセンサーの y軸 をチェックする (0.0f -> -90.0f -> 0.0f)

                if (auto acc = static_cast<Acceleration *>(event->getUserData()))
                {
                    const auto text = StringUtils::format("acc... x:%8.2f, y:%8.2f, z:%8.2f", acc->x, acc->y, acc->z);

                    if (auto label = dynamic_cast<Label *>(this->getChildByName("debug_label_guigui")))
                    {
                        label->setString(text);
                    }

                    //器を持ち上げていなければ
                    if (!this->_accCheck)
                    {
                        //器を(はじめて)持ち上げたら
                        if (acc->y < -0.15f)
                        {
                            this->_accCheck = true;
                        }
                    }
                    //お茶を飲んだら
                    else if (!this->_accCheck2)
                    {
                        if (acc->y <= -0.9f)
                        {
                            this->_accCheck2 = true;
                        }
                    }
                    else
                    {
                        //水平に戻したら終了
                        if (acc->y > -0.2f)
                        {
                            //終了処理へ
                            this->step7();
                        }
                    }
                }
            }
        };

        if (auto listener = EventListenerCustom::create(EVENT_NAME__ACCELERATION, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }

    //「シャカシャカ」、「どうぞ」
    {
        auto callback = [this](EventCustom * event) {

            if (auto data = static_cast<Value *>(event->getUserData()))
            {
                const auto message = data->asString();
                if (message.compare("SWING") == 0)
                {
                    //「シャカシャカ」
                }
                else if (message.compare("DOUZO") == 0)
                {
                    //「どうぞ」
                    this->step6();
                }
            }
        };

        if (auto listener = EventListenerCustom::create(EVENT_NAME__TEXTFROMWATCH, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }

    this->scheduleUpdate();
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

    this->getEventDispatcher()->removeEventListenersForTarget(this);

    this->unscheduleUpdate();
}


#pragma mark -
void OchaLayer::update(float delta)
{
    //水平回転チェック(方位)
    if (this->getStepIndex() == 4)
    {
        //方位の取得
        auto pos = cocos2dExt::NativeInterface::getCompass();

        const auto tmp = pos.x - this->_rotateLastStep;
        if (tmp > 0.0f)
        {
            this->_rotateStep += tmp;
        }
        this->_rotateLastStep = pos.x;

        const auto text = StringUtils::format("trueHeading:%8.2f, rotateStep:%8.2f, check:%8.2f",
                                              pos.x, this->_rotateStep, ((this->_rotateStep - this->_rotateFirstStep)));
        if (auto label = dynamic_cast<Label *>(this->getChildByName("debug_label_guru x 2")))
        {
            label->setString(text);
        }

        //3回転以上
        if ((this->_rotateStep - this->_rotateFirstStep) >= (360.0f * 3.0f))
        {
            //次のステップへ
            this->step5();
        }
    }
}


#pragma mark - ### 茶道の工程 ###
void OchaLayer::step1()
{
    //MARK: 工程チェック用変数の初期化
    {
        this->_rotateStep       = 0.0f;
        this->_rotateFirstStep  = 0.0f;
        this->_rotateLastStep   = 0.0f;
    }


    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("こな入れてぇぇぇの");
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
        cocos2dExt::NativeInterface::speech("お湯入れてぇぇぇの");
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
        cocos2dExt::NativeInterface::speech("お茶立ててぇぇぇの");
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
    //最初の方位を取得
    this->_rotateStep       = cocos2dExt::NativeInterface::getCompass().x;
    this->_rotateLastStep   = this->_rotateStep;
    this->_rotateFirstStep  = this->_rotateStep;

    cocos2dExt::NativeInterface::putTextToWatch(this->_stepIndex++);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お茶まわしぃぃの");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

//                                   //自動で次のステップへ
//                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step5, this)),
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
        cocos2dExt::NativeInterface::speech("お茶渡しぃぃの");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(2.0f),

//                                   //自動で次のステップへ
//                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step6, this)),
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

//                                   //自動で次のステップへ
//                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step7, this)),
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
                                   DelayTime::create(5.0f),

                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step1, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}
