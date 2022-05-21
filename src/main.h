#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "admin_module/admin.h"
#include "cui.h"
#include "dataControler.h"
#include "datastruct.h"
#include "student_module/student.h"
#include "teacher_module/teacher.h"

#define DATA_DIR "./data"

// us: UI style settings
static const int us_width = 72;
static const int us_height = 32;

/**
 * @brief 首页：选择用户类别
 * @return char 用户类别
 */
char page_getUserType();

/**
 * @brief 登录页面：获取用户输入的账号和密码原文(参考page_getUserType)
 * @param account 账号值
 * @param passwd 密码原文
 * @author 
 */
void page_login(long long account, char* passwd);
