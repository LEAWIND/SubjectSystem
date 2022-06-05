#pragma once


int startAdminModule(Database* db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	Admin* user;
	{
		//===============跳过登入环节
		// 让用户输入账号和密码
		// page_login(&account, passwd, "管理员登录");
		// while (!dc_checkAdminLogin(*db, account, passwd, &user)) {	// 检查账号和密码是否正确
		// 	system("cls");
		// 	cui_putStringCenterAt(us_width / 2, 3, "账号或密码错误，请重新输入! 按任意键继续", 0);
		// 	getch();
		// 	page_login(&account, passwd, "管理员登录");
		// }
		//===============以第一个管理员身份登入系统
		user = &(db->admins[0]);
		int stayHere = 1;
		while (stayHere) {
			cui_hideCursor();
			system("cls");
			// 显示页面
			printf("==========================================\n");
			printf("           选项界面\n");
			printf("==========================================\n");
			printf("\n\n  [1]管理课程\n");
			printf("\n\n  [2]管理课程班级\n");
			printf("\n\n  [3]修改密码\n");
			printf("\n\n  [ESC]  返回\n");

			// 获取输入
			char c;
			c = getch();
			switch (c) {
				case '\033'://ESC
					stayHere = 0;
					break;
				case '1':
					manageCourse(db);
					break;
				case '2':
					printf("管理老师模块");
					break;
				case '3':
					cui_showCursor();
					resetKey(user);
					break;
				//如果没有匹配任何一个选项则继续获取输入
				default:
					break;
			}
		}
		printf("Account: %lld\nPasswd: %s\n", account, passwd);
	}
	printf("Successfully login: administrator module\n");
	return 0;
}

void showCourses(Database *db, int page, int N)
{
	char* neStartTime[] = {"大一上","大一下","大二上", "大二下","大三上","大三下","大四上", "大四下"};
	printf("  课程ID  课程名称                    开课学期  所属的学院        学分\n");
	int i;
	for(i = page*N; i < (page+1)*N; i++)
	{
		Course c = db->courses[i];
		if(i >= db->courseCount) printf("\n");
		else
		{
			printf("  %-8lld%-28s%-10s%-18s%d\n", c.id, c.name, neStartTime[c.availableTime-1], colleges[c.college], c.point);
		}
	}
}

void manageCourse(Database* db)
{	
	int N = 10;//一页展示课程的数目
	int stayHere = 1;
	int page = 0;
	while(stayHere)
	{
		cui_hideCursor();
		//展示选项
		system("cls");
		printf("=====================================================================\n");
		printf("                  管理课程模块\n");
		printf("=====================================================================\n");
		showCourses(db, page, N);
		printf("=====================================================================\n");
		printf("\n\n  [esc]退出  [1]添加课程  [2]删除课程  [3]查找课程  [4]修改课程信息\n");
		printf("\n\n  左箭头：上一页  右箭头：下一页");
		//匹配选项
		int c;
		c = getch();
		switch (c)
		{
			case 27://ESC
				stayHere = 0;
				break;
			case 49://添加课程
				break;
			case 50://删除课程
				break;
			case 51://查找课程
				break;
			case 224://方向键区的ASCII码
				c = getch();	                    
				switch(c){
				case 75:    
					//左
					page = page-1 >= 0? page-1 : page;
					break;
				case 77:
					//右
					page = (page+1)*N < db->courseCount ? page+1 : page;
					break;   
				}
				break;
			default:
				break;
		}
	}
}

void resetKey(Admin *user)
{
	printf("\n\n  请输入您的新密码:");
	char key[32];
	char backupKey[32];
	scanf("%s", key);
	printf("\n\n  请再次输入您的新密码:");
	scanf("%s", backupKey);
	if(!strcmp(key, backupKey))
	{
		system("cls");
		printf("\n\n\n\n        设置成功");
		printf("%s", key);
		unsigned char psd[HASH_LEN];
		dc_hash32(key, 0, psd);
		memcpy((*user).key, psd, HASH_LEN);
	}
	else{
		system("cls");
		printf("\n\n\n\n        两次密码不一致");
	}
	getch();
}

