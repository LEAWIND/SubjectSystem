#pragma once

int startStudentModule(Database db) {
	system("color F0");
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		Student* stu;
		if (!DEBUG_MODE) {
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
			printf("��ӭ %s ͬѧ", stu->name);
			int y = 4;
			cui_putStringAt(1, y += 2, "  1.�鿴�γ̱�");
			cui_putStringAt(1, y += 2, "  2.ѡ��");
			cui_putStringAt(1, y += 2, "  3.�޸�����");
			cui_putStringAt(1, y += 2, "Esc.����");
			// ��ȡ����
			char c;
			c = getch();
			switch (c) {
				case '1':
					stu_page_classSheet(&db, stu);
					break;
				case '2':
					stu_page_chooseCourse(&db, stu);
					break;
				case '3':
					stu_page_changePassword(&db, stu);
					break;
				case '\033':
					stayHere = 0;
					break;
			}
		}
	}
	printf("Successfully login: student module\n");
}

// ����ѧ���Ŀγ̱�
int stu_page_classSheet(Database* db, Student* stu) {
	char stayHere = 1;
	while (stayHere) {
		{  // render
			system("cls");
			printf("��ӭ %s ͬѧ", stu->name);
			int y = 1;
			cui_putStringCenterAt(us_width / 2, y, "�γ̱�", 0);

			const int w = 15, h = 3;
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
					} else {  // ���ƿγ�����
						CourseClass* cc = ds_getCourseClassById(db, ccid);
						Course* course = ds_getCourseById(db, cc->course);
						cui_putWrappedText(dx, dy, w, h, course->name, 0);
					}
				}
			}
		}
		char c;
		c = getch();
		switch (c) {
			case '\033':
				stayHere = 0;
				break;
		}
	}
	return 0;
}

// ��ѡ�ν���
int stu_page_chooseCourse(Database* db, Student* stu) {
	const int ItemsPerPage = 12;
	int pageIndex = 0;
	char stayHere = 1;
	while (stayHere) {
		int ix, iy;			  // �û��������λ��
		char inputBuff[100];  // �û����뻺��
		memset(inputBuff, 0, 100);
		int inputLen = 0;

		{  // render
			char buff[200];
			system("cls");
			printf("��ӭ %s ͬѧ", stu->name);
			int y = 5;
			// �г���ҳ���пγ�
			{
				int x = 3;
				cui_putStringAt(x + 0, y, "���");
				cui_putStringAt(x + 5, y, "�γ�����");
				cui_putStringAt(x + 50, y, "�γ̰༶����");
				int j = pageIndex * ItemsPerPage;  // ��ҳ��һ�����±�
				for (int i = 0; i < ItemsPerPage && j + i < db->courseCount; i++) {
					Course* course = db->courses + j + i;
					y += 2;
					sprintf(buff, "%3d. %s", j + i, course->name);
					cui_putStringAt(x, y, buff);			 // ��ӡ�γ�����
					cui_strokeRect(x - 1, y - 1, 70, 3, 0);	 // ���Ʊ߿�

					sprintf(buff, "%2d", dc_searchCourseClasses(db, course, NULL));	 // ��ӡ��Ӧ�Ŀγ̰༶����
					cui_putStringAt(x + 50, y, buff);
					cui_strokeRect(x - 1, y - 1, 70, 3, 0);
				}
			}
			// ҳ����ʾ
			sprintf(buff, "[%d/%d] �� ',' �� '.' ����ҳ", pageIndex, db->courseCount / ItemsPerPage);
			cui_putStringAt(5, y += 2, buff);
			cui_putStringAt(2, y += 1, "������γ���ţ�");

			ix = 5;
			iy = y += 1;
			cui_setCursorPos(ix, iy);
		}
		{
			int hisChoice = -1;
			char keepTyping = 1;
			char c;
			while (keepTyping) {
				c = getch();
				switch (c) {
					case ',':
						pageIndex -= pageIndex > 0 ? 1 : 0;
						keepTyping = 0;
						break;
					case '.':
						pageIndex += (pageIndex < (db->courseCount / ItemsPerPage)) ? 1 : 0;
						keepTyping = 0;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						if (inputLen < 10)
							inputBuff[inputLen++] = c;
						break;
					case '\b':
						if (inputLen) {
							inputBuff[--inputLen] = '\0';
							printf("\033[1D\033[1X");
						}
						break;
					case '\r':
						sscanf(inputBuff, "%d", &hisChoice);
						if (hisChoice >= db->courseCount) {
							memset(inputBuff, 0, 100);
							inputLen = 0;
							cui_clearRect(ix, iy, 10, 1);
						} else {
							keepTyping = 0;
						}
						break;
					case '\033':
						stayHere = 0;
						keepTyping = 0;
						break;
					default:
						break;
				}
				cui_putStringAt(ix, iy, inputBuff);
			}
			if (hisChoice >= 0) {
				// ѡ��Ŀγ��� hisChoice
				stu_page_chooseCourseClasses(db, stu, db->courses + hisChoice);	 // ѡ��γ̰༶
			}
		}
	}
	return 0;
}

