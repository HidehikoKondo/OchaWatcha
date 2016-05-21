//
//  NativeInterface_iOS.mm
//  JankenPon
//
//  Created by OhsakaTakashi on 2015/01/11.
//
//

#include "NativeInterface_iOS.h"
#include "NativeInterface.h"


@interface NativeInterface_iOS()
@end


@implementation NativeInterface_iOS

//Watchから文字を受け取る
+ (void) getTextFromWatch:(NSString *) text
{
    cocos2dExt::NativeInterface::getTextFromWatch([text UTF8String]);
}

@end
