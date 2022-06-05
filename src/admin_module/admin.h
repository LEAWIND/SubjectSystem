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
 * @param len ���鳤��
 * @return ���ҵ��������±���δ�ҵ�������-1
 * @author �»�
 */
int strFind(char *arr[], char *str, int len);

/**
 * @brief ����Ѱ�ҷ���id�Ŀγ�
 * @param course �γ̿�
 * @param id Ѱ�ҿγ̵�id
 * @param l ��ʼ
 * @param r �յ�
 * @return ���ҵ������ص�ַ����δ�ҵ�������NULL
 * @author �»�
 */
Course* findCourse(Course* courses, long long id, int l, int r);

/**
 * @brief ɾ���γ�
 * @param db ���ݿ�
 * @author �»�
 */
void delCourse(Database * db);

/**
 * @brief ���ӿγ�
 * @param db ���ݿ�
 * @author �»�
 */
void addCourse(Database *db);

/**
 * @brief ���ҿγ�
 * @param db ���ݿ�
 * @author �»�
 */
void findCourseName(Database* db);

/**
 * @brief �޸Ŀγ�
 * @param db ���ݿ�
 * @author �»�
 */
void changeCourse(Database *db);
#include "admin.c"