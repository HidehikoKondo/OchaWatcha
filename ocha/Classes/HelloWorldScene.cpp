#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "PrivateConfig.h"


USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program you may modify it.
    {
        auto func = [](Ref* pSender)
        {
            Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        };

        auto closeItem = MenuItemImage::create(
                                               "CloseNormal.png",
                                               "CloseSelected.png",
                                               func);

        closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                    origin.y + closeItem->getContentSize().height/2));

        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }

    /////////////////////////////
    // 3. add your codes below...
    if (auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24))
    {
        label->setName("label");

        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
    }

    if (auto sprite = Sprite::create("HelloWorld.png"))
    {
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        this->addChild(sprite, 0);
    }

    return true;
}


#pragma mark -
void HelloWorld::onEnter()
{
    Layer::onEnter();

    {
        auto callback = [this](EventCustom * event) {

            if (auto data = static_cast<Value *>(event->getUserData()))
            {
                if (auto label = dynamic_cast<Label *>(this->getChildByName("label")))
                {
                    label->setString(data->asString());
                }
            }
        };

        if (auto listener = EventListenerCustom::create(EVENT_NAME__TEXTFROMWATCH, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }
}

void HelloWorld::onExit()
{
    Layer::onExit();

    this->getEventDispatcher()->removeEventListenersForTarget(this);
}
