#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "administrator.h"
#include "cui.h"
#include "dataControler.h"
#include "datastruct.h"
#include "student.h"
#include "teacher.h"

#define FPATH_STUDENT "data/student.dat"
#define FPATH_TEACHER "data/teacher.dat"
#define FPATH_ADMIN "data/admin.dat"
#define FPATH_COURSE "data/course.dat"
#define FPATH_COURSECLASS "data/courseClass.dat"

// us: UI style settings
static const int us_width = 72;
static const int us_height = 32;

static int studentCount = 1000, teacherCount = 100, adminCount = 100, ccCount = 1000, courseCount = 300;

static Student* students;
static Teacher* teachers;
static Admin* admins;
static CourseClass* courseClasses;
static Course* courses;

int loadEntireDatabaseIfDare();
static int isDBModified = 0;
int saveEntireDatabase();

// 首页：选择用户类别
char page_getUserType();

// TODO 登录页面：输入账号和密码原文
int page_login(char* account, char* passwd);