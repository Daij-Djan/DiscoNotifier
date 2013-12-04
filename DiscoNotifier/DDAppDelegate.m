//
//  DDAppDelegate.m
//  DiscoNotifier
//
//  Created by Dominik Pich on 28/11/13.
//  Copyright (c) 2013 Dominik Pich. All rights reserved.
//

#import "DDAppDelegate.h"
#import "DDUserNotificationCenterMonitor.h"
#import "DDLMUService.h"
#import "DDOpenAtLoginController.h"

@implementation DDAppDelegate {
    DDUserNotificationCenterMonitor *_ncMonitor;
    DDLMUService *_lmuService;
    NSStatusItem *_statusItem;
    DDOpenAtLoginController *_openAtLoginController;
    BOOL _isFading;
}

- (void)flashKeyboard {
    if(!_isFading) {
        _isFading = YES;

        //get
        CGFloat before = _lmuService.keyboardLightPercentageValue;
        __weak DDAppDelegate *weakSelf = self;
        
        //fade & fade back and set _isFading=NO
        [_lmuService fadeKeyboardLightTo:100-before
                                duration:2000
                       completionHandler:^(NSInteger percentage) {
                           
            [_lmuService fadeKeyboardLightTo:before
                                    duration:2000
                           completionHandler:^(NSInteger percentage) {
                               DDAppDelegate *sself = weakSelf;
                               if(sself) {
                                   sself->_isFading = NO;
                               }
                               sself = nil;
                           }];
                       }];
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"numberOfPresentedNotifications"]) {
        [self flashKeyboard];
    }
}

- (IBAction)toggleRunOnLogin:(id)sender {
    _openAtLoginController.appStartsAtLogin = @(!_openAtLoginController.appStartsAtLogin.boolValue);
    
    NSMenuItem *item = [_statusItem.menu itemWithTag:555];
    [item setState:_openAtLoginController.appStartsAtLogin.boolValue ? NSOnState : NSOffState];
}

- (IBAction)sendTest:(id)sender {
    //test
    NSUserNotification *n = [[NSUserNotification alloc] init];
    n.title = @"test";
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:n];
}

- (IBAction)quitApp:(id)sender {
    [NSApp terminate:sender];
}

#pragma mark NSApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    //load LMU
    if(![DDLMUService isAvailable]) {
        NSRunAlertPanel(@"Error", @"DiscoNotifier cant find the keyboard backlight controller.\n\nWill Quit", @"OK", nil, nil);
        [NSApp terminate:nil];
    }
    DDLMUService *lmu = [[DDLMUService alloc] init];
    
    //load NCMonitor
    DDUserNotificationCenterMonitor *watcher = [[DDUserNotificationCenterMonitor alloc] init];
    NSError *error;
    if(![watcher start:&error]) {
        NSRunAlertPanel(@"Error", [NSString stringWithFormat:@"DiscoNotifier cant monitor notification center: %@.\n\nWill Quit", error.localizedDescription], @"OK", nil, nil);
        [NSApp terminate:nil];
    }
    [watcher addObserver:self forKeyPath:@"numberOfPresentedNotifications" options:0 context:nil];
    
    //save pointers
    _lmuService = lmu;
    _ncMonitor = watcher;

    //_openAtLoginController.appStartsAtLogin
    _openAtLoginController = [[DDOpenAtLoginController alloc] init];
    
    //status item
    _statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
    _statusItem.title = @"DiscoNotifier";

    //prepare menu for item
    NSMenu *menu = [[NSMenu alloc] init];
    
    //1
    NSMenuItem *item = [[NSMenuItem alloc] initWithTitle:@"Run On Login"
                                                  action:@selector(toggleRunOnLogin:)
                                           keyEquivalent:@""];
    item.target = self;
    item.tag = 555;
    [item setState:_openAtLoginController.appStartsAtLogin.boolValue ? NSOnState : NSOffState];
    [menu addItem:item];

    //2
    item = [NSMenuItem separatorItem];
    [menu addItem:item];
    
    //3
    item = [[NSMenuItem alloc] initWithTitle:@"Send Test Notification"
                                      action:@selector(sendTest:)
                               keyEquivalent:@""];
    item.target = self;
    [menu addItem:item];
    
    //4
    item = [[NSMenuItem alloc] initWithTitle:@"Quit"
                                      action:@selector(quitApp:)
                               keyEquivalent:@""];
    item.target = self;
    [menu addItem:item];
    
    _statusItem.menu = menu;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    [_ncMonitor removeObserver:self forKeyPath:@"numberOfPresentedNotifications"];
    [_ncMonitor stop];
    
    [[NSStatusBar systemStatusBar] removeStatusItem:_statusItem];
}

@end
