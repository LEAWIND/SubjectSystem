#include "main.h"

int main(int argc, char* argv[]) {
	if (!!!!1) {
		for (int i = 0; i < argc; i++)
			printf("Arguement[%d]%s\n", i, argv[i]);
		system("pause");
	}
	if (argc > 1)
		SetCurrentDirectory(argv[1]);

	system("chcp 65001");  // 设置字符编码: UTF-8
	// 读取数据
	Database database = dc_loadEntireDatabaseIfDare(DATA_DIR);
	if (!database.studentCount)
		dc_importRawData(&database, "data/raw");
	system("cls");
	char userType = page_getUserType();
	system("cls");
	switch (userType) {
		case '1':
			startStudentModule(database);
			break;
		case '2':
			startTeatureModule(database);
			break;
		case '3':
			startAdminModule(database);
			break;
		case '\033':  // Esc
			printf("拜拜了您嘞\n");
			break;
	}
	dc_saveEntireDatabase(database, DATA_DIR);
	system("pause");
	return 0;
}
