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

/**
 * @brief 创建数据
 * @return Database Database 结构体
 */
Database dc_createDatabase();

/**
 * @brief 加载数据
 * @param dir 目录路径
 */
Database loadEntireDatabaseIfDare(char* dir);

/**
 * @brief 保存数据
 * 
 * @param db 数据库
 * @param dir 目录路径
 */
void saveEntireDatabase(Database db, char* dir);

// 从文件读取结构体数组
int dc_loadArray(int elementSize, void* p, char* fpath);

// 将结构体数组以二进制形式保存到文件
void dc_saveArray(int elementSize, void* p, int plen, char* fpath);

/**
 * @brief 导入原始数据
 * @param db	数据库地址
 * @param dirPath 原始数据目录
 */
void dc_importRawData(Database* db, char* dirPath);

#include "dataControler.c"