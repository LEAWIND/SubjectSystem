#pragma once

// ��ҳ��ѡ���û����
char page_getUserType() {
	// printf("\033[?1049h");
	cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
	cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�
	// ���ع��
	cui_hideCursor();
	// ����һЩ�ı�
	cui_putStringCenterAt(us_width / 2, 1, " ѡ �� ϵ ͳ ", 0);
	int y = 2;
	cui_putStringAt(us_width / 2 - 18, y += 2, "�밴��:");
	cui_putStringAt(us_width / 2 - 14, y += 2, "1. ѧ��");
	cui_putStringAt(us_width / 2 - 14, y += 2, "2. ��ʦ");
	cui_putStringAt(us_width / 2 - 14, y += 2, "3. ����Ա");
	cui_putStringAt(us_width / 2 - 14, y += 2, "Esc. �˳�");
	// �����û�����
	char ut;
	do {
		ut = getch();  // �޻�������
	} while (!strchr("123\033", ut));
	cui_showCursor();  // ��ʾ���
	// printf("\033[?1049l");
	return ut;
}

void getVerificationCode(char verificationCode[], int n) {
	char str[] = "2323456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	// 0,1������ĸ��o���롮l'����������
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++)
		verificationCode[i] = str[rand() % 62];
	verificationCode[n] = '\0';
}

// ��¼ҳ�棺��ȡ�û�������˺ź�����ԭ��
void page_login(long long* account, char* passwd, char* info) {
	while (1) {
		system("cls");
		// cui_setFontStyle(0);						   // Ĭ����ʽ
		cui_clearRect(0, 0, us_width, us_height);	   // ��վ�������
		cui_strokeRect(0, 0, us_width, us_height, 0);  // ���Ʊ߿�

		int y = 3;
		// �����ı�
		cui_putStringCenterAt(us_width / 2, y += 2, info, strlen(info));

		cui_putStringAt(3, y += 2, "�˺�:________________");
		cui_moveCursor(-16, 0);
		// cui_setFontStyle(4);  // ���»���
		char buff[50];
		cui_inputs(buff, 49, 0);
		sscanf(buff, "%lld", account);
		cui_setFontStyle(24);  // �����»���

		cui_putStringAt(3, y += 2, "����:________________");
		cui_moveCursor(-16, 0);
		cui_setFontStyle(4);
		cui_inputs(passwd, 32, '*');  // ��������
		cui_setFontStyle(24);

		//��֤����֤
		char verificationCode[5];		//�����֤��
		char inputVerificationCode[5];	//�����û��������֤��
		getVerificationCode(verificationCode, 4);
		printf("\n\n   ��֤�룺            [%s]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", verificationCode);
		scanf("%s", inputVerificationCode);
		int flag = 1;
		if (strcmp(verificationCode, inputVerificationCode)) {
			system("cls");
			printf("��֤�����");
			getch();
			continue;
		}
		break;
	}
}