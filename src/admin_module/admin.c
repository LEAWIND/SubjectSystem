#pragma once

int startAdminModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		// ���û������˺ź�����
		page_login(&account, passwd, "����Ա��¼");
		while (!dc_checkAdminLogin(db, account, passwd)) {	// ����˺ź������Ƿ���ȷ
			system("cls");
			cui_putStringCenterAt(us_width / 2, 3, "�˺Ż������������������! �����������", 0);
			getch();
			page_login(&account, passwd, "����Ա��¼");
		}

		char stayHere = 1;
		while (stayHere) {
			system("cls");
			// ��ʾҳ��
			printf("�ɹ���¼����Ա�˺�: %lld\n", account);
			printf("ESC  ����");

			// ��ȡ����
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
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("Successfully login: administrator module\n");
	return 0;
}