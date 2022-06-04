// [����̨API](https://docs.microsoft.com/zh-cn/windows/console/using-the-console)

#pragma once
#include <stdio.h>
#include <string.h>

/**
 * @brief ���ù��λ��
 * @param x
 * @param y
 * @author LEAWIND
 */
void cui_setCursorPos(int x, int y);

/**
 * @brief �ƶ����
 * @param x
 * @param y
 * @author LEAWIND
 */
void cui_moveCursor(int x, int y);

/**
 * @brief �����ı���ʽ
 * @param n ��ʽ���� �ο�https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences#text-formatting
 * @author LEAWIND
 */
void cui_setFontStyle(int n);

/**
 * @brief ��ȡ�û������ַ���
 * @param s ��������ַ������浽�˵�ַ
 * @param maxLen �ַ�����󳤶�
 * @param replaceChar ���Ե�����ַ���'\0' ��ʾ�������ʵ�ַ�
 * @author LEAWIND
 */
void cui_inputs(char* s, int maxLen, char replaceChar);

// ���ع��
void cui_hideCursor();

// ��ʾ���
void cui_showCursor();

/**
 * @brief ���ַ�����ӡ��ָ��λ��
 * @param x x ����
 * @param y y ����
 * @param c �ַ�����ַ
 */
void cui_putStringAt(int x, int y, char* c);

/**
 * @brief ���ַ�����ӡ��ָ��λ�ã����Ķ���
 * @param x �ַ��������� x ����
 * @param y �ַ��������� y ����
 * @param c �ַ�����ַ
 * @param len �ַ������ȣ���Ϊ 0 ���Զ�����
 */
void cui_putStringCenterAt(int x, int y, char* c, int len);

/**
 * @brief ��ָ���ַ�����������
 * @param x ���Ͻ� x ����
 * @param y ���Ͻ� y ����
 * @param w ���ο��
 * @param h ���θ߶�
 * @param c �ַ�
 */
void cui_fillRect(int x, int y, int w, int h, char c);

// �����������

/**
 * @brief ��վ�������
 * @param x ���Ͻ� x ����
 * @param y ���Ͻ� y ����
 * @param w ���ο��
 * @param h ���θ߶�
 */
void cui_clearRect(int x, int y, int w, int h);

/**
 * @brief ���ƾ��α߿�
 * @param x ���Ͻ� x ����
 * @param y ���Ͻ� y ����
 * @param w ���ο��
 * @param h ���θ߶�
 * @param c ���Ϊ0���ڱ�Ե�� |,- ���ַ����������ַ� c
 */
void _strokeRect(int x, int y, int w, int h, char c);

/**
 * @brief ���û����ı�
 * �ھ��������з����ı����Զ�����
 * �������ֲ���ʾ
 *
 * @param x ���Ͻ� x ����
 * @param y ���Ͻ� y ����
 * @param w ���ο��
 * @param h ���θ߶�
 * @param str �ַ���
 * @param len �ַ�������, 0��ʾ�Զ�
 */
void cui_putWrappedText(int x, int y, int w, int h, char* str, int len);
#include "cui.c"