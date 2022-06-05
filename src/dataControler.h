#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastruct.h"

typedef struct Database {
	int studentCount;
	int teacherCount;
	int adminCount;
	int ccCount;
	int courseCount;
	Student* students;
	Teacher* teachers;
	Admin* admins;
	CourseClass* courseClasses;
	Course* courses;
} Database;

/**
 * @brief 32 �ֽڹ�ϣ����
 * �������ݿ�����
 * @param src Դ���ݵ�ַ
 * @param len Դ���ݳ���
 * @param dst ��ϣֵ��ŵ�ַ
 */
void dc_hash32(const void* src, int len, void* dst);

/**
 * @brief ��������
 * @param dir Ŀ¼·��
 * @return Database ���ݿ�ṹ��
 * @author LEAWIND
 */
Database dc_loadEntireDatabaseIfDare(char* dir);

/**
 * @brief ��������
 *
 * @param db ���ݿ�
 * @param dir Ŀ¼·��
 * @author LEAWIND
 */
void dc_saveEntireDatabase(Database db, char* dir);

/**
 * @brief ���ļ���ȡ�ṹ������
 * @param elementSize Ԫ�ش�С
 * @param p ���浽�˵�ַ
 * @param fpath �ļ�·��
 * @return int ��ȡ���ĳ���
 * @author LEAWIND
 */
int dc_loadArray(int elementSize, void* p, char* fpath);

/**
 * @brief ���ṹ�������Զ�������ʽ���浽�ļ�
 * @param elementSize Ԫ�ش�С
 * @param p �ṹ���ַ
 * @param plen Ԫ������
 * @param fpath �ļ�·��
 * @author LEAWIND
 */
void dc_saveArray(int elementSize, void* p, int plen, char* fpath);

/**
 * @brief ����ԭʼ����
 * @param db	���ݿ��ַ
 * @param dirPath ԭʼ����Ŀ¼
 * @author LEAWIND
 */
void dc_importRawData(Database* db, char* dirPath);

/**
 * @brief ������Ա�˺������Ƿ���ȷ
 * @param db Database �ṹ��
 * @param account �˺�
 * @param passwd ����ԭ��
 * @parsm user ���ڵ���Ĺ���Ա
 * @return 1:ƥ��ɹ�|0:�˺Ż��������
 */
int dc_checkAdminLogin(Database db, long long account, char* passwd, Admin ** user);

/**
 * @brief ���ѧ���˺������Ƿ���ȷ�������ȷ�򷵻�ѧ���ṹ���ַ
 * @param db Database �ṹ��
 * @param account �˺�
 * @param passwd ����ԭ��
 * @return ��ַ:ƥ��ɹ�|NULL:�˺Ż��������
 */
Student* dc_checkStudentLogin(Database db, long long account, char* passwd);

/**
 * @brief ����ʦ�˺������Ƿ���ȷ
 * @param db Database �ṹ��
 * @param account �˺�
 * @param passwd ����ԭ��
 * @param user ����ɹ����˻�
 * @return 1:ƥ��ɹ�|0:�˺Ż��������
 * @author �»�
 */
int dc_checkTeacherLogin(Database db, long long account, char* passwd, Teacher** user);

#include "dataControler.c"