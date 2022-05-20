#pragma once

void cui_printRect(int w, int h, char c) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++)
			putchar(c);
		putchar('\n');
	}
}

void cui_setCursorPos(int x, int y) {
	x = x < 0 ? 0 : x;
	y = y < 0 ? 0 : y;
	printf("\033[%d;%dH", 1 + y, 1 + x);
}

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
		printf(buff);
}

void cui_hideCursor() {
	printf("\033[?25l");
}

void cui_showCursor() {
	printf("\033[?25h");
}

void cui_putStringAt(int x, int y, char* c) {
	printf("\033[%d;%dH%s", 1 + y, 1 + x, c);
}

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

void cui_fillRect(int x, int y, int w, int h, char c) {
	for (int i = 0; i < h; i++) {
		printf("\033[%d;%dH", 1 + y + i, 1 + x);
		for (int j = 0; j < w; j++)
			putchar(c);
	}
}

void cui_clearRect(int x, int y, int w, int h) {
	for (int i = 0; i < h; i++)
		printf("\033[%d;%dH\033[%dX", 1 + y + i, 1 + x, w);
}

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
