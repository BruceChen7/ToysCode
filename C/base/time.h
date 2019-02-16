//=====================================================================
//
// time.h - 时间相关的函数
//
// Created by brookchen on 2019/02/16
// Last Modified: 2019/02/16 03:04:50
//
//=====================================================================

#ifndef __BASE_TIME_H__
#define __BASE_TIME_H__
#include <stdio.h>

// 返回当前的毫秒数
long long timeInMilliseconds();


#define startBenchMark() start = timeInMilliseconds()
#define endBenchMark(msg) do  {  \
    elapsed = timeInMilliseconds() - start ;  \
    printf("%s, %lld items cost %lld ms\n", msg, count, elapsed); \
} while(0)
#endif
