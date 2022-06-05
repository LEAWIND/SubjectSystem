#pragma once


int startAdminModule(Database* db) {
	system("cls");
	long long account;
	char passwd[HASH_LEN];
	Admin* user;
	{
		//===============�������뻷��
		// ���û������˺ź�����
		// page_login(&account, passwd, "����Ա��¼");
		// while (!dc_checkAdminLogin(*db, account, passwd, &user)) {	// ����˺ź������Ƿ���ȷ
		// 	system("cls");
		// 	cui_putStringCenterAt(us_width / 2, 3, "�˺Ż������������������! �����������", 0);
		// 	getch();
		// 	page_login(&account, passwd, "����Ա��¼");
		// }
		//===============�Ե�һ������Ա��ݵ���ϵͳ
		user = &(db->admins[0]);
		int stayHere = 1;
		while (stayHere) {
			cui_hideCursor();
			system("cls");
			// ��ʾҳ��
			printf("==========================================\n");
			printf("           ѡ�����\n");
			printf("==========================================\n");
			printf("\n\n  [1]����γ�\n");
			printf("\n\n  [2]����γ̰༶\n");
			printf("\n\n  [3]�޸�����\n");
			printf("\n\n  [ESC]  ����\n");

			// ��ȡ����
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
					printf("������ʦģ��");
					break;
				case '3':
					cui_showCursor();
					resetKey(user);
					break;
				//���û��ƥ���κ�һ��ѡ���������ȡ����
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
	int N = 10;//һҳչʾ�γ̵���Ŀ
	int stayHere = 1;
	int page = 0;
	while(stayHere)
	{
		cui_hideCursor();
		//չʾѡ��
		system("cls");
		printf("=====================================================================\n");
		printf("                  ����γ�ģ��\n");
		printf("=====================================================================\n");
		showCourses(db, page, N);
		printf("=====================================================================\n");
		printf("\n\n  [esc]�˳�  [1]��ӿγ�  [2]ɾ���γ�  [3]���ҿγ�  [4]�޸Ŀγ���Ϣ\n");
		printf("\n\n  <-����һҳ  ->����һҳ");
		//ƥ��ѡ��
		int c;
		c = getch();
		switch (c)
		{
			case 27://ESC
				stayHere = 0;
				break;
			case 49://��ӿγ�
				addCourse(db);
				break;
			case 50://ɾ���γ�
				delCourse(db);
				break;
			case 51://���ҿγ�
				findCourseName(db);
				break;
			case 52://���ҿγ�
				changeCourse(db);
				break;
			case 224://���������ASCII��
				c = getch();	                    
				switch(c){
				case 75:    
					//��
					page = page-1 >= 0? page-1 : page;
					break;
				case 77:
					//��
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
	printf("\n\n  ����������������:");
	char key[32];
	char backupKey[32];
	scanf("%s", key);
	printf("\n\n  ���ٴ���������������:");
	scanf("%s", backupKey);
	if(!strcmp(key, backupKey))
	{
		system("cls");
		printf("\n\n\n\n        ���óɹ�");
		printf("%s", key);
		unsigned char psd[HASH_LEN];
		dc_hash32(key, 0, psd);
		memcpy((*user).key, psd, HASH_LEN);
	}
	else{
		system("cls");
		printf("\n\n\n\n        �������벻һ��");
	}
	getch();
}

int strFind(char *arr[], char *str, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
		if(!strcmp(arr[i], str)) return i;
	return -1;//δ�ҵ�
}

void addCourse(Database *db)
{
	char* neStartTime[] = {"��һ��", "��һ��", "�����", "�����", "������", "������", "������", "������"};	 // ��ѧ������
	cui_showCursor();
	Course c;
	//��ȡ�γ�����
	printf("\n\n  ������γ�����:");
	scanf("%s", c.name);
	//��ȡ����ʱ��
	printf("  ������γ̿���ʱ��:");
	char startTime[100];
	scanf("%s", startTime);

	int t = strFind(neStartTime, startTime, 8);
	if(t == -1)
	{
		printf("  ����ʱ�����󣡣���");
		getch();
		return;
	}
	c.availableTime = t;
	//��ȡ����ѧԺ
	printf("  ����������ѧԺ:");
	char college[100];
	scanf("%s", college);
	t = strFind(colleges, college, 18);
	if(t == -1)
	{
		printf("  ѧԺ���󣡣���");
		getch();
		return;
	}
	c.college = t;
	//��ȡѧ��
	printf("  ������ѧ��:");
	scanf("%d", &(c.point));

	// ��ȡ�µ� id
	c.id = db->courseCount+1;
	c.isDeleted = 0;
	db->courses[db->courseCount++] = c;
	printf("  �����ɹ�������");
	getch();
}

void showCourses(Database *db, int page, int N)
{
	printf("  �γ�ID  �γ�����                    ����ѧ��  ������ѧԺ        ѧ��\n");
	int i;
	int cnt = 0;//��Ҫ��ӡ�Ŀ���
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
	printf("\n\n  ��������Ҫɾ���γ̵�id:");
	long long id;
	scanf("%lld", &id);
	//Ѱ�ҿγ�
	Course *c = findCourse(db->courses,id,  0, db->courseCount-1);
	if(!c)
	{
		printf("  �ÿγ̲����ڣ��޷�ɾ��!!!");
		getch();
		return;
	}
	//���ÿγ̶�Ӧ�Ŀγ̰༶ɾ��
	int i;
	for(i = 0; i < db->ccCount; i ++)
	{
		if(db->courseClasses[i].course == id) db->courseClasses[i].isDeleted = 1;
	}
	//ɾ���ÿγ�
	c->isDeleted = 1;
	printf("  ɾ���ɹ�������");
	getch();
}

//��ѧ���������ҵ�ѧ��Ϊid��ѧ��������
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
	printf("\n\n  ������γ�����:");
	scanf("%s", name);
	int i = 0;
	int cnt = 0;//��¼�ҵ��Ľ����Ŀ
	printf("  �γ�ID  �γ�����                    ����ѧ��  ������ѧԺ        ѧ��\n");
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
	if(!cnt) printf("\n\n  ����Ϊ��\n\n");
	getch();
}

void changeCourse(Database *db)
{
	cui_showCursor();
	long long id;
	printf("\n\n  ��������Ҫ�޸Ŀγ̵�id:");
	scanf("%lld", &id);
	Course* c = findCourse(db->courses, id, 0, db->courseCount-1);
	printf("  ����ʾ��������ֲ���������-1��");

	//��ȡ�γ�����
	printf("\n\n  ������γ�����:");
	char name[100];
	scanf("%s", name);
	if(strcmp("-1", name)) strcpy(c->name, name);
	//��ȡ����ʱ��
	printf("  ������γ̿���ʱ��:");
	char startTime[100];
	scanf("%s", startTime);

	int t = strFind(neStartTime, startTime, 8);
	if(strcmp("-1", startTime) && t == -1)
	{
		printf("  ����ʱ�����󣡣���");
		getch();
		return;
	}
	if(strcmp("-1", startTime)) c->availableTime = t;
	//��ȡ����ѧԺ
	printf("  ����������ѧԺ:");
	char college[100];
	scanf("%s", college);
	t = strFind(colleges, college, 18);
	if(strcmp("-1", college) && t == -1)
	{
		printf("  ѧԺ���󣡣���");
		getch();
		return;
	}
	if(strcmp("-1", college)) c->college = t;
	//��ȡѧ��
	printf("  ������ѧ��:");
	int point;
	scanf("%d", &point);
	if(point != -1) c->point = point;
	// ��ȡ�µ� id
	c->isDeleted = 0;
	printf("  �޸ĳɹ�������");
	getch();
}