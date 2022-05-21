#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "datastruct.h"

// 将结构体数组以二进制形式保存到文件
void dc_saveArray(int elementSize, void* p, int plen, char* fpath);

// 从文件读取结构体数组
int dc_loadArray(int elementSize, void* p, char* fpath);
#include "dataControler.c"