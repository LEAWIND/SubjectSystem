#pragma once
// [����̨�����ն�����](https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences)

/**
 * @brief �����ı���ʽ��n ��ֵ�ο�[https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences#text-formatting]
 * @param n
 */
void cui_setFontStyle(int n) {
	printf("\033[%dm", n);
};

// ��ȡ�û������ַ���
void cui_inputs(char* s, int maxLen, char replaceChar) {
	int len = 0;
	char c, doLoop = 1;
	int flag;
	while (doLoop) {
		c = getch();  // �޻�������
		switch (c) {
			case '\r':	// �س� \r\n �����������
				if (len)
					doLoop = 0;
				break;
			case '\b':	// �˸�
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

// ���ù��λ��
void cui_setCursorPos(int x, int y) {
	printf("\033[%d;%dH", y < 0 ? 1 : 1 + y, x < 0 ? 1 : 1 + x);
}

// �ƶ����
void cui_moveCursor(int x, int y) {
	char buff_fmt[15];	// ��ʽ����
	char buff[64];		// �����ַ�����
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

// ���ع��
void cui_hideCursor() {
	printf("\033[?25l");
}

// ��ʾ���
void cui_showCursor() {
	printf("\033[?25h");
}

// ���ַ�����ӡ��ָ��λ��
void cui_putStringAt(int x, int y, char* c) {
	printf("\033[%d;%dH%s", 1 + y, 1 + x, c);
}

// ���ַ�����ӡ��ָ��λ�ã����Ķ���
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

// ���ַ�����������
void cui_fillRect(int x, int y, int w, int h, char c) {
	for (int i = 0; i < h; i++) {
		printf("\033[%d;%dH", 1 + y + i, 1 + x);
		for (int j = 0; j < w; j++)
			putchar(c);
	}
}

// �����������
void cui_clearRect(int x, int y, int w, int h) {
	for (int i = 0; i < h; i++)
		printf("\033[%d;%dH\033[%dX", 1 + y + i, 1 + x, w);
}

// ���ƾ��α߿�
void cui_strokeRect(int x, int y, int w, int h, char c) {
	// �ƶ����
	printf("\033[%d;%dH", 1 + y, 1 + x);
	// ����
	putchar('*' | c);
	// ��
	for (int i = 2; i < w; i++)
		putchar('-' | c);
	// ����
	putchar('*' | c);
	// �ƶ����
	printf("\033[%d;%dH", 2 + y, 1 + x);
	// ��
	for (int i = 2; i < h; i++)
		printf("%c\033[1B\033[1D", '|' | c);
	// ����
	putchar('*' | c);
	// ��
	for (int i = 2; i < w; i++)
		putchar('-' | c);
	// ����
	putchar('*' | c);
	// �ƶ����
	printf("\033[%d;%dH", 2 + y, x + w);
	// ��
	for (int i = 2; i < h; i++)
		printf("%c\033[1B\033[1D", '|' | c);
}
