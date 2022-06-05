#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief 启动学生模块
 * @param db 数据库
 */
int startStudentModule(Database db);

int stu_page_classSheet(Database* db, Student* stu);
int stu_page_chooseCourse(Database* db, Student* stu);
int stu_page_chooseCourseClasses(Database* db, Student* stu, Course* course);
int stu_page_courseClassPreview(Database* db, CourseClass* cc);

#include "student.c"