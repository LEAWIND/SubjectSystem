#pragma once
// [控制台虚拟终端序列](https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences)

/**
 * @brief 设置文本格式，n 的值参考[https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences#text-formatting]
 * @param n
 */
void cui_setFontStyle(int n) {
	printf("\033[%dm", n);
};

// 获取用户输入字符串
void cui_inputs(char* s, int maxLen, char replaceChar) {
	int len = 0;
	char c, doLoop = 1;
	int flag;
	while (doLoop) {
		c = getch();  // 无缓冲输入
		switch (c) {
			case '\r':	// 回车 \r\n 代表输入结束
				if (len)
					doLoop = 0;
				break;
			case '\b':	// 退格
				if (len) {
					s[--len] = '\0';
					printf("\033[1D \033[1D");
				}
				break;
			default:
				if (len < maxLen) {
					s[len++] = c;
					putchar(replaceChar ? replaceChar : c);
				}
		}
	}
	s[len++] = 0;
}

// 设置光标位置
void cui_setCursorPos(int x, int y) {
	printf("\033[%d;%dH", y < 0 ? 1 : 1 + y, x < 0 ? 1 : 1 + x);
}

// 移动光标
void cui_moveCursor(int x, int y) {
	char buff_fmt[15];	// 格式缓存
	char buff[64];		// 控制字符缓存
	char* pbuff = buff;
	if (y) {
		strcpy(buff_fmt, y > 0 ? "\033[%dB" : "\033[%dA");
		pbuff += sprintf(pbuff, buff_fmt, y > 0 ? y : -y);
	}
	if (x) {
		strcpy(buff_fmt, x > 0 ? "\033[%dC" : "\033[%dD");
		pbuff += sprintf(pbuff, buff_fmt, x > 0 ? x : -x);
	}
	if (x | y)
		printf(buff);
}

// 隐藏光标
void cui_hideCursor() {
	printf("\033[?25l");
}

// 显示光标
void cui_showCursor() {
	printf("\033[?25h");
}

// 将字符串打印到指定位置
void cui_putStringAt(int x, int y, char* c) {
	printf("\033[%d;%dH%s", 1 + y, 1 + x, c);
}

// 将字符串打印到指定位置，中心对齐
void cui_putStringCenterAt(int x, int y, char* c, int len) {
	if (!len)
		len = strlen(c);
	x -= len / 2;
	if (x < 0) {
		c -= x;
		x = 0;
	}
	printf("\033[%d;%dH%s", 1 + y, 1 + x, c);
}

// 用字符填充矩形区域
void cui_fillRect(int x, int y, int w, int h, char c) {
	for (int i = 0; i < h; i++) {
		printf("\033[%d;%dH", 1 + y + i, 1 + x);
		for (int j = 0; j < w; j++)
			putchar(c);
	}
}

// 清除矩形区域
void cui_clearRect(int x, int y, int w, int h) {
	for (int i = 0; i < h; i++)
		printf("\033[%d;%dH\033[%dX", 1 + y + i, 1 + x, w);
}

// 绘制矩形边框
void cui_strokeRect(int x, int y, int w, int h, char c) {
	// 移动光标
	printf("\033[%d;%dH", 1 + y, 1 + x);
	// 左上
	putchar('*' | c);
	// 上
	for (int i = 2; i < w; i++)
		putchar('-' | c);
	// 右上
	putchar('*' | c);
	// 移动光标
	printf("\033[%d;%dH", 2 + y, 1 + x);
	// 左
	for (int i = 2; i < h; i++)
		printf("%c\033[1B\033[1D", '|' | c);
	// 左下
	putchar('*' | c);
	// 下
	for (int i = 2; i < w; i++)
		putchar('-' | c);
	// 右下
	putchar('*' | c);
	// 移动光标
	printf("\033[%d;%dH", 2 + y, x + w);
	// 右
	for (int i = 2; i < h; i++)
		printf("%c\033[1B\033[1D", '|' | c);
}
