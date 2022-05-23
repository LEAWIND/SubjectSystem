#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief 启动学生模块
 * @param db 数据库
 */
int startStudentModule(Database db);

#include "student.c"