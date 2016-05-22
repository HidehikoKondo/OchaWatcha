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

#include "TitleLayer.hpp"

#include "audio/include/SimpleAudioEngine.h"


USING_NS_CC;


//#define DEBUG_UI


#pragma mark -
OchaLayer::OchaLayer()
: _stepIndex(0)
, _rotateStep(0.0f)
, _rotateFirstStep(0.0f)
, _rotateLastStep(0.0f)
, _accCheck(false)
, _accCheck2(false)

, swingCnt(0)
, isSwing(false)
, isSwingStart(false)
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

        //お茶たて用
        visibleSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        winSize = Director::getInstance()->getWinSize();
        initGame();  //ゲームの初期化
        
        auto visibleRect = Rect::ZERO;
        {
            visibleRect.origin = Director::getInstance()->getVisibleOrigin();
            visibleRect.size   = Director::getInstance()->getVisibleSize();
        }


        if (auto sprite = Sprite::create("title/background.png"))
        {
            const auto size = sprite->getContentSize();

            const auto rate = MAX(visibleRect.size.width  / size.width,
                                  visibleRect.size.height / size.height);
            sprite->setScale(rate);

            auto pos = Point::ZERO;
            pos = Point(visibleRect.getMidX(), visibleRect.getMidY());

            sprite->setPosition(pos);

            this->addChild(sprite, -10);
        }


        //傾き検知用
        if (auto input = InputLayer::create())
        {
            input->setName("input");
            this->addChild(input);
        }



#ifdef DEBUG_UI
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
        if (auto label = Label::createWithSystemFont("swing", "", 32.0f))
        {
            auto callback = [this](Ref * pSender) {
                if (this->getStepIndex() == 3)
                {
                    cocos2dExt::NativeInterface::getTextFromWatch("SWING");
                }
            };

            if (auto item = MenuItemLabel::create(label, callback))
            {
                if (auto menu = Menu::createWithItem(item))
                {
                    const auto pos = visibleRect.origin + Point(visibleRect.size.width  * 0.1f,
                                                                visibleRect.size.height * 0.5f);
                    menu->setPosition(pos);

                    this->addChild(menu);
                }
            }
        }

        //DEBUG 4 (仮ボタン)
        if (auto label = Label::createWithSystemFont("douzo", "", 32.0f))
        {
            auto callback = [this](Ref * pSender) {
                if (this->getStepIndex() == 4)
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
#endif

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
                            if (this->maccha)
                            {
                                auto action = MoveBy::create(1.0f, Point(0.0f, -50.0f));
                                this->maccha->runAction(action);
                            }

                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("drinking_a_hot_one2.mp3");
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
                    if (this->getStepIndex() == 3)
                    {
                        this->swingAnimation(isSwing = true);
                    }
                }
                else if (message.compare("DOUZO") == 0)
                {
                    //「どうぞ」
                    if (this->getStepIndex() == 4)
                    {
                        this->step5();
                    }
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
    if (this->getStepIndex() == 5)
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

        //反転してもらう
        if ((fabsf(this->_rotateStep) - fabsf(this->_rotateFirstStep)) >= 180.0f)
        {
            //次のステップへ
            this->step6();
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

        this->_stepIndex        = 0;

        this->swingCnt  = 0;
    }


    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お茶の粉を茶碗に入れます");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(5.0f),

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
    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("次にお湯を茶碗に入れます");

        if (this->maccha)
        {
            auto action = MoveBy::create(1.0f, Point(0.0f, 50.0f));
            this->maccha->runAction(action);
        }
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(5.0f),

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
    //茶せん
    {
        hero = Hero::create(ImageType::chasen);
        hero->setScale(0.5f, 0.5f);
        hero->setAnchorPoint(Point(0.5f, 1.1f));

        const auto size = hero->getBoundingBox().size;
        hero->setPosition(Vec2(winSize.width*0.5f, winSize.height + size.height));
        this->addChild(hero, 1);

        {
            auto pos = Point(winSize.width * 0.5f, winSize.height * 0.5f + size.height * 0.8f);
            auto action = MoveTo::create(0.2f, pos);

            hero->runAction(action);
        }
    }


    isSwingStart = true;    //お茶たて開始

    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("ちゃせんを使い、お茶たてます");
    };

    auto action = Sequence::create(
                                   DelayTime::create(0.2f),

                                   CallFunc::create(func),
                                   DelayTime::create(5.0f),

                                   //自動で次のステップへ
                                   //CallFunc::create(CC_CALLBACK_0(OchaLayer::step4, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step4()
{
    //茶せん:
    {
        const auto size = hero->getBoundingBox().size;
        {
            auto pos = Point(winSize.width*0.5f, winSize.height + size.height);

            auto action = Sequence::create(RotateTo::create(0.1f, 0.0f),
                                           MoveTo::create(0.2f, pos),
                                           nullptr);

            hero->runAction(action);
        }
    }


    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("茶碗の正面をお客様の方に向けて、茶碗を差し出します");
    };

    auto action = Sequence::create(
                                   DelayTime::create(0.3f),

                                   CallFunc::create(func),
                                   DelayTime::create(7.0f),

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
    hero->removeFromParent();  //茶せん消去
    isSwingStart = false;  //お茶たて終了
    
    //最初の方位を取得
    this->_rotateStep       = cocos2dExt::NativeInterface::getCompass().x;
    this->_rotateLastStep   = this->_rotateStep;
    this->_rotateFirstStep  = this->_rotateStep;

    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お茶碗を３回左回りに回します");
    };

    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(8.0f),

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
    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("お点前頂戴致します");
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
    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        cocos2dExt::NativeInterface::speech("結構なお点前で");
    };

    auto action = Sequence::create(
                                   DelayTime::create(6.0f),
                                   CallFunc::create(func),
                                   DelayTime::create(3.0f),
                                   //自動で次のステップへ
                                   CallFunc::create(CC_CALLBACK_0(OchaLayer::step8, this)),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


void OchaLayer::step8()
{
    cocos2dExt::NativeInterface::putTextToWatch(++this->_stepIndex);

    auto func = [this]() {
        if (auto sprite = Sprite::create("good.png"))
        {
            auto visibleRect = Rect::ZERO;
            {
                visibleRect.origin = Director::getInstance()->getVisibleOrigin();
                visibleRect.size   = Director::getInstance()->getVisibleSize();
            }

            const auto pos = visibleRect.origin + Point(visibleRect.size.width * 0.8f,
                                                        visibleRect.size.height * 0.8f);
            const auto movePos = visibleRect.origin + Point(visibleRect.size.width * 0.6f,
                                                            visibleRect.size.height * 0.6f);
            sprite->setPosition(pos);

            sprite->setScale(5.0f);

            sprite->setOpacity(0);
            this->addChild(sprite, 100);


            auto action = Spawn::create(
                                        ScaleTo::create(0.5f, 1.0f),
                                        FadeTo::create(0.2f, 255),
                                        MoveTo::create(0.5f, movePos),
                                        nullptr);
            sprite->runAction(action);
        }
    };


    auto end_func = [this]() {
        if (auto scene = TitleLayer::createScene())
        {
            Director::getInstance()->replaceScene(TransitionFade::create(0.8f, scene));
        }
    };


    auto action = Sequence::create(
                                   CallFunc::create(func),
                                   DelayTime::create(0.7f),
                                   CallFunc::create([](){ CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("drum-japanese2.mp3"); }),
                                   DelayTime::create(2.3f),

                                   //タイトルに戻る
                                   CallFunc::create(end_func),
                                   nullptr);
    if (action)
    {
        this->runAction(action);
    }
}


//----------------------------------------------------
//ゲームの初期化
//----------------------------------------------------
void OchaLayer::initGame(){
    createHero();  //自機の生成
}

//----------------------------------------------------
//スプライトの生成
//----------------------------------------------------
void OchaLayer::createHero()
{
    yunomi1 = Hero::create(ImageType::yunomi1);
    yunomi1->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.45f));
    yunomi1->setScale(0.5f, 0.5f);
    this->addChild(yunomi1, 0);

    maccha = Hero::create(ImageType::maccha);
    maccha->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.35f));
    maccha->setColor(Color3B::GRAY);
    maccha->setScale(0.5f, 0.5f);
    this->addChild(maccha, 2);

    yunomi2 = Hero::create(ImageType::yunomi2);
    yunomi2->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.383f));
    yunomi2->setScale(0.5f, 0.5f);
    this->addChild(yunomi2, 3);
}

