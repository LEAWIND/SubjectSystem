#pragma once

int startStudentModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		page_login(&account, passwd, "学生登录");
		while (!dc_checkStudentLogin(db, account, passwd)) {
			system("cls");
			cui_putStringCenterAt(us_width / 2, 3, "账号或密码错误，请重新输入! 按任意键继续", 0);
			getch();
			page_login(&account, passwd, "学生登录");
		}
		char stayHere = 1;
		while (stayHere) {
			system("cls");
			// 显示页面
			printf("成功登录学生账号: %lld\n", account);
			int y = 4;
			cui_putStringAt(1, y += 2, "");
			// 获取输入
			char c;
			do {
				c = getch();
				switch (c) {
					case '\033':
						stayHere = 0;
						break;
				}
			} while (stayHere);
		}
	}
	printf("Successfully login: student module\n");
}