// ѡ��γ̰༶
int stu_page_chooseCourseClasses(Database* db, Student* stu, Course* course) {
	char inputBuff[100];
	memset(inputBuff, 0, 100);
	int inlen = 0;
	int ix, iy;

	char buff[100];
	char stayHere = 1;
	char keepTyping = 1;
	int hisChoice;
	while (stayHere) {
		// render
		system("cls");
		printf("��ӭ %s ͬѧ", stu->name);
		int x = us_width / 2 - 20;
		int y = 0;
		cui_putStringCenterAt(us_width / 2, y += 2, course->name, 0);

		// �������ж�Ӧ�Ŀγ̰༶
		CourseClass* ccs[100];
		int ccslen = dc_searchCourseClasses(db, course, ccs);

		// ��ӡ���ж�Ӧ�Ŀγ̰༶
		if (ccslen) {
			sprintf(buff, "%15s%20s", "��ʦ", "����");
			cui_putStringAt(x, y += 2, buff);
			for (int i = 0; i < ccslen; i++) {
				if (!(ccs[i]))
					continue;
				// �±ꡢ��ʦ����������
				sprintf(buff, "[%2d] %13s%20s", i, db->teachers[ccs[i]->teacherID].name, "W4508");
				cui_putStringAt(x, y += 2, buff);
				cui_strokeRect(x - 1, y - 1, 40, 3, 0);
			}
			cui_putStringAt(2, y += 3, "������γ̰༶���:");
		} else {
			cui_putStringCenterAt(us_width / 2, y += 2, "û�ж�Ӧ�Ŀγ̰༶�ɹ�ѡ��", 0);
		}
		ix = 5;
		iy = y += 1;
		cui_setCursorPos(ix, iy);

		char c;
		while (keepTyping) {
			c = getch();
			switch (c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if (inlen < 10)
						inputBuff[inlen++] = c;
					break;
				case '\b':
					if (inlen) {
						inputBuff[--inlen] = '\0';
						printf("\033[1D\033[1X");
					}
					break;
				case '\r':
					sscanf(inputBuff, "%d", &hisChoice);
					if (hisChoice >= ccslen) {
						memset(inputBuff, 0, 100);
						inlen = 0;
						cui_clearRect(ix, iy, 10, 1);
					} else if (inlen) {
						keepTyping = 0;
						stayHere = 0;
						int res = stu_page_courseClassPreview(db, ccs[hisChoice]);

						if (res) {
							// TODO ȷ��ѡ��˿γ�
							CourseClass* cc = ccs[hisChoice];
							// db, stu, course, cc
							{  // �޸�ѧ���γ̱�
								// �����γ̵�ʱ�����
								for (int i = 0; i < cc->periods[0]; i++) {
									int p = cc->periods[i + 1];	 // ʱ����±�
									int day = p / 7;
									int cp = p % 7;
									stu->classSheet[day][cp] = cc->id;	// �޸Ŀγ̱� ��Ӧλ�� Ϊ�γ̰༶id
								}
							}
							{
								// �޸Ŀγ̰༶�� ѧ�� ID
								cc->students[cc->students[0] + 1] = stu->id;
								cc->students[0]++;
							}
						}
					}
					break;
				case '\033':
					keepTyping = 0;
					stayHere = 0;
					break;
				default:
					break;
			}
			cui_putStringAt(ix, iy, inputBuff);
		}
	}
	return 0;
}

