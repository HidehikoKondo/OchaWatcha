//
//  Step2Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step2Layer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
Step2Layer::Step2Layer()
{
}
Step2Layer::~Step2Layer()
{
}


#pragma mark -
bool Step2Layer::init()
{
//    auto result = false;
//
//    do
//    {
//        if (! Layer::init())
//        {
//            break;
//        }
//
//        result = true;
//    } while (0);
//
//    return result;
    
    if(!Layer::init()){
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    winSize = Director::getInstance()->getWinSize();
    
    initGame();  //ゲームの初期化
    return true;
}

//----------------------------------------------------
//シーンの生成
//----------------------------------------------------
Scene* Step2Layer::createScene(){
    auto scene = Scene::create();
    auto layer = Step2Layer::create();
    scene->addChild(layer);
    return scene;
}

void Step2Layer::swingAnimation(bool isSwing)
{
    if(isSwing){
        swingCnt++;
        
    }
    isSwing = false;
    
}

//----------------------------------------------------
//ゲームの初期化
//----------------------------------------------------
void Step2Layer::initGame(){
//    returnCount = 0;
//    
//    auto sprite = Sprite::create(ImageFileName.at(ImageType::table));
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - winSize.height*0.1f));
//    sprite->setScale(0.9f, 0.7f);
//    this->addChild(sprite, 0);
//    
//    /*
//     //リトライメニュー(テスト用)
//     auto retryItem = MenuItemImage::create(ImageFileName.at(ImageType::retry), ImageFileName.at(ImageType::retry), CC_CALLBACK_1(GameScene::menuRetryCallback, this));
//     retryItem->setPosition(Vec2(origin.x + visibleSize.width - retryItem->getContentSize().width/2 ,
//     origin.y + retryItem->getContentSize().height/2));
//     auto menu = Menu::create(retryItem, NULL);
//     menu->setPosition(Vec2::ZERO);
//     this->addChild(menu, 1);
//     */
//    
//    //スコアラベル
//    score = StringUtils::format("Score : %i", returnCount);
//    scoreLabel = Label::createWithTTF(score, "fonts/Marker Felt.ttf", 24);
//    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
//                                 origin.y + visibleSize.height - scoreLabel->getContentSize().height));
//    this->addChild(scoreLabel, 1);
//    
//    //音声のプリロード
//    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioUtils::getFileName(SoundFileName.at(SoundType::racketEffect).c_str()).c_str());
//    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioUtils::getFileName(SoundFileName.at(SoundType::boundEffect).c_str()).c_str());
//    
    createHero();  //自機の生成
//    createEnemy();  //敵の生成
//    gameState = READY;
//    bulletMovePattern = SINGLE_PATTERN;
}

//----------------------------------------------------
//自機の生成
//----------------------------------------------------
void Step2Layer::createHero(){
    //    log("createHero");
    //    log("visibleSize.width:%f, height:%f",visibleSize.width,visibleSize.height);
    //    log("winSize.width:%f, height:%f",winSize.width,winSize.height);
    //    log("origin.x:%f, y:%f",origin.x,origin.y);
    hero = Hero::create(ImageType::Hero01);
    hero->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.2f));
    this->addChild(hero, 0);
}

//----------------------------------------------------
//
//----------------------------------------------------
void Step2Layer::moveReturnBullet()
{//(Bullet* bullet){
//    CallFunc *racketEffectSoundPlayCF = CallFunc::create([=](){
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName(SoundFileName.at(SoundType::racketEffect).c_str()).c_str());
//    });
//    CallFunc *boundEffectSoundPlayCF = CallFunc::create([=](){
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName(SoundFileName.at(SoundType::boundEffect).c_str()).c_str());
//    });
//    
//    bullet->setScale(1.2f, 1.2f);
//    float distanceX = enemyPos.x - hero->getPositionX();
//    float distanceY = enemyPos.y - (hero->getPositionY() + hero->getContentSize().height*0.5f + bullet->getContentSize().width);
//    
//    //    log("distanceY:%f",distanceY);
//    
//    auto jumpAct01 = JumpBy::create(0.6f, Vec2(distanceX*0.6f, distanceY*0.7f), 100, 1);
//    auto jumpAct02 = JumpBy::create(0.4f, Vec2(distanceX*0.4f, distanceY*0.3f), 70, 1);
//    auto scaleAct = ScaleTo::create(1.0f, 0.6f, 0.6f);
//    
//    auto seq = Sequence::create(racketEffectSoundPlayCF, jumpAct01, boundEffectSoundPlayCF, jumpAct02, nullptr);
//    auto spn = Spawn::create(seq, scaleAct, nullptr);
//    
//    bullet->runAction(spn);
}

//----------------------------------------------------
//
//----------------------------------------------------
#pragma mark -
void Step2Layer::onEnter()
{
    Layer::onEnter();
    
    {
        auto callback = [this](EventCustom * event) {
            if (auto data = static_cast<Value *>(event->getUserData()))
            {
                if(data->asString().compare("swing")){
                    this->swingAnimation(isSwing = true);
                }
            }
        };
        
        if (auto listener = EventListenerCustom::create(EVENT_NAME__TEXTFROMWATCH, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }
}

void Step2Layer::onExit()
{
    Layer::onExit();
    
    this->getEventDispatcher()->removeEventListenersForTarget(this);
}
//void Step2Layer::onEnter()
//{
//    Layer::onEnter();
//}
//
//void Step2Layer::onExit()
//{
//    Layer::onExit();
//}
