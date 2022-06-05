#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief 启动学生模块
 * @param db 数据库
 */
int startStudentModule(Database db);

/**
 * @brief 绘制学生的课程表
 * @param db 数据库
 * @param stu 学生
 */
int stu_page_classSheet(Database* db, Student* stu);

/**
 * @brief 学生选择课程
 * @param db 数据库
 * @param stu 学生
 */
int stu_page_chooseCourse(Database* db, Student* stu);

/**
 * @brief 选择课程班级
 * @param db 数据库
 * @param stu 学生
 * @param course 课程
 */
int stu_page_chooseCourseClasses(Database* db, Student* stu, Course* course);

/**
 * @brief 课程班级信息预览
 * @param db 数据库
 * @param cc 课程班级
 */
int stu_page_courseClassPreview(Database* db, CourseClass* cc);

/**
 * @brief 修改学生密码
 * @param db 数据库
 * @param stu 学生
 */
int stu_page_changePassword(Database* db, Student* stu);

#include "student.c"