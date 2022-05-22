#include "main.h"

int main(int argc, char* argv[]) {
	system("chcp 65001");  // 设置字符编码: UTF-8
	// 读取数据
	Database database = loadEntireDatabaseIfDare(DATA_DIR);

	system("cls");
	char userType = page_getUserType();

	switch (userType) {
		case '1':
			startStudentModule();
			break;
		case '2':
			startTeatureModule();
			break;
		case '3':
			startAdminModule();
			break;
		case '\033':  // Esc
			system("cls");
			printf("拜拜了您嘞\n");
			break;
	}
	saveEntireDatabase(database, DATA_DIR);
	system("pause");
	return 0;
}
