#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_
//////////////////////////////////////////////////////////////////////////
//通用数据类型的调用

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef int8
#define int8  char
#endif


#ifndef uint16
#define uint16	unsigned short
#endif

#ifndef int16
#define int16	short
#endif

#ifndef uint32
#define uint32	unsigned int
#endif

#ifndef int32
#define int32	int
#endif

#ifndef uint64
#define uint64 unsigned long long
#endif

#ifndef int64
#define int64  long long
#endif

#ifndef NULL
#define NULL 0
#endif

#endif