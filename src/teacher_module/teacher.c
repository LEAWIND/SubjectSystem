#pragma once

int startTeacherModule(Database db) {
	system("cls");
	Teacher* user;//正在使用的用户

	//===============跳过登入
	// long long account;//教师输入的账号
	// char passwd[HASH_LEN];//输入的密码
	// {
	// 	page_login(&account, passwd, "教师登录");
	// 	while (!dc_checkTeacherLogin(db, account, passwd, &user)) {
	// 		page_login(&account, passwd, "教师登录: 账号或密码错误，请重新输入");
	// 	}
	// }
	//====================
	user = db.teachers;
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
	showCS(1, 0, db, user);
}

//在学生们里面找到学号为id的学生并返回
Student* findStudent(Student* students, long long id, int l, int r)
{
	while(l < r)
	{
		int mid = l + r >> 1;
		if(students[mid].id >= id) r = mid;
		else l = mid+1;
	}
	return &(students[l]);
}

void showCS(int posClass, int posStudent, Database db, Teacher* user){
	system("cls");
	const int N = 10;//一页最多展示学生数目
	int i;
	long long classId = (*user).CourseClasses[posClass];
	CourseClass* CC;
	//找到对应的课程班级
	for(i = 0; i < db.ccCount; i++)
	{
		if(db.courseClasses[i].id == classId)
		{
			CC = &(db.courseClasses[i]);
		}
	}
	//得到课程名字
	char* courseName;
	for(i = 0; i < db.courseCount; i++)
	{
		if(db.courses[i].id == CC->course)
		{
			courseName = db.courses[i].name;
		}
	}
	printf("===================================================\n");
	printf("               %s%d班\n", courseName,CC->id_local);
	printf("===================================================\n");
	printf("   学号          姓名         所属学院\n");
	//打印学生信息
	for(int i = posStudent*N + 1; i <= posStudent*(N+1); i++)
	{
		Student* stu = findStudent(db.students,CC->students[i], 0, db.studentCount-1);
		printf("   %-12lld  %-6s    %-8s\n",stu->id, stu->name, colleges[stu->college]);
	}
	printf("===================================================\n");
	printf("左箭头:上一页，右箭头:下一页，上箭头:上一个班级，下箭头:下一个班级\n");
	//等待用户输入
	int stayHere = 1;
	while (stayHere) {
		stayHere = 0;
		int userType = getch();	
		switch(userType){
			case 224://方向键区的ASCII码
				userType = getch();	                    
				switch(userType){
				case 72:
					//上
					showCS(posClass-1 >= 1 ? posClass -1 : posClass , 0, db,  user);
					break;
				case 80:
					//下 
					showCS(posClass+1 <= user->CourseClasses[0] ? posClass+1 : posClass, 0, db,  user);
					break;
				case 75:    
					//左
					showCS(posClass, posStudent-1 >= 0 ? posStudent-1: posStudent, db,  user);
					break;
				case 77:
					showCS(posClass, (posStudent+1)*N+1 <= CC->students[0]?posStudent+1:posStudent, db,  user);
					//右
					break;   
				}
				break;
			case 27:  // Esc
				break;
		default:
			stayHere = 1;       
		}
	}
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
		cui_inputs(content, 32, '*');
		printf("\n  请重新输入输入您的新密码:");
		char temp[1024];
		memset(temp, '\0', sizeof(temp));
		cui_inputs(temp, 32, '*');
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