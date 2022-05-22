#pragma once

int startStudentModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		page_login(&account, passwd, "学生登录");
		while (!dc_checkStudentLogin(db, account, passwd)) {
			page_login(&account, passwd, "学生登录: 账号或密码错误，请重新输入");
		}
		// printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("student module\n");
}
