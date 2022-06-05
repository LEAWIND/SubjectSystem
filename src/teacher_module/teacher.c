#pragma once

int startTeacherModule(Database db) {
	system("cls");
	Teacher* user;//����ʹ�õ��û�

	//===============��������
	long long account;//��ʦ������˺�
	char passwd[HASH_LEN];//���������
	{
		page_login(&account, passwd, "��ʦ��¼");
		while (!dc_checkTeacherLogin(db, account, passwd, &user)) {
			page_login(&account, passwd, "��ʦ��¼: �˺Ż������������������");
		}
	}
	//====================
	// user = db.teachers;

	startSection(db, user);
}

void startSection(Database db, Teacher* user){
	system("cls");
	int op;//�洢�û���ѡ��
	op = showMenuTeacher((*user).name);//��ȡ�û�ѡ��
	switch (op)
	{
	case '\033':
		return ;
	case '1':
		manageClass(db, user);
		break;
	case '2':
		resetInfo(db, user);
		break;
	default:
		system("cls");
		cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
		cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
		cui_putStringCenterAt(us_width/2, us_height/2, "����������ֲ�����Ҫ��", 0);
		getch();
		startSection(db, user);
		break;
	}
	startSection(db, user);
}

char showMenuTeacher(char *name){
	cui_setFontStyle(0);						   // Ĭ����ʽ
	cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
	cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
	int y = 2;
	// ���ع��
	cui_hideCursor();
	cui_putStringCenterAt(us_width / 2, y += 4, name, strlen(name));
	cui_putStringAt(2, y += 2, "[esc]�˳���¼");
	cui_putStringAt(2, y += 2, "[1]����༶");
	cui_putStringAt(2, y += 2, "[2]�޸ĸ�����Ϣ");
	// �����û�����
	char ut;
	do {
		ut = getch();  // �޻�������
	} while (!strchr("012\033", ut));
	cui_showCursor();  // ��ʾ���
	// printf("\033[?1049l");
	return ut;
}

void manageClass(Database db, Teacher* user){
	system("cls");
	showCS(1, 0, db, user);
}

//��ѧ���������ҵ�ѧ��Ϊid��ѧ��������
Student* findStudent(Student* students, long long id, int l, int r)
{
	while(l < r)
	{
		int mid = l + r >> 1;
		//printf("--mid students[%d].id:%lld --\n", mid, students[mid].id);
		if(students[mid].id%100000000 >= id%100000000) r = mid;
		else l = mid+1;
	}
	if(students[l].id != id) return NULL;
	return &(students[l]);
}

