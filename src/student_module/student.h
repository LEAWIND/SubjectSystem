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
int stu_page_chooseClasses(Database* db, Student* stu);

#include "student.c"