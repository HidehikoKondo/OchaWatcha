//
//  InterfaceController.m
//  ocha Extension
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#import "InterfaceController.h"
#import <CoreMotion/CoreMotion.h>

@interface InterfaceController()
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *messageLabel;

//float xPos;

@end


@implementation InterfaceController{
    CMMotionManager *motionManager;
}

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

    //加速度センサー開始
    motionManager = [[CMMotionManager alloc] init];
    [motionManager startAccelerometerUpdates];
    [self setupAccelerometer];
    
    [super willActivate];
}


- (void)setupAccelerometer{
    if (motionManager.accelerometerAvailable){
        // センサーの更新間隔の指定、２Hz
        motionManager.accelerometerUpdateInterval = 0.2f;
        
        // ハンドラを設定
        CMAccelerometerHandler handler = ^(CMAccelerometerData *data, NSError *error)
        {
            // 加速度センサー
            double xac = data.acceleration.x;
            double yac = data.acceleration.y;
            double zac = data.acceleration.z;
            
            // 画面に表示
            NSLog([NSString stringWithFormat:@"x: %0.3f", xac]);
            //NSLog([NSString stringWithFormat:@"y: %0.3f", yac]);
            //NSLog([NSString stringWithFormat:@"z: %0.3f", zac]);
            
        };
        
        // 加速度の取得開始
        [motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:handler];
    }
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



