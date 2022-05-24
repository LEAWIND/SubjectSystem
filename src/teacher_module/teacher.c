#pragma once

int startTeacherModule(Database db) {
	system("cls");
	long long account;//教师输入的账号
	char passwd[HASH_LEN];//输入的密码
	{
		page_login(&account, passwd, "教师登录");
		while (!dc_checkTeacherLogin(db, account, passwd)) {
			page_login(&account, passwd, "教师登录: 账号或密码错误，请重新输入");
		}
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("Successfully login: teacher module\n");
}