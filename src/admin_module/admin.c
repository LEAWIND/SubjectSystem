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

void showCourses(Database *db, int page, int N)
{
	char* neStartTime[] = {"��һ��","��һ��","�����", "�����","������","������","������", "������"};
	printf("  �γ�ID  �γ�����                    ����ѧ��  ������ѧԺ        ѧ��\n");
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
		printf("\n\n  ���ͷ����һҳ  �Ҽ�ͷ����һҳ");
		//ƥ��ѡ��
		int c;
		c = getch();
		switch (c)
		{
			case 27://ESC
				stayHere = 0;
				break;
			case 49://��ӿγ�
				break;
			case 50://ɾ���γ�
				break;
			case 51://���ҿγ�
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

