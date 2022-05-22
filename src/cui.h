// [控制台API](https://docs.microsoft.com/zh-cn/windows/console/using-the-console)

#pragma once
#include <stdio.h>
#include <string.h>

void cui_printRect(int w, int h, char c);

// 设置光标位置
void cui_setCursorPos(int x, int y);
// 移动光标
void cui_moveCursor(int x, int y);

/**
 * @brief 设置文本格式
 * @param n 格式代码 参考https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences#text-formatting
 */
void cui_setFontStyle(int n);

/**
 * @brief 输入密文
 * @param s 将输入的密文保存到此地址
 * @param maxLen 密文最大长度
 * @param replaceChar 在屏幕上显示的替代字符，'\0' 表示默认 '*'
 */
void cui_inputSecret(char* s, int maxLen, char replaceChar);

// 隐藏光标
void cui_hideCursor();
// 显示光标
void cui_showCursor();

// 将字符串打印到指定位置
void cui_putStringAt(int x, int y, char* c);

// 将字符串打印到指定位置，中心对齐
void cui_putStringCenterAt(int x, int y, char* c, int len);

// 用字符填充矩形区域
void cui_fillRect(int x, int y, int w, int h, char c);

// 清除矩形区域
void cui_clearRect(int x, int y, int w, int h);

// 描边
void _strokeRect(int x, int y, int w, int h, char c);

#include "cui.c"