#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "cui.h"
#include "datastruct.h"
// us: UI style settings
const int us_width = 72;
const int us_height = 32;

/**
 * @brief 首页：选择用户类别
 * @return char 用户类别
 * @author LEAWIND
 */
char page_getUserType();

/**
 * @brief 登录页面：获取用户输入的账号和密码原文(参考page_getUserType)
 * @param account 账号变量保存地址
 * @param passwd 密码原文保存地址
 * @author LEAWIND
 */
void page_login(long long* account, char* passwd);

#include "page.c"