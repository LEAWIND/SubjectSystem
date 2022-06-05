#pragma once
#include "../dataControler.h"
#include "../datastruct.h"
#include "../page.h"
/**
 * @brief ��������Աģ��
 * @param db ���ݿ�
 */
int startAdminModule(Database* db);

/**
 * @brief �������ù���Ա������
 * @param user ����ɹ��Ĺ������˺ŵĵ�ַ
 * @author �»�
 */
void resetKey(Admin *user);

/**
 * @brief չʾ�γ̲��ṩ����γ̵�ѡ��
 * @param db ���ݿ�
 * @author �»�
 */
void manageCourse(Database* db);

/**
 * @brief չʾ�γ̲��ṩ����γ̵�ѡ��
 * @param db ���ݿ�
 * @param page ҳ��
 * @param һҳչʾ�����γ���
 * @author �»�
 */
void showCourses(Database *db, int page, int N);

/**
 * @brief ��arr���ҵ��ַ���str
 * @param arr ����������
 * @param str ��Ҫ���ҵ��ַ���
 * @return ���ҵ��������±���δ�ҵ�������-1
 * @author �»�
 */
int strFind(char *arr[], char *str, int len);
#include "admin.c"