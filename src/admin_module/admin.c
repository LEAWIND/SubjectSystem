#pragma once

int startAdminModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		page_login(&account, passwd, "管理员登录");
		while (!dc_checkAdminLogin(db, account, passwd)) {
			page_login(&account, passwd, "管理员登录: 账号或密码错误，请重新输入");
		}
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("administrator module\n");
}