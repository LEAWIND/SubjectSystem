#include "main.h"

char page_getUserType() {
	cui_clearRect(0, 0, us_width, us_height);
	cui_strokeRect(0, 0, us_width, us_height, 0);

	cui_putStringCenterAt(us_width / 2, 1, " 选 课 系 统 ", 0);
	int y = 2;
	cui_putStringAt(us_width / 2 - 18, y += 2, "请按键:");
	cui_putStringAt(us_width / 2 - 14, y += 2, "1. 学生");
	cui_putStringAt(us_width / 2 - 14, y += 2, "2. 教师");
	cui_putStringAt(us_width / 2 - 14, y += 2, "3. 管理员");
	cui_putStringAt(us_width / 2 - 14, y += 2, "Esc. 退出");
	cui_hideCursor();
	char ut;
	do {
		ut = getch();
	} while (!strchr("123\033", ut));
	cui_showCursor();
	return ut;
}

void page_login(long long account, char* passwd) {
}
int main(int argc, char* argv[]) {
	system("chcp 65001");  // 设置字符编码: UTF-8
	// 读取数据
	Database database;
	loadEntireDatabaseIfDare(&database, DATA_DIR);
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
