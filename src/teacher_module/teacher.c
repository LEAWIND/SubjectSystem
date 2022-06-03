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
	//user = db.teachers;
	startSection(db, user);
}

void startSection(Database db, Teacher* user){
	system("cls");
	int op;//�洢�û���ѡ��
	op = showMenuTeacher((*user).name);//��ȡ�û�ѡ��
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
		cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
		cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
		cui_putStringCenterAt(us_width/2, us_height/2, "����������ֲ�����Ҫ��", 0);
		getch();
		startSection(db, user);
		break;
	}
	startSection(db, user);
}

int showMenuTeacher(char *name){
	cui_setFontStyle(0);						   // Ĭ����ʽ
	cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
	cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
	int y = 2;
	// ���ع��
	cui_hideCursor();
	cui_putStringCenterAt(us_width / 2, y += 4, name, strlen(name));
	cui_putStringAt(2, y += 2, "[0]�˳���¼");
	cui_putStringAt(2, y += 2, "[1]����༶");
	cui_putStringAt(2, y += 2, "[2]�޸ĸ�����Ϣ");
	cui_putStringAt(2, y += 4, "������ѡ��");
	// �����û�����
	char ut;
	do {
		ut = getch();  // �޻�������
	} while (!strchr("012", ut));
	cui_showCursor();  // ��ʾ���
	// printf("\033[?1049l");
	int op = ut - 48;
	return op;
}


void manageClass(Database db, Teacher* user){
	system("cls");
	printf("���ѽ������༶ģ��");
}

void resetInfo(Database db, Teacher* user){
	system("cls");
	//չʾ�޸ĸ�����Ϣ��ѡ��
	cui_setFontStyle(0);						   // Ĭ����ʽ
	cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
	cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
	int y = 2;
	cui_putStringAt(2, y += 2, "[0]�˳�ѡ��");
	cui_putStringAt(2, y += 2, "[1]�޸�����");
	cui_putStringAt(2, y += 2, "[2]�޸ĸ��˼��");
	cui_putStringAt(2, y += 2, "[3]�޸�����");
	cui_putStringAt(2, y += 2, "[4]��ѯ������Ϣ");
	cui_putStringAt(2, y += 4, "������ѡ�");
	//��ȡѡ��޸Ķ�Ӧ����
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
		printf("  ����������������:");
		scanf("%s", content);

		// unsigned char sss[1024];
		// dc_test_sprintByte(content, sss);
		// printf("%s", sss);

		strcpy((*user).name, content);
		system("cls");
		printf("content %s\n", content);
		printf("  �޸ĳɹ�������������Ϊ��%s\n", (*user).name);
		getch();
		break;
	case 2:
		printf("  �����������¸��˼��:");
		gets(content);
		strcpy((*user).introduce, content);
		system("cls");
		printf("  �޸ĳɹ������Ľ���ΪΪ��%s\n", (*user).introduce);
		getch();
		break;
	case 3:
		printf("  ����������������:");
		scanf("%s", content);

		printf("  ������������������������:");
		char temp[1024];
		memset(temp, '\0', sizeof(temp));
		scanf("%s", temp);
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
	case 4:
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