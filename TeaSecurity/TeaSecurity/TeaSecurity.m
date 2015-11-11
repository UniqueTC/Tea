//
//  TeaSecurity.m
//  TeaSecurity
//
//  Created by TC on 15/11/11.
//  Copyright © 2015年 TC. All rights reserved.
//

#import "TeaSecurity.h"

@implementation TeaSecurity

//加密
+(int)stringNeedEncrypt:(NSString *)sendString charArray:(char *)encryString{
    
    char *needEncrypt = (char *)[sendString UTF8String];
    sprintf(encryString,"%s",needEncrypt);
    
    //加密的key需要读取
    char KEY[16]={0x3A,0xDA,0x75,0x21,0xDB,0xE2,0xDB,0xB3,0x11,0xB4,0x49,0x01,0xA5,0xC6,0xEA,0xD4};
    int  length=strlen(encryString);
    
    tea_encrypt_fun(encryString, length, KEY);
    
    
    
    return length;
    
}


+(NSString *)stringNeedUnEncrypt:(char*)destSource anlen:(int)len{
    
    char KEY[16]={0x3A,0xDA,0x75,0x21,0xDB,0xE2,0xDB,0xB3,0x11,0xB4,0x49,0x01,0xA5,0xC6,0xEA,0xD4};
    
    tea_decrypt_fun(destSource, len, KEY);
    
    NSString *result = [[NSString alloc]initWithCString:destSource encoding:NSUTF8StringEncoding];
    return result;
}



@end
