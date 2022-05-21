#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "datastruct.h"

typedef struct Database {
	int studentCount;
	int teacherCount;
	int adminCount;
	int ccCount;
	int courseCount;
	Student* students;
	Teacher* teachers;
	Admin* admins;
	CourseClass* courseClasses;
	Course* courses;
} Database;

void loadEntireDatabaseIfDare(Database* db, char* dir);
void saveEntireDatabase(Database db, char* dir);

// 从文件读取结构体数组
int dc_loadArray(int elementSize, void* p, char* fpath);

// 将结构体数组以二进制形式保存到文件
void dc_saveArray(int elementSize, void* p, int plen, char* fpath);
// 导入原始数据
void dc_importRawData(char* dirPath);

#include "dataControler.c"