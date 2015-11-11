//
//  ViewController.m
//  TeaSecurity
//
//  Created by TC on 15/11/11.
//  Copyright © 2015年 TC. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
{
    BOOL remPass;//记住密码
    NSString *nameStr;
    NSString *passStr;
    
    NSDictionary *dic;
    NSString *path;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    path = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/login.plist"];
    dic = [NSDictionary dictionaryWithContentsOfFile:path];
    if (!dic) {
        
        NSLog(@"没有登陆过");
        remPass = YES;
        self.remBtn.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"log_rem_no.png"]];
    }else
    {
        remPass = [[dic objectForKey:@"remPass"] boolValue];
        
        if (remPass) {
            self.remBtn.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"log_rem_no.png"]];
            
            NSArray *personAry= [dic objectForKey:@"ary"];
            self.nameTF.text = personAry[0];
            if (personAry.count == 1) {
                
            }else
            {
                NSString *securityStr = personAry[1];
                NSData *passData = [GTMBase64 decodeString:securityStr];
                char *neicun[1024*20] = {0};
                memcpy(neicun, [passData bytes], passData.length);
                int length = strlen(neicun);
                NSString *passStr = [TeaSecurity stringNeedUnEncrypt:neicun anlen:length];
                NSString *oldPass = [passStr substringFromIndex:8];
                self.passTF.text = oldPass;
            }
            //解密
        }else
        {
            self.remBtn.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"log_rem_yes.png"]];
        }
        
    }
   
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}

- (IBAction)btnAction:(id)sender {
    
    nameStr = self.nameTF.text;
    passStr = self.passTF.text;
    
    //避免长度不到8
    NSString *newPass = [NSString stringWithFormat:@"12345678%@",passStr];
    //加密
    char *pstr =(char *)malloc(1024*20);//分配20K的内存
    if (pstr == NULL) {
        return;
    }
    memset(pstr, 0, 1024*20);
    int leng = [TeaSecurity stringNeedEncrypt:newPass charArray:pstr];
    //转码
    NSString *gtmStr = [GTMBase64 stringByEncodingBytes:pstr length:leng];
    
    NSArray *userAndPassAry = [NSArray array];
    if (remPass) {
        //密码保存有值
        userAndPassAry = @[nameStr,gtmStr];
    }else
    {
        //密码保存空
        userAndPassAry = @[nameStr];
        
    }
    
    NSMutableDictionary *userAndPassDci = [[NSMutableDictionary alloc]initWithDictionary:dic];
    if (remPass) {
        [userAndPassDci setObject:@"YES" forKey:@"remPass"];
    }else
    {
        [userAndPassDci setObject:@"NO" forKey:@"remPass"];
    }
    [userAndPassDci setObject:userAndPassAry forKey:@"ary"];
    [userAndPassDci writeToFile:path atomically:YES];
    
    SuccessVC *sucVC = [[SuccessVC alloc] init];
    [self.navigationController pushViewController:sucVC animated:YES];
    
}

- (IBAction)remPassAction:(id)sender {
    
    if (remPass) {
        remPass = NO;
        self.remBtn.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"log_rem_yes.png"]];
    }else
    {
        remPass = YES;
        self.remBtn.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"log_rem_no.png"]];
    }
}
@end
