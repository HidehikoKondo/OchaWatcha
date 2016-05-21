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

    if ([WCSession isSupported]) {
        WCSession *session = [WCSession defaultSession];
        session.delegate = self;
        [session activateSession];
    }
    
    
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
    
    NSDictionary *applicationDict = @{@"hoge" : @"huga"};
    [[WCSession defaultSession] updateApplicationContext:applicationDict error:nil];
    
    
    if ([[WCSession defaultSession] isReachable]) {
        [[WCSession defaultSession] sendMessage:applicationDict
                                   replyHandler:^(NSDictionary *replyHandler) {
                                       // do something
                                       NSLog(@"送った");
                                   }
                                   errorHandler:^(NSError *error) {
                                       // do something
                                       NSLog(@"送れなかった・・・orz");
                                   }
         ];
    }else{
        NSLog(@"つながってないよ");
    }
    
    
    
    
}

@end



