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

		int stayHere = 1;
		while (stayHere) {
			system("cls");
			// ��ʾҳ��
			printf("==========================================\n");
			printf("           ѡ�����\n");
			printf("==========================================\n");
			printf("  [1]����ѧ���˺�\n");
			printf("  [2]������ʦ�˺�\n");
			printf("  ESC  ����\n");

			// ��ȡ����
			char c;
			do {
				c = getch();
				stayHere = 0;
				switch (c) {
					case '\033':
						break;
					case '1':
						printf("����ѧ��ģ��");
						break;
					case '2':
						printf("������ʦģ��");
						break;
					//���û��ƥ���κ�һ��ѡ���������ȡ����
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