#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief 启动教师模块
 * @param db 数据库
 * @author 陈华
 */
int startTeacherModule(Database db);

/**
 * @brief 启动选项页面
 * @param db 数据库
 * @param user 当前登入的用户
 * @author 陈华
 */
void startSection(Database db, Teacher* user);

/**
 * @brief 展示选项
 * @param name 登入的用户的名字
 * @author 陈华
 * @return 返回用户的选项
 */

int showMenuTeacher(char *name);

#include "teacher.c"