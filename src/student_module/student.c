#pragma once

int startStudentModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		page_login(&account, passwd, "ѧ����¼");
		while (!dc_checkStudentLogin(db, account, passwd)) {
			system("cls");
			cui_putStringCenterAt(us_width / 2, 3, "�˺Ż������������������! �����������", 0);
			getch();
			page_login(&account, passwd, "ѧ����¼");
		}
		char stayHere = 1;
		while (stayHere) {
			system("cls");
			// ��ʾҳ��
			printf("�ɹ���¼ѧ���˺�: %lld\n", account);
			int y = 4;
			cui_putStringAt(1, y += 2, "");
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
	}
	printf("Successfully login: student module\n");
}
