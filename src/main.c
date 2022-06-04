#include "main.h"
int test() {
	dc_test_hash32();

	getch();
	return 0;
}
int main(int argc, char* argv[]){
	// return test();
	if (argc > 1)
		SetCurrentDirectory(argv[1]);

	// ���Լ��ض���������
	Database database = dc_loadEntireDatabaseIfDare(DATA_DIR);
	if (!database.studentCount)
		dc_importRawData(&database, "data/raw");  // ��������
	char stayHere = 1;
	while (stayHere) {
		system("cls");						 // ��ջ�����
		char userType = page_getUserType();	 // �����û�����ѡ�����
		system("cls");
		switch (userType) {
			case '1':
				startStudentModule(database);  // ѧ��
				break;
			case '2':
				startTeacherModule(database);  //��ʦ
				break;
			case '3':
				startAdminModule(database);	 // ����Ա
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