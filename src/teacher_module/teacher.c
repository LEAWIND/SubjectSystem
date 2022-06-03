#pragma once

int startTeacherModule(Database db) {
	system("cls");
	Teacher user;

	//===============跳过登入
	// long long account;//教师输入的账号
	// char passwd[HASH_LEN];//输入的密码
	// {
	// 	page_login(&account, passwd, "教师登录");
	// 	while (!dc_checkTeacherLogin(db, account, passwd, &user)) {
	// 		page_login(&account, passwd, "教师登录: 账号或密码错误，请重新输入");
	// 	}
	// }

	user = db.teachers[0];
	startSection(db, &user);
}

void startSection(Database db, Teacher* user){
	system("cls");
	int op;//存储用户的选项
	op = showMenuTeacher((*user).name);//获取用户选项
	switch (op)
	{
	case 1:
		queryClass(db, user);
		break;
	case 2:
		manageClass(db, user);
		break;
	case 3:
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
	getch();
}

int showMenuTeacher(char *name){
	cui_setFontStyle(0);						   // 默认样式
	cui_clearRect(0, 0, us_width, us_height);	   // 清空矩形区域
	cui_strokeRect(0, 0, us_width, us_height, 0);  // 绘制边框
	int y = 2;
	cui_putStringCenterAt(us_width / 2, y += 4, name, strlen(name));

	cui_putStringAt(2, y += 2, "[1]查看班级信息");
	cui_putStringAt(2, y += 2, "[2]管理班级");
	cui_putStringAt(2, y += 2, "[3]修改个人信息模块");
	cui_putStringAt(2, y += 4, "[   ]请输入选项\b\b\b\b\b\b\b\b\b\b\b\b\b");

	int c;
	scanf("%d", &c);
	return c;
}

void queryClass(Database db, Teacher* user){
	system("cls");
	printf("您已进入查询班级信息模块");
}

void manageClass(Database db, Teacher* user){
	system("cls");
	printf("您已进入管理班级模块");
}

void resetInfo(Database db, Teacher* user){
	system("cls");
	printf("您已进入修改个人信息模块");
}