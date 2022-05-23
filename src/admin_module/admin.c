#pragma once

int startAdminModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		// 让用户输入账号和密码
		page_login(&account, passwd, "管理员登录");
		while (!dc_checkAdminLogin(db, account, passwd)) {	// 检查账号和密码是否正确
			page_login(&account, passwd, "管理员登录: 账号或密码错误，请重新输入");
		}
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("Successfully login: administrator module\n");
	return 0;
}