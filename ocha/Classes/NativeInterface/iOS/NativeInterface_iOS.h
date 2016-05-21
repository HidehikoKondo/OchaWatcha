//
//  NativeInterface_iOS.h
//  JankenPon
//
//  Created by OhsakaTakashi on 2015/01/11.
//
//

#import <Foundation/Foundation.h>


@interface NativeInterface_iOS

//Watchから文字を受け取る
+ (void) getTextFromWatch:(NSString *) text;

//Watchへ文字を送る
+ (void) putTextToWatch:(std::string) text;

@end
