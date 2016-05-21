//
//  InterfaceController.m
//  ocha Extension
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#import "InterfaceController.h"

@interface InterfaceController()

@end


@implementation InterfaceController

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];

    // Configure interface objects here.
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}

-(IBAction)submitNotification:(id)sender{
    NSLog(@"通知送る");
    
    
    // NSDictionary生成　Key:"counterValue" Value（値）:counterString(counterカウント)
    NSDictionary *applicationData = @{@"FromWatchApp":@"CAMERABOOT"};
    
//    // 一つ目の引数に渡したいデータを入れればOK
//    [WKInterfaceController openParentApplication:applicationData reply:^(NSDictionary *replyInfo, NSError *error) {
//        NSLog(@"%@",[replyInfo objectForKey:@"FromParentApp"]);
//        
//        //親Appからの返信
//        if([(NSString*)[replyInfo objectForKey:@"FromParentApp"]isEqualToString:@"CAMERAOPENED"]){
//            //音声入力画面の起動
//            //[self callMorphingCode];
//        }
//        //        else if([(NSString*)[replyInfo objectForKey:@"FromParentApp"]isEqualToString:@"CAMERACLOSED"]){
//        //
//        //        }
//    }];
    

    // 送信側
    NSDictionary *applicationDict = @{@"hoge" : @"huga"};
    [[WCSession defaultSession] updateApplicationContext:applicationDict error:nil];
    
}

@end



