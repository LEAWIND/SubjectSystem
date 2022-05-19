#pragma once

void cui_printRect(int w, int h, char c) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++)
			putchar(c);
		putchar('\n');
	}
}

void cui_setCursorPos(int x, int y) {
	printf("\033[%d;%dH", 1 + y, 1 + x);
}

void cui_moveCursor(int x, int y) {
	char buff_fmt[25];
	char buff[64];
	if (y) {
		if (y > 0)
			strcat(buff_fmt, "\033[%dA");
		else
			strcat(buff_fmt, "\033[%dB");
		sprintf(buff, buff_fmt, y > 0 ? y : -y);
	}
	if (x) {
		if (x > 0)
			strcat(buff_fmt, "\033[%dC");
		else
			strcat(buff_fmt, "\033[%dD");
		sprintf(buff, buff_fmt, x > 0 ? x : -x);
	}
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
	printf("\033[%d;%dH", 1 + y, 1 + x);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			putchar(c);
		printf("\n\033[%dC", x - 1);
	}
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