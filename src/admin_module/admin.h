#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"
/**
 * @brief 启动管理员模块
 * @param db 数据库
 */
int startAdminModule(Database db);
#include "admin.c"