#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"

/**
 * @brief ������ʦģ��
 * @param db ���ݿ�
 * @author �»�
 */
int startTeacherModule(Database db);

/**
 * @brief ����ѡ��ҳ��
 * @param db ���ݿ�
 * @param user ��ǰ������û�
 * @author �»�
 */
void startSection(Database db, Teacher* user);

/**
 * @brief չʾѡ��
 * @param name ������û�������
 * @author �»�
 * @return �����û���ѡ��
 */

int showMenuTeacher(char *name);

/**
 * @brief ����༶��Ϣ
 * @param db ���ݿ�
 * @param user ��ǰ������û�
 * @author �»�
 */
void manageClass(Database db, Teacher* user);

/**
 * @brief �޸ĸ�����Ϣ
 * @param db ���ݿ�
 * @param user ��ǰ������û�
 * @author �»�
 */
void resetInfo(Database db, Teacher* user);

#include "teacher.c"