#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief ����ѧ��ģ��
 * @param db ���ݿ�
 */
int startStudentModule(Database db);

/**
 * @brief ����ѧ���Ŀγ̱�
 * @param db ���ݿ�
 * @param stu ѧ��
 */
int stu_page_classSheet(Database* db, Student* stu);

/**
 * @brief ѧ��ѡ��γ�
 * @param db ���ݿ�
 * @param stu ѧ��
 */
int stu_page_chooseCourse(Database* db, Student* stu);

/**
 * @brief ѡ��γ̰༶
 * @param db ���ݿ�
 * @param stu ѧ��
 * @param course �γ�
 */
int stu_page_chooseCourseClasses(Database* db, Student* stu, Course* course);

/**
 * @brief �γ̰༶��ϢԤ��
 * @param db ���ݿ�
 * @param cc �γ̰༶
 */
int stu_page_courseClassPreview(Database* db, CourseClass* cc);

/**
 * @brief �޸�ѧ������
 * @param db ���ݿ�
 * @param stu ѧ��
 */
int stu_page_changePassword(Database* db, Student* stu);

#include "student.c"