#pragma once

int startAdminModule() {
	system("cls");

	long long account;
	char passwd[HASH_LEN];
	{
		page_login(&account, passwd);
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("administrator module\n");
}