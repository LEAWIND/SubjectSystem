#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "datastruct.h"

typedef struct Database {
	static Student* students;
	static Teacher* teachers;
	static Admin* admins;
	static CourseClass* courseClasses;
	static Course* courses;
} Database;

// 从文件读取结构体数组
int dc_loadArray(int elementSize, void* p, char* fpath);

// 将结构体数组以二进制形式保存到文件
void dc_saveArray(int elementSize, void* p, int plen, char* fpath);
// 导入初始数据
void dc_importRawData(char* dirPath);

#include "dataControler.c"