//----------------------------------------------------
//
//----------------------------------------------------
void OchaLayer::swingAnimation(bool isSwing)
{
    if (this->swingCnt >= SWING_COUNT)
    {
        return;
    }

    if(isSwing && isSwingStart){
        swingCnt++;
        moveHero();
    }
    isSwing = !isSwing;


    if (isSwing)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shakashaka.mp3");
    }
}

//----------------------------------------------------
//
//----------------------------------------------------
void OchaLayer::moveHero()
{
    if (hero->getActionByTag(999))
    {
        return;
    }

    const auto isEnd = (swingCnt >= SWING_COUNT);
    auto func = [this, isEnd]() {
        if (isEnd)
        {
            if (this->maccha)
            {
                auto action = TintTo::create(0.1f, 255, 255, 255);
                this->maccha->runAction(action);
            }

            this->step4();
        }
    };

    auto rotate = RotateBy::create(0.05f, 20.0f);
    auto seq = Sequence::create(rotate,
                                rotate->reverse(),
                                rotate->reverse(),
                                rotate,

                                CallFunc::create(func),
                                nullptr);
    if (seq)
    {
        if (this->maccha)
        {
            const auto color = this->maccha->getColor();
            CCLOG("color: r:%3d, g:%3d, b:%3d", color.r, color.g, color.b);

            auto action = TintTo::create(0.02f,
                                         MIN(color.r + 2, 255),
                                         MIN(color.g + 2, 255),
                                         MIN(color.b + 2, 255));
            this->maccha->runAction(action);
        }

        seq->setTag(999);

        hero->runAction(seq);
    }
}
