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
 * @brief 加载数据
 * @param dir 目录路径
 * @return Database 数据库结构体
 * @author LEAWIND
 */
Database loadEntireDatabaseIfDare(char* dir);

/**
 * @brief 保存数据
 * 
 * @param db 数据库
 * @param dir 目录路径
 * @author LEAWIND
 */
void saveEntireDatabase(Database db, char* dir);

/**
 * @brief 从文件读取结构体数组
 * @param elementSize 元素大小
 * @param p 保存到此地址
 * @param fpath 文件路径
 * @return int 读取到的长度
 * @author LEAWIND
 */
int dc_loadArray(int elementSize, void* p, char* fpath);

/**
 * @brief 将结构体数组以二进制形式保存到文件
 * @param elementSize 元素大小
 * @param p 结构体地址
 * @param plen 元素数量
 * @param fpath 文件路径
 * @author LEAWIND
 */
void dc_saveArray(int elementSize, void* p, int plen, char* fpath);

/**
 * @brief 导入原始数据
 * @param db	数据库地址
 * @param dirPath 原始数据目录
 * @author LEAWIND
 */
void dc_importRawData(Database* db, char* dirPath);

#include "dataControler.c"