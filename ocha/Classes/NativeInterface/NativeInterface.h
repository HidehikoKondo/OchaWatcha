//
//  NativeInterface.h
//  JankenPon
//
//  Created by OhsakaTakashi on 2015/01/11.
//
//

#ifndef __JankenPon__NativeInterface__
#define __JankenPon__NativeInterface__

#include "cocos2d.h"


namespace cocos2dExt
{
    class NativeInterface
    {
    public:
//    protected:
//        NativeInterface() {};
//        virtual ~NativeInterface() {};

        //Watchから文字を受け取る
        static void getTextFromWatch(std::string text);

        //Watchへ文字を送る
        static void putTextToWatch(int number) {
            NativeInterface::putTextToWatch(cocos2d::StringUtils::toString(number));
        }
        static void putTextToWatch(std::string text);

        //コンパス
        static cocos2d::Point getCompass();
    };
};
#endif
