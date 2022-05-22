#pragma once

char page_getUserType() {
	printf("\033[?1049h");
	cui_clearRect(0, 0, us_width, us_height);
	cui_strokeRect(0, 0, us_width, us_height, 0);

	cui_putStringCenterAt(us_width / 2, 1, " 选 课 系 统 ", 0);
	int y = 2;
	cui_putStringAt(us_width / 2 - 18, y += 2, "请按键:");
	cui_putStringAt(us_width / 2 - 14, y += 2, "1. 学生");
	cui_putStringAt(us_width / 2 - 14, y += 2, "2. 教师");
	cui_putStringAt(us_width / 2 - 14, y += 2, "3. 管理员");
	cui_putStringAt(us_width / 2 - 14, y += 2, "Esc. 退出");
	cui_hideCursor();
	char ut;
	do {
		ut = getch();
	} while (!strchr("123\033", ut));
	cui_showCursor();
	return ut;
	printf("\033[?1049l");
}

void page_login(long long* account, char* passwd, char* info) {
	printf("\033[?1049h");
	cui_clearRect(0, 0, us_width, us_height);
	cui_strokeRect(0, 0, us_width, us_height, 0);
	int y = 3;
	char buff[50];
	cui_putStringCenterAt(us_width / 2, y += 2, info, strlen(info));

	cui_putStringAt(3, y += 2, "账号:________________");
	cui_moveCursor(-16, 0);
	cui_setFontStyle(4);
	scanf("%lld", account);
	cui_setFontStyle(24);

	cui_putStringAt(3, y += 2, "密码:________________");
	cui_moveCursor(-16, 0);
	cui_setFontStyle(4);
	cui_inputSecret(passwd, 32, '*');
	cui_setFontStyle(24);
	printf("\033[?1049l");
}