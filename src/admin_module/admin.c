#pragma once

int startAdminModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		// 让用户输入账号和密码
		page_login(&account, passwd, "管理员登录");
		while (!dc_checkAdminLogin(db, account, passwd)) {	// 检查账号和密码是否正确
			system("cls");
			cui_putStringCenterAt(us_width / 2, 3, "账号或密码错误，请重新输入! 按任意键继续", 0);
			getch();
			page_login(&account, passwd, "管理员登录");
		}

		int stayHere = 1;
		while (stayHere) {
			system("cls");
			// 显示页面
			printf("==========================================\n");
			printf("           选项界面\n");
			printf("==========================================\n");
			printf("  [1]管理学生账号\n");
			printf("  [2]管理老师账号\n");
			printf("  ESC  返回\n");

			// 获取输入
			char c;
			do {
				c = getch();
				stayHere = 0;
				switch (c) {
					case '\033':
						break;
					case '1':
						printf("管理学生模块");
						break;
					case '2':
						printf("管理老师模块");
						break;
					//如果没有匹配任何一个选项则继续获取输入
					default:
						stayHere = 1;
						break;
				}
			} while (stayHere);
		}
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("Successfully login: administrator module\n");
	return 0;
}