void showCS(int posClass, int posStudent, Database db, Teacher* user){
	system("cls");
	const int N = 10;//һҳ���չʾѧ����Ŀ
	int i;
	long long classId = (*user).CourseClasses[posClass];
	CourseClass* CC;
	//�ҵ���Ӧ�Ŀγ̰༶
	for(i = 0; i < db.ccCount; i++)
	{
		if(db.courseClasses[i].id == classId)
		{
			CC = &(db.courseClasses[i]);
		}
	}
	//�õ��γ�����
	char* courseName;
	for(i = 0; i < db.courseCount; i++)
	{
		if(db.courses[i].id == CC->course)
		{
			courseName = db.courses[i].name;
		}
	}
	printf("========================================================================\n");
	printf("               %s%d��\n", courseName,CC->id_local);
	printf("========================================================================\n");
	printf("   ѧ��          ����         ����ѧԺ\n");
	//��ӡѧ����Ϣ
	for(i = posStudent*N + 1; i <= (posStudent+1)*N; i++)
	{
		Student* stu = findStudent(db.students,CC->students[i], 0, db.studentCount-1);
		if(stu != NULL) printf("   %-12lld  %-13s    %-8s\n",stu->id, stu->name, colleges[stu->college]);
		else printf("\n");
	}
	printf("========================================================================\n");
	printf("���ͷ:��һҳ���Ҽ�ͷ:��һҳ���ϼ�ͷ:��һ���༶���¼�ͷ:��һ���༶ d:ɾ��ѧ��\n");
	//�ȴ��û�����
	int stayHere = 1;
	while (stayHere) {
		stayHere = 0;
		int userType = getch();	
		switch(userType){
			case 224://���������ASCII��
				userType = getch();	                    
				switch(userType){
				case 72:
					//��
					showCS(posClass-1 >= 1 ? posClass -1 : posClass , 0, db,  user);
					break;
				case 80:
					//�� 
					showCS(posClass+1 <= user->CourseClasses[0] ? posClass+1 : posClass, 0, db,  user);
					break;
				case 75:    
					//��
					showCS(posClass, posStudent-1 >= 0 ? posStudent-1: posStudent, db,  user);
					break;
				case 77:
					showCS(posClass, (posStudent+1)*N+1 <= CC->students[0]?posStudent+1:posStudent, db,  user);
					//��
					break;   
				}
				break;
			case 27:  // Esc
				break;
			case 100://d
				printf("\n\n  ��������Ҫɾ��ѧ����ѧ��:");
				long long stuId;//��ɾ��ѧ����ѧ��
				scanf("%lld", &stuId);
				long long temp;
				printf("  ���ٴ�������Ҫɾ��ѧ����ѧ��:");
				scanf("%lld", &temp);
				if(temp != stuId)
				{
					printf("  ���������ѧ�Ų�һ��");
					getch();
					showCS(posClass , 0, db,  user);
					break;
				}
				Student* dStu = findStudent(db.students, stuId, 0, db.studentCount-1);//��ɾ����ѧ��
				if (!dStu) {
					printf("  ��ѧ���������������İ༶");
					getch();
					showCS(posClass , 0, db,  user);
					break;
				}
				else{
					//�ӿα���ȥ�����ſ�
					int i, j;
					for(i = 0;i < 7; i++)
					{
						for(j = 0; j < 7; j++)
						{
							if(dStu->classSheet[i][j] == CC->id) dStu->classSheet[i][j] = -1;
						}
					}
					//�ӿγ̰༶��ɾ����ѧ��
					for(i = 1; i <= CC->students[0]; i++)
					{
						if(CC->students[i] == stuId) break;
					}
					for(i = i; i <= CC->students[0]; i++)
					{
						CC->students[i] = CC->students[i+1];
					}
					CC->students[0] -= 1;
					showCS(posClass , 0, db,  user);
					break;
				}
				
		default:
			stayHere = 1;       
		}
	}
}

void resetInfo(Database db, Teacher* user){
	system("cls");
	cui_hideCursor();
	//չʾ�޸ĸ�����Ϣ��ѡ��
	cui_setFontStyle(0);						   // Ĭ����ʽ
	cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
	cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
	int y = 2;
	cui_putStringAt(2, y += 2, "[esc]�˳�ѡ��");
	cui_putStringAt(2, y += 2, "[1]�޸�����");
	cui_putStringAt(2, y += 2, "[2]�޸ĸ��˼��");
	cui_putStringAt(2, y += 2, "[3]�޸�����");
	cui_putStringAt(2, y += 2, "[4]��ѯ������Ϣ");
	//��ȡѡ��޸Ķ�Ӧ����
	char op;
	char content[1024];
	memset(content, '\0', sizeof(content));
	op = getch();
	cui_showCursor();
	switch (op)
	{
	case '\033':
		return ;
	case '1':
		printf("  ����������������:");
		scanf("%s", content);
		strcpy((*user).name, content);
		system("cls");
		printf("content %s\n", content);
		printf("  �޸ĳɹ�������������Ϊ��%s\n", (*user).name);
		getch();
		break;
	case '2':
		printf("  �����������¸��˼��:");
		gets(content);
		strcpy((*user).introduce, content);
		system("cls");
		printf("  �޸ĳɹ������Ľ���ΪΪ��%s\n", (*user).introduce);
		getch();
		break;
	case '3':
		printf("  ����������������:");
		cui_inputs(content, 32, '*');
		printf("\n  ������������������������:");
		char temp[1024];
		memset(temp, '\0', sizeof(temp));
		cui_inputs(temp, 32, '*');
		if(!strcmp(temp, content))
		{
			unsigned char psd[HASH_LEN];
			dc_hash32(content, 0, psd);
			memcpy((*user).key, psd, HASH_LEN);

			system("cls");
			printf("  �޸ĳɹ�����������ΪΪ��%s\n", content);
		}
		else
		{
			printf("  ��������������벢����ͬ����!");
			resetInfo(db, user);
		}
		getch();
		break;
	case '4':
		system("cls");
		printf("==================================================\n");
		printf("        ������Ϣ\n");
		printf("==================================================\n\n");
		printf("   ����Ϊ��%s\n\n", (*user).name);
		printf("   ���˼��Ϊ��%s\n\n", (*user).introduce);
		getch();
	default:
		break;
	}
}