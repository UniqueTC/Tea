//
//  TeaSecurity.h
//  TeaSecurity
//
//  Created by TC on 15/11/11.
//  Copyright © 2015年 TC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "tea.h"
@interface TeaSecurity : NSObject


//加密数据
+(int)stringNeedEncrypt:(NSString *)sendString charArray:( char *)encryString;

//解密数据
+(NSString *)stringNeedUnEncrypt:(char*)destSource anlen:(int)len;

@end
