#include "main.h"
int test() {
	system("cls");
	getch();
	return 0;
}
int main(int argc, char* argv[]) {
	// printf("\033[47m\033[30m");
	system("color F0");
	// return test();
	if (argc > 1)
		SetCurrentDirectory(argv[1]);

	// ���Լ��ض���������
	Database database = dc_loadEntireDatabaseIfDare(DATA_DIR);
	if (!database.studentCount)
		dc_importRawData(&database, "data/raw");  // ��������
	char stayHere = 1;

	int i;
	for(i = 0; i < 100; i++) printf("%d:%lld\n",i, database.students[i].id);

	while (stayHere) {
		system("cls");						 // ��ջ�����
		char userType = page_getUserType();	 // �����û�����ѡ�����
		system("cls");
		switch (userType) {
			case '1':
				startStudentModule(database);  // ѧ��
				break;
			case '2':
				system("color F0");
				startTeacherModule(database);  //��ʦ
				break;
			case '3':
				system("color F0");
				startAdminModule(&database);  // ����Ա
				break;
			case '\033':  // Esc
				printf("�ݰ�������\n");
				stayHere = 0;
				break;
		}
	}
	dc_saveEntireDatabase(database, DATA_DIR);	// ��������
	system("pause");
	return 0;
}