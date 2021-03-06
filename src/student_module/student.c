#pragma once

int startStudentModule(Database db) {
	system("color F0");
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	{
		Student* stu;
		if (!DEBUG_MODE) {
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
			printf("欢迎 %s 同学", stu->name);
			int y = 4;
			cui_putStringAt(1, y += 2, "  1.查看课程表");
			cui_putStringAt(1, y += 2, "  2.选课");
			cui_putStringAt(1, y += 2, "  3.修改密码");
			cui_putStringAt(1, y += 2, "Esc.返回");
			// 获取输入
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

// 绘制学生的课程表
int stu_page_classSheet(Database* db, Student* stu) {
	char stayHere = 1;
	while (stayHere) {
		{  // render
			system("cls");
			printf("欢迎 %s 同学", stu->name);
			int y = 1;
			cui_putStringCenterAt(us_width / 2, y, "课程表", 0);

			const int w = 15, h = 3;
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
					} else {  // 绘制课程名称
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

// 打开选课界面
int stu_page_chooseCourse(Database* db, Student* stu) {
	const int ItemsPerPage = 12;
	int pageIndex = 0;
	char stayHere = 1;
	while (stayHere) {
		int ix, iy;			  // 用户输入回显位置
		char inputBuff[100];  // 用户输入缓冲
		memset(inputBuff, 0, 100);
		int inputLen = 0;

		{  // render
			char buff[200];
			system("cls");
			printf("欢迎 %s 同学", stu->name);
			int y = 5;
			// 列出本页所有课程
			{
				int x = 3;
				cui_putStringAt(x + 0, y, "序号");
				cui_putStringAt(x + 5, y, "课程名称");
				cui_putStringAt(x + 50, y, "课程班级数量");
				int j = pageIndex * ItemsPerPage;  // 本页第一条的下标
				for (int i = 0; i < ItemsPerPage && j + i < db->courseCount; i++) {
					Course* course = db->courses + j + i;
					y += 2;
					sprintf(buff, "%3d. %s", j + i, course->name);
					cui_putStringAt(x, y, buff);			 // 打印课程名称
					cui_strokeRect(x - 1, y - 1, 70, 3, 0);	 // 绘制边框

					sprintf(buff, "%2d", dc_searchCourseClasses(db, course, NULL));	 // 打印对应的课程班级数量
					cui_putStringAt(x + 50, y, buff);
					cui_strokeRect(x - 1, y - 1, 70, 3, 0);
				}
			}
			// 页数提示
			sprintf(buff, "[%d/%d] 按 ',' 和 '.' 键翻页", pageIndex, db->courseCount / ItemsPerPage);
			cui_putStringAt(5, y += 2, buff);
			cui_putStringAt(2, y += 1, "请输入课程序号：");

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
				// 选择的课程是 hisChoice
				stu_page_chooseCourseClasses(db, stu, db->courses + hisChoice);	 // 选择课程班级
			}
		}
	}
	return 0;
}

// 选择课程班级
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
		printf("欢迎 %s 同学", stu->name);
		int x = us_width / 2 - 20;
		int y = 0;
		cui_putStringCenterAt(us_width / 2, y += 2, course->name, 0);

		// 搜索所有对应的课程班级
		CourseClass* ccs[100];
		int ccslen = dc_searchCourseClasses(db, course, ccs);

		// 打印所有对应的课程班级
		if (ccslen) {
			sprintf(buff, "%15s%20s", "教师", "教室");
			cui_putStringAt(x, y += 2, buff);
			for (int i = 0; i < ccslen; i++) {
				if (!(ccs[i]))
					continue;
				// 下标、教师姓名、教室
				sprintf(buff, "[%2d] %13s%20s", i, db->teachers[ccs[i]->teacherID].name, "W4508");
				cui_putStringAt(x, y += 2, buff);
				cui_strokeRect(x - 1, y - 1, 40, 3, 0);
			}
			cui_putStringAt(2, y += 3, "请输入课程班级序号:");
		} else {
			cui_putStringCenterAt(us_width / 2, y += 2, "没有对应的课程班级可供选择。", 0);
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
							// TODO 确认选择此课程
							CourseClass* cc = ccs[hisChoice];
							// db, stu, course, cc
							{  // 修改学生课程表
								// 遍历课程的时间段们
								for (int i = 0; i < cc->periods[0]; i++) {
									int p = cc->periods[i + 1];	 // 时间段下标
									int day = p / 7;
									int cp = p % 7;
									stu->classSheet[day][cp] = cc->id;	// 修改课程表 对应位置 为课程班级id
								}
							}
							{
								// 修改课程班级的 学生 ID
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

// 课程班级预览
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
			// 课程班级
			sprintf(name, "%s%3d班", tea->name, cc->id_local);
			cui_putStringAt(x, y += 2, name);
			// 教室
			sprintf(buff, "教室：%s", cc->room);
			cui_putStringAt(x, y += 1, buff);
			// 教师介绍
			sprintf(buff, "教师简介：%s", tea->introduce);
			cui_putStringAt(x, y += 2, buff);
			{  //  上课时间段（表格）
				const int w = 15, h = 2;
				// 边框
				// 一周 7 天
				for (int day = 0; day < 7; day++) {
					// 一天 7 个时段
					for (int cp = 0; cp < PERIODS_PER_DAY; cp++) {
						int dx = 4 + day * (w + 1),
							dy = y + 2 + cp * (h + 1);
						cui_strokeRect(dx - 1, dy - 1, w + 2, h + 2, 0);  // 绘制边框
					}
				}
				// 内容
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
			// 按键提示
			cui_putStringAt(x, y += 1, "按回车确认, ESC 取消 ");
		}
		{  // event
			char c;
			c = getch();
			switch (c) {
				case '\r':
					// TODO 确认选择
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
		cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
		cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框
		int x = 2, y = 0;
		sprintf(buff, "正在修改 %s 同学的密码(*￣0￣)", stu->name);
		cui_putStringCenterAt(us_width / 2, y += 1, buff, 0);

		cui_putStringAt(x, y += 2, "请输入新密码:________________");
		cui_moveCursor(-16, 0);
		cui_setFontStyle(4);
		cui_inputs(npsd1, 32, '*');
		cui_setFontStyle(24);

		cui_putStringAt(x, y += 2, "再次输入密码:________________");
		cui_moveCursor(-16, 0);
		cui_setFontStyle(4);
		cui_inputs(npsd2, 32, '*');	 // 输入密码
		cui_setFontStyle(24);

		if (!strcmp(npsd1, npsd2)) {
			// 若相等
			stayHere = 0;

			// 修改密码
			dc_hash32(npsd1, 32, npsd2);
			memcpy(stu->key, npsd2, 32);
		};
	}
}