// �γ̰༶Ԥ��
int stu_page_courseClassPreview(Database* db, CourseClass* cc) {
	Teacher* tea = ds_getTeacherById(db, cc->teacherID);
	if (!tea) {
		getch();
	}
	char stayHere = 1;
	while (stayHere) {
		{  // render
			char buff[100];
			char name[100];
			system("cls");
			int x = 5;
			int y = 0;

			cui_putStringCenterAt(us_width / 2, y += 1, ds_getCourseById(db, cc->course)->name, 0);
			// �γ̰༶
			sprintf(name, "%s%3d��", tea->name, cc->id_local);
			cui_putStringAt(x, y += 2, name);
			// ����
			sprintf(buff, "���ң�%s", cc->room);
			cui_putStringAt(x, y += 1, buff);
			// ��ʦ����
			sprintf(buff, "��ʦ��飺%s", tea->introduce);
			cui_putStringAt(x, y += 2, buff);
			{  //  �Ͽ�ʱ��Σ����
				const int w = 15, h = 2;
				// �߿�
				// һ�� 7 ��
				for (int day = 0; day < 7; day++) {
					// һ�� 7 ��ʱ��
					for (int cp = 0; cp < PERIODS_PER_DAY; cp++) {
						int dx = 4 + day * (w + 1),
							dy = y + 2 + cp * (h + 1);
						cui_strokeRect(dx - 1, dy - 1, w + 2, h + 2, 0);  // ���Ʊ߿�
					}
				}
				// ����
				for (int i = 0; i < cc->periods[0]; i++) {
					int index = cc->periods[i + 1];
					int day = index / 7,
						cp = index % 7;
					int dx = 4 + day * (w + 1),
						dy = y + 2 + cp * (h + 1);
					cui_putWrappedText(dx, dy, w, h, name, 0);
				}
				y += 7 * (h + 1) + 1;
			}
			// ������ʾ
			cui_putStringAt(x, y += 1, "���س�ȷ��, ESC ȡ�� ");
		}
		{  // event
			char c;
			c = getch();
			switch (c) {
				case '\r':
					// TODO ȷ��ѡ��
					return 1;
				case '\033':
					return 0;
			}
		}
	}
}

//
int stu_page_changePassword(Database* db, Student* stu) {
	char buff[100];
	char npsd1[32];
	char npsd2[32];
	char stayHere = 1;
	while (stayHere) {
		cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
		cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
		int x = 2, y = 0;
		sprintf(buff, "�����޸� %s ͬѧ������(*��0��)", stu->name);
		cui_putStringCenterAt(us_width / 2, y += 1, buff, 0);

		cui_putStringAt(x, y += 2, "������������:________________");
		cui_moveCursor(-16, 0);
		cui_setFontStyle(4);
		cui_inputs(npsd1, 32, '*');
		cui_setFontStyle(24);

		cui_putStringAt(x, y += 2, "�ٴ���������:________________");
		cui_moveCursor(-16, 0);
		cui_setFontStyle(4);
		cui_inputs(npsd2, 32, '*');	 // ��������
		cui_setFontStyle(24);

		if (!strcmp(npsd1, npsd2)) {
			// �����
			stayHere = 0;

			// �޸�����
			dc_hash32(npsd1, 32, npsd2);
			memcpy(stu->key, npsd2, 32);
		};
	}
}