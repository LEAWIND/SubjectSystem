#pragma once

int startStudentModule(Database db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		Student* stu;
		if (0) {
			page_login(&account, passwd, "学生登录");
			while (1) {
				stu = dc_checkStudentLogin(db, account, passwd);
				if (stu != NULL)
					break;
				system("cls");
				cui_putStringCenterAt(us_width / 2, 3, "账号或密码错误，请重新输入! 按任意键继续", 0);
				getch();
				page_login(&account, passwd, "学生登录");
			}
		} else {
			stu = dc_checkStudentLogin(db, 201900000001, "123456");
		}

		char stayHere = 1;
		while (stayHere) {
			system("cls");
			// 显示页面
			printf("成功登录学生账号: %lld\n", account);
			int y = 4;
			cui_putStringAt(1, y += 2, "1.查看课程表");
			cui_putStringAt(1, y += 2, "2.选课");
			cui_putStringAt(1, y += 2, "3.修改密码");
			// 获取输入
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

// 打开课程表
int stu_page_classSheet(Database* db, Student* stu) {
	char stayHere = 1;
	while (stayHere) {
		{  // render
			system("cls");
			printf("%s", stu->name);
			int y = 1;
			cui_putStringCenterAt(us_width / 2, y, "课程表", 0);

			const int w = 11, h = 4;
			// 一周 7 天
			for (int day = 0; day < 7; day++) {
				// 一天 7 个时段
				for (int cp = 0; cp < PERIODS_PER_DAY; cp++) {
					long long ccid = stu->classSheet[day][cp];
					int dx = 4 + day * (w + 1),
						dy = y + 2 + cp * (h + 1);
					cui_strokeRect(dx - 1, dy - 1, w + 2, h + 2, 0);  // 绘制边框

					if (ccid < 0) {
						cui_putWrappedText(dx, dy, w, h, "空", 0);
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