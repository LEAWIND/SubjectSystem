#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "cui.h"
#include "datastruct.h"
// us: UI style settings
const int us_width = 72;
const int us_height = 32;

/**
 * @brief ��ҳ��ѡ���û����
 * @return char �û����
 * @author LEAWIND
 */
char page_getUserType();

/**
 * @brief ��¼ҳ�棺��ȡ�û�������˺ź�����ԭ��
 * @param account �˺ű��������ַ
 * @param passwd ����ԭ�ı����ַ
 * @param info ��ʾ��Ϣ
 * @author LEAWIND
 */
void page_login(long long* account, char* passwd, char* info);

#include "page.c"
