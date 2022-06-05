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
		printf("\n\n  <-：上一页  ->：下一页");
		//匹配选项
		int c;
		c = getch();
		switch (c)
		{
			case 27://ESC
				stayHere = 0;
				break;
			case 49://添加课程
				addCourse(db);
				break;
			case 50://删除课程
				delCourse(db);
				break;
			case 51://查找课程
				findCourseName(db);
				break;
			case 52://查找课程
				changeCourse(db);
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

int strFind(char *arr[], char *str, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
		if(!strcmp(arr[i], str)) return i;
	return -1;//未找到
}

void addCourse(Database *db)
{
	char* neStartTime[] = {"大一上", "大一下", "大二上", "大二下", "大三上", "大三下", "大四上", "大四下"};	 // 各学期名称
	cui_showCursor();
	Course c;
	//获取课程名称
	printf("\n\n  请输入课程名称:");
	scanf("%s", c.name);
	//获取开课时间
	printf("  请输入课程开课时间:");
	char startTime[100];
	scanf("%s", startTime);

	int t = strFind(neStartTime, startTime, 8);
	if(t == -1)
	{
		printf("  开课时间有误！！！");
		getch();
		return;
	}
	c.availableTime = t;
	//获取所属学院
	printf("  请输入所属学院:");
	char college[100];
	scanf("%s", college);
	t = strFind(colleges, college, 18);
	if(t == -1)
	{
		printf("  学院有误！！！");
		getch();
		return;
	}
	c.college = t;
	//获取学分
	printf("  请输入学分:");
	scanf("%d", &(c.point));

	// 获取新的 id
	c.id = db->courseCount+1;
	c.isDeleted = 0;
	db->courses[db->courseCount++] = c;
	printf("  创建成功！！！");
	getch();
}

void showCourses(Database *db, int page, int N)
{
	printf("  课程ID  课程名称                    开课学期  所属的学院        学分\n");
	int i;
	int cnt = 0;//需要打印的空行
	for(i = page*N; i < (page+1)*N; i++)
	{
		Course c = db->courses[i];
		if(i >= db->courseCount || c.isDeleted == 1) printf("\n");
		else
		{
			printf("  %-8lld%-28s%-10s%-18s%d\n", c.id, c.name, neStartTime[c.availableTime-1], colleges[c.college], c.point);
		}
	}
}

void delCourse(Database * db)
{
	printf("\n\n  请输入需要删除课程的id:");
	long long id;
	scanf("%lld", &id);
	//寻找课程
	Course *c = findCourse(db->courses,id,  0, db->courseCount-1);
	if(!c)
	{
		printf("  该课程不存在，无法删除!!!");
		getch();
		return;
	}
	//将该课程对应的课程班级删除
	int i;
	for(i = 0; i < db->ccCount; i ++)
	{
		if(db->courseClasses[i].course == id) db->courseClasses[i].isDeleted = 1;
	}
	//删除该课程
	c->isDeleted = 1;
	printf("  删除成功！！！");
	getch();
}

//在学生们里面找到学号为id的学生并返回
Course* findCourse(Course* courses, long long id, int l, int r)
{
	while(l < r)
	{
		int mid = l + r >> 1;
		if(courses[mid].id >= id) r = mid;
		else l = mid+1;
	}
	if(courses[l].id != id) return NULL;
	return &(courses[l]);
}

void findCourseName(Database* db)
{
	char name[100];
	printf("\n\n  请输入课程名称:");
	scanf("%s", name);
	int i = 0;
	int cnt = 0;//记录找到的结果数目
	printf("  课程ID  课程名称                    开课学期  所属的学院        学分\n");
	for(i = 0; i < db->courseCount; i++)
	{
		Course c = db->courses[i];
		//printf("--%s %s %d %s--\n ", c.name, name,c.isDeleted, strstr(c.name, name));
		if(c.isDeleted != 1 && strstr(c.name, name) != NULL)
		{
			cnt++;
			printf("  %-8lld%-28s%-10s%-18s%d\n", c.id, c.name, neStartTime[c.availableTime-1], colleges[c.college], c.point);
		}
	}
	if(!cnt) printf("\n\n  内容为空\n\n");
	getch();
}

void changeCourse(Database *db)
{
	cui_showCursor();
	long long id;
	printf("\n\n  请输入您要修改课程的id:");
	scanf("%lld", &id);
	Course* c = findCourse(db->courses, id, 0, db->courseCount-1);
	printf("  （提示：如果保持不变则输入-1）");

	//获取课程名称
	printf("\n\n  请输入课程名称:");
	char name[100];
	scanf("%s", name);
	if(strcmp("-1", name)) strcpy(c->name, name);
	//获取开课时间
	printf("  请输入课程开课时间:");
	char startTime[100];
	scanf("%s", startTime);

	int t = strFind(neStartTime, startTime, 8);
	if(strcmp("-1", startTime) && t == -1)
	{
		printf("  开课时间有误！！！");
		getch();
		return;
	}
	if(strcmp("-1", startTime)) c->availableTime = t;
	//获取所属学院
	printf("  请输入所属学院:");
	char college[100];
	scanf("%s", college);
	t = strFind(colleges, college, 18);
	if(strcmp("-1", college) && t == -1)
	{
		printf("  学院有误！！！");
		getch();
		return;
	}
	if(strcmp("-1", college)) c->college = t;
	//获取学分
	printf("  请输入学分:");
	int point;
	scanf("%d", &point);
	if(point != -1) c->point = point;
	// 获取新的 id
	c->isDeleted = 0;
	printf("  修改成功！！！");
	getch();
}