#pragma once
#include <stdio.h>

#include "datastruct.h"

// 将结构体数组以二进制形式保存到文件
#define saveArray(TP, p, plen, fpath)    \
	{                                    \
		FILE* fp = fopen(fpath, "wb");   \
		int s = plen;                    \
		fwrite(&s, sizeof(int), 1, fp);  \
		fwrite(p, sizeof(TP), plen, fp); \
		fclose(fp);                      \
	}

// 从文件读取结构体数组
#define loadArray(TP, p, fpath)          \
	{                                    \
		FILE* fp = fopen(fpath, "rb");   \
		int len;                         \
		fread(&len, sizeof(int), 1, fp); \
		fread(p, sizeof(TP), len, fp);   \
		fclose(fp);                      \
	}

#include "dataControler.c"