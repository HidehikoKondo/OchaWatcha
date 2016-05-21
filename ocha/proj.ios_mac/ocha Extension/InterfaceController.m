//
//  InterfaceController.m
//  ocha Extension
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#import "InterfaceController.h"

@interface InterfaceController()
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *messageLabel;

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
    
    NSDictionary *applicationDict = @{@"message" : @"SWING"};
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

// Interactive Message
// 受信
- (void)session:(nonnull WCSession *)session didReceiveMessage:(nonnull NSDictionary<NSString *,id> *)message replyHandler:(nonnull void (^)(NSDictionary<NSString *,id> * __nonnull))replyHandler
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"---");
        NSLog([message objectForKey:@"message"]);
        NSLog(@"---");
        NSLog([NSString stringWithFormat:@"----   app -> watch SUCCESS!!!!   ----%@", [message objectForKey:@"message"]]);
        
        [_messageLabel setText:[message objectForKey:@"message"]];
    });
    
    replyHandler(@{@"reply" : @"OK"});
}


@end



