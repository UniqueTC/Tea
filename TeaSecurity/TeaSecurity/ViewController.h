//
//  ViewController.h
//  TeaSecurity
//
//  Created by TC on 15/11/11.
//  Copyright © 2015年 TC. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TeaSecurity.h"
#import "GTMBase64.h"
#import "SuccessVC.h"
@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextField *nameTF;

@property (weak, nonatomic) IBOutlet UITextField *passTF;

@property (weak, nonatomic) IBOutlet UIButton *remBtn;

- (IBAction)btnAction:(id)sender;

- (IBAction)remPassAction:(id)sender;

@end

