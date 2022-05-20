#pragma once

void cui_printRect(int w, int h, char c) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++)
			putchar(c);
		putchar('\n');
	}
}

// 设置光标位置
void cui_setCursorPos(int x, int y) {
	printf("\033[%d;%dH", y < 0 ? 1 : 1 + y, x < 0 ? 1 : 1 + x);
}

// 移动光标
void cui_moveCursor(int x, int y) {
	char buff_fmt[15];
	char buff[64];
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
		puts(buff);
}

// 隐藏光标
void cui_hideCursor() {
	puts("\033[?25l");
}

// 显示光标
void cui_showCursor() {
	puts("\033[?25h");
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

// 描边
void cui_strokeRect(int x, int y, int w, int h, char c) {
	printf("\033[%d;%dH", 1 + y, 1 + x);

	putchar('*' | c);  // LT

	for (int i = 2; i < w; i++)
		putchar('-' | c);

	putchar('*' | c);  // RT

	printf("\033[%d;%dH", 2 + y, 1 + x);
	for (int i = 2; i < h; i++)
		printf("%c\033[1B\033[1D", '|' | c);

	putchar('*' | c);  //LB

	for (int i = 2; i < w; i++)
		putchar('-' | c);

	putchar('*' | c);  //RB

	printf("\033[%d;%dH", 2 + y, x + w);
	for (int i = 2; i < h; i++)
		printf("%c\033[1B\033[1D", '|' | c);
}
