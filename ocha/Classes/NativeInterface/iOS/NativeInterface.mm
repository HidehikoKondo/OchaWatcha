//
//  NativeInterface.mm
//  JankenPon
//
//  Created by OhsakaTakashi on 2015/01/11.
//
//

#include "NativeInterface.h"

#import "NativeInterface_iOS.h"

#import <GameKit/GameKit.h>

#include "cocos2d.h"


namespace cocos2dExt
{
    //Watchから文字を受け取る
    void NativeInterface::getTextFromWatch(std::string text)
    {
        //イベントでわたしてみる (必要なとこで受け取る)
        auto event = cocos2d::EventCustom("TextFromWatch");

        auto data = cocos2d::Value(text);
        event.setUserData(&data);

        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
};
