#pragma once

int startAdminModule() {
	system("cls");

	long long account;
	char passwd[HASH_LEN];
	{
		do {
			page_login(&account, passwd);
			// 查询数据库，判断是否正确
			break;
		} while (1);
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("administrator module\n");
}