#pragma once

int startTeacherModule(Database db) {
	system("cls");
	Teacher* user;//正在使用的用户

	//===============跳过登入
	long long account;//教师输入的账号
	char passwd[HASH_LEN];//输入的密码
	{
		page_login(&account, passwd, "教师登录");
		while (!dc_checkTeacherLogin(db, account, passwd, &user)) {
			page_login(&account, passwd, "教师登录: 账号或密码错误，请重新输入");
		}
	}
	//====================
	//user = db.teachers;
	startSection(db, user);
}

void startSection(Database db, Teacher* user){
	system("cls");
	int op;//存储用户的选项
	op = showMenuTeacher((*user).name);//获取用户选项
	switch (op)
	{
	case 0:
		return ;
	case 1:
		manageClass(db, user);
		break;
	case 2:
		resetInfo(db, user);
		break;
	default:
		system("cls");
		cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
		cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框
		cui_putStringCenterAt(us_width/2, us_height/2, "您输入的数字不符合要求", 0);
		getch();
		startSection(db, user);
		break;
	}
	startSection(db, user);
}

int showMenuTeacher(char *name){
	cui_setFontStyle(0);						   // 默认样式
	cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
	cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框
	int y = 2;
	// 隐藏光标
	cui_hideCursor();
	cui_putStringCenterAt(us_width / 2, y += 4, name, strlen(name));
	cui_putStringAt(2, y += 2, "[0]退出登录");
	cui_putStringAt(2, y += 2, "[1]管理班级");
	cui_putStringAt(2, y += 2, "[2]修改个人信息");
	cui_putStringAt(2, y += 4, "请输入选项");
	// 监听用户输入
	char ut;
	do {
		ut = getch();  // 无缓冲输入
	} while (!strchr("012", ut));
	cui_showCursor();  // 显示光标
	// printf("\033[?1049l");
	int op = ut - 48;
	return op;
}


void manageClass(Database db, Teacher* user){
	system("cls");
	printf("您已进入管理班级模块");
}

void resetInfo(Database db, Teacher* user){
	system("cls");
	//展示修改个人信息的选项
	cui_setFontStyle(0);						   // 默认样式
	cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
	cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框
	int y = 2;
	cui_putStringAt(2, y += 2, "[0]退出选择");
	cui_putStringAt(2, y += 2, "[1]修改名字");
	cui_putStringAt(2, y += 2, "[2]修改个人简介");
	cui_putStringAt(2, y += 2, "[3]修改密码");
	cui_putStringAt(2, y += 2, "[4]查询个人信息");
	cui_putStringAt(2, y += 4, "请输入选项：");
	//获取选项及修改对应内容
	int op;
	char content[1024];
	memset(content, '\0', sizeof(content));
	scanf("%d", &op);
	getchar();
	switch (op)
	{
	case 0:
		return ;
	case 1:
		printf("  请输入您的新名字:");
		scanf("%s", content);

		// unsigned char sss[1024];
		// dc_test_sprintByte(content, sss);
		// printf("%s", sss);

		strcpy((*user).name, content);
		system("cls");
		printf("content %s\n", content);
		printf("  修改成功，您的新名字为：%s\n", (*user).name);
		getch();
		break;
	case 2:
		printf("  请输入您的新个人简介:");
		gets(content);
		strcpy((*user).introduce, content);
		system("cls");
		printf("  修改成功，您的介绍为为：%s\n", (*user).introduce);
		getch();
		break;
	case 3:
		printf("  请输入您的新密码:");
		scanf("%s", content);

		printf("  请重新输入输入您的新密码:");
		char temp[1024];
		memset(temp, '\0', sizeof(temp));
		scanf("%s", temp);
		if(!strcmp(temp, content))
		{
			unsigned char psd[HASH_LEN];
			dc_hash32(content, 0, psd);
			memcpy((*user).key, psd, HASH_LEN);

			system("cls");
			printf("  修改成功，您的密码为为：%s\n", content);
		}
		else
		{
			printf("  您两次输入的密码并不相同！！!");
			resetInfo(db, user);
		}
		getch();
		break;
	case 4:
		system("cls");
		printf("==================================================\n");
		printf("        个人信息\n");
		printf("==================================================\n\n");
		printf("   名字为：%s\n\n", (*user).name);
		printf("   个人简介为：%s\n\n", (*user).introduce);
		getch();
	default:
		break;
	}
}