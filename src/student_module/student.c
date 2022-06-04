#pragma once

int startStudentModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		Student* stu;
		if (0) {
			page_login(&account, passwd, "ѧ����¼");
			while (1) {
				stu = dc_checkStudentLogin(db, account, passwd);
				if (stu != NULL)
					break;
				system("cls");
				cui_putStringCenterAt(us_width / 2, 3, "�˺Ż������������������! �����������", 0);
				getch();
				page_login(&account, passwd, "ѧ����¼");
			}
		} else {
			stu = dc_checkStudentLogin(db, 201900000001, "123456");
		}

		char stayHere = 1;
		while (stayHere) {
			system("cls");
			// ��ʾҳ��
			printf("�ɹ���¼ѧ���˺�: %lld\n", account);
			int y = 4;
			cui_putStringAt(1, y += 2, "1.�鿴�γ̱�");
			cui_putStringAt(1, y += 2, "2.ѡ��");
			cui_putStringAt(1, y += 2, "3.�޸�����");
			// ��ȡ����
			char c;
			do {
				c = getch();
				switch (c) {
					case '1':
						stu_page_classSheet(&db, stu);
						break;
					case '2':
						break;
					case '3':
						break;
					case '\033':
						stayHere = 0;
						break;
				}
			} while (stayHere);
		}
	}
	printf("Successfully login: student module\n");
}

// �򿪿γ̱�
int stu_page_classSheet(Database* db, Student* stu) {
	char stayHere = 1;
	while (stayHere) {
		{  // render
			system("cls");
			printf("%s", stu->name);
			int y = 1;
			cui_putStringCenterAt(us_width / 2, y, "�γ̱�", 0);

			const int w = 11, h = 4;
			// һ�� 7 ��
			for (int day = 0; day < 7; day++) {
				// һ�� 7 ��ʱ��
				for (int cp = 0; cp < PERIODS_PER_DAY; cp++) {
					long long ccid = stu->classSheet[day][cp];
					int dx = 4 + day * (w + 1),
						dy = y + 2 + cp * (h + 1);
					cui_strokeRect(dx - 1, dy - 1, w + 2, h + 2, 0);  // ���Ʊ߿�

					if (ccid < 0) {
						cui_putWrappedText(dx, dy, w, h, "��", 0);
						continue;
					} else {
						CourseClass* courseClass = db->courseClasses + ccid;
						Course* course = db->courses + courseClass->course;
						cui_putWrappedText(dx, dy, w, h, course->name, 0);
						// printf("%s\n", course->name);
					}
				}
			}
		}
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
	return 0;
}