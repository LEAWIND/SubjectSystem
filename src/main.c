#include "main.h"

char page_getUserType() {
	system("cls");

	cui_clearRect(0, 0, us_width, us_height);
	cui_strokeRect(0, 0, us_width, us_height, 0);

	cui_putStringCenterAt(us_width / 2, 1, " 选 课 系 统 ", 0);
	cui_putStringAt(us_width / 2 - 14, 4, "1. 学生");
	cui_putStringAt(us_width / 2 - 14, 6, "2. 教师");
	cui_putStringAt(us_width / 2 - 14, 8, "3. 管理员");
	cui_putStringAt(us_width / 2 - 14, 10, "0. 退出");
	cui_putStringCenterAt(us_width / 2, 13, "请选择:[ ]", 0);
	cui_moveCursor(-2, 0);
	char ut = getchar();

	cui_fillRect(0, 0, us_width, us_height, ' ');

	return ut;
}

int startStudentModule() {
	system("cls");
	printf("student module\n");
}

int startTeatureModule() {
	system("cls");
	printf("teacher module\n");
}

int startAdminModule() {
	system("cls");
	printf("administrator module\n");
}

int main(int argc, char* argv[]) {
	system("chcp 65001");  // 字符编码: UTF-8
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
		case '0':
			system("cls");
			printf("拜拜了您嘞\n");
			break;
		default:
			break;
	}

	system("pause");
	return 0;
}