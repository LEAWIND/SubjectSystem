// [控制台API](https://docs.microsoft.com/zh-cn/windows/console/using-the-console)

#pragma once
#include <stdio.h>
#include <string.h>

/**
 * @brief 设置光标位置
 * @param x
 * @param y
 * @author LEAWIND
 */
void cui_setCursorPos(int x, int y);

/**
 * @brief 移动光标
 * @param x
 * @param y
 * @author LEAWIND
 */
void cui_moveCursor(int x, int y);

/**
 * @brief 设置文本格式
 * @param n 格式代码 参考https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences#text-formatting
 * @author LEAWIND
 */
void cui_setFontStyle(int n);

/**
 * @brief 获取用户输入字符串
 * @param s 将输入的字符串保存到此地址
 * @param maxLen 字符串最大长度
 * @param replaceChar 回显的替代字符，'\0' 表示输入的真实字符
 * @author LEAWIND
 */
void cui_inputs(char* s, int maxLen, char replaceChar);

// 隐藏光标
void cui_hideCursor();

// 显示光标
void cui_showCursor();

/**
 * @brief 将字符串打印到指定位置
 * @param x x 坐标
 * @param y y 坐标
 * @param c 字符串地址
 */
void cui_putStringAt(int x, int y, char* c);

/**
 * @brief 将字符串打印到指定位置，中心对齐
 * @param x 字符串的中心 x 坐标
 * @param y 字符串的中心 y 坐标
 * @param c 字符串地址
 * @param len 字符串长度，若为 0 则自动计算
 */
void cui_putStringCenterAt(int x, int y, char* c, int len);

/**
 * @brief 用指定字符填充矩形区域
 * @param x 左上角 x 坐标
 * @param y 左上角 y 坐标
 * @param w 矩形宽度
 * @param h 矩形高度
 * @param c 字符
 */
void cui_fillRect(int x, int y, int w, int h, char c);

// 清除矩形区域

/**
 * @brief 清空矩形区域
 * @param x 左上角 x 坐标
 * @param y 左上角 y 坐标
 * @param w 矩形宽度
 * @param h 矩形高度
 */
void cui_clearRect(int x, int y, int w, int h);

/**
 * @brief 绘制矩形边框
 * @param x 左上角 x 坐标
 * @param y 左上角 y 坐标
 * @param w 矩形宽度
 * @param h 矩形高度
 * @param c 如果为0则在边缘用 |,- 等字符，否则用字符 c
 */
void _strokeRect(int x, int y, int w, int h, char c);

#include "cui.c"