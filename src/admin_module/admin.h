#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"
/**
 * @brief 启动管理员模块
 * @param db 数据库
 */
int startAdminModule(Database* db);

/**
 * @brief 重新设置管理员的密码
 * @param user 登入成功的管理者账号的地址
 * @author 陈华
 */
void resetKey(Admin *user);

/**
 * @brief 展示课程并提供管理课程的选项
 * @param db 数据库
 * @author 陈华
 */
void manageCourse(Database* db);

/**
 * @brief 展示课程并提供管理课程的选项
 * @param db 数据库
 * @param page 页号
 * @param 一页展示的最大课程数
 * @author 陈华
 */
void showCourses(Database *db, int page, int N);
#include "admin.c"