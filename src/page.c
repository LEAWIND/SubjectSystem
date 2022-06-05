#pragma once

// 首页：选择用户类别
char page_getUserType() {
	// printf("\033[?1049h");
	cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
	cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框
	// 隐藏光标
	cui_hideCursor();
	// 放置一些文本
	cui_putStringCenterAt(us_width / 2, 1, " 选 课 系 统 ", 0);
	int y = 2;
	cui_putStringAt(us_width / 2 - 18, y += 2, "请按键:");
	cui_putStringAt(us_width / 2 - 14, y += 2, "1. 学生");
	cui_putStringAt(us_width / 2 - 14, y += 2, "2. 教师");
	cui_putStringAt(us_width / 2 - 14, y += 2, "3. 管理员");
	cui_putStringAt(us_width / 2 - 14, y += 2, "Esc. 退出");
	// 监听用户输入
	char ut;
	do {
		ut = getch();  // 无缓冲输入
	} while (!strchr("123\033", ut));
	cui_showCursor();  // 显示光标
	// printf("\033[?1049l");
	return ut;
}

void getVerificationCode(char verificationCode[], int n) {
	char str[] = "2323456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	// 0,1易与字母‘o’与‘l'混消，不用
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++)
		verificationCode[i] = str[rand() % 62];
	verificationCode[n] = '\0';
}

// 登录页面：获取用户输入的账号和密码原文
void page_login(long long* account, char* passwd, char* info) {
	while (1) {
		system("cls");
		// cui_setFontStyle(0);						   // 默认样式
		cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
		cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框

		int y = 3;
		// 放置文本
		cui_putStringCenterAt(us_width / 2, y += 2, info, strlen(info));

		cui_putStringAt(3, y += 2, "账号:________________");
		cui_moveCursor(-16, 0);
		// cui_setFontStyle(4);  // 带下划线
		char buff[50];
		cui_inputs(buff, 49, 0);
		sscanf(buff, "%lld", account);
		cui_setFontStyle(24);  // 不带下划线

		cui_putStringAt(3, y += 2, "密码:________________");
		cui_moveCursor(-16, 0);
		cui_setFontStyle(4);
		cui_inputs(passwd, 32, '*');  // 输入密码
		cui_setFontStyle(24);

		//验证码验证
		char verificationCode[5];		//存放验证码
		char inputVerificationCode[5];	//存入用户输入的验证码
		getVerificationCode(verificationCode, 4);
		printf("\n\n   验证码：            [%s]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", verificationCode);
		scanf("%s", inputVerificationCode);
		int flag = 1;
		if (strcmp(verificationCode, inputVerificationCode)) {
			system("cls");
			printf("验证码出错");
			getch();
			continue;
		}
		break;
	}
}