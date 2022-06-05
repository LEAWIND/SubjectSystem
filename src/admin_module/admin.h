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

/**
 * @brief 在arr中找到字符串str
 * @param arr 被查找数组
 * @param str 需要查找的字符串
 * @param len 数组长度
 * @return 若找到，返回下表，若未找到，返回-1
 * @author 陈华
 */
int strFind(char *arr[], char *str, int len);

/**
 * @brief 二分寻找符合id的课程
 * @param course 课程库
 * @param id 寻找课程的id
 * @param l 起始
 * @param r 终点
 * @return 若找到，返回地址，若未找到，返回NULL
 * @author 陈华
 */
Course* findCourse(Course* courses, long long id, int l, int r);

/**
 * @brief 删除课程
 * @param db 数据库
 * @author 陈华
 */
void delCourse(Database * db);

/**
 * @brief 增加课程
 * @param db 数据库
 * @author 陈华
 */
void addCourse(Database *db);

/**
 * @brief 查找课程
 * @param db 数据库
 * @author 陈华
 */
void findCourseName(Database* db);

/**
 * @brief 修改课程
 * @param db 数据库
 * @author 陈华
 */
void changeCourse(Database *db);
#include "admin.c"