//
//  TitleLayer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "TitleLayer.hpp"

#include "PrivateConfig.h"

#include "OchaLayer.hpp"


USING_NS_CC;


#pragma mark -
TitleLayer::TitleLayer()
{
}
TitleLayer::~TitleLayer()
{
}


#pragma mark -
Scene * TitleLayer::createScene()
{
    auto scene = Scene::create();
    if (auto layer = TitleLayer::create())
    {
        scene->addChild(layer);
    }
    return scene;
}


#pragma mark -
bool TitleLayer::init()
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


        if (auto sprite = Sprite::create("title/background.png"))
        {
            const auto size = sprite->getContentSize();

            const auto rate = MAX(visibleRect.size.width  / size.width,
                                  visibleRect.size.height / size.height);
            sprite->setScale(rate);

            auto pos = Point::ZERO;
            pos = Point(visibleRect.getMidX(), visibleRect.getMidY());

            sprite->setPosition(pos);

            this->addChild(sprite);
        }


        if (auto sprite = Sprite::create("title/title.png"))
        {
            const auto size = sprite->getContentSize();

            const auto rate = visibleRect.size.width  / size.width;
            sprite->setScale(rate);


            auto pos = Point::ZERO;
            pos = Point(visibleRect.getMidX(), visibleRect.getMidY());

            sprite->setPosition(pos);

            this->addChild(sprite);
        }


        //メニュー (最前面になるように)
        auto callback = [this](Ref * pSender) {
            if (auto item = dynamic_cast<MenuItem *>(pSender))
            {
                item->setEnabled(false);
                if (auto scene = OchaLayer::createScene())
                {
                    Director::getInstance()->replaceScene(TransitionFade::create(0.8f, scene, Color3B::BLACK));
                }
            }
        };
        if (auto item = MenuItem::create(callback))
        {
            item->setContentSize(visibleRect.size);
            if (auto menu = Menu::createWithItem(item))
            {
                this->addChild(menu, 100);
            }
        }


        result = true;
    } while (0);

    return result;
}


#pragma mark -
void TitleLayer::onEnter()
{
    Layer::onEnter();
}

void TitleLayer::onExit()
{
    Layer::onExit();
}
