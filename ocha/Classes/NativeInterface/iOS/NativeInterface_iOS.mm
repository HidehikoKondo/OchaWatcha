//
//  NativeInterface_iOS.mm
//  JankenPon
//
//  Created by OhsakaTakashi on 2015/01/11.
//
//

#include "NativeInterface_iOS.h"
#include "NativeInterface.h"

#import "AppController.h"


@interface NativeInterface_iOS()
@end


@implementation NativeInterface_iOS

//Watchから文字を受け取る
+ (void) getTextFromWatch:(NSString *) text
{
    cocos2dExt::NativeInterface::getTextFromWatch([text UTF8String]);
}

//Watchへ文字を送る
+ (void) putTextToWatch:(std::string) text
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    if (appController)
    {
        //TODO:
        //[appController sendMessageForWatch:[NSString stringWithUTF8String:text]];
    }
}


@end
