#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief ����ѧ��ģ��
 * @param db ���ݿ�
 */
int startStudentModule(Database db);

int stu_page_classSheet(Database* db, Student* stu);
int stu_page_chooseCourse(Database* db, Student* stu);
int stu_page_chooseCourseClasses(Database* db, Student* stu, Course* course);
int stu_page_courseClassPreview(Database* db, CourseClass* cc);

#include "student.c"