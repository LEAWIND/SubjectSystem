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

	// 尝试加载二进制数据
	Database database = dc_loadEntireDatabaseIfDare(DATA_DIR);
	if (!database.studentCount)
		dc_importRawData(&database, "data/raw");  // 导入数据
	char stayHere = 1;
	while (stayHere) {
		system("cls");						 // 清空缓冲区
		char userType = page_getUserType();	 // 进入用户类型选择界面
		system("cls");
		switch (userType) {
			case '1':
				startStudentModule(database);  // 学生
				break;
			case '2':
				startTeacherModule(database);  //教师
				break;
			case '3':
				startAdminModule(database);	 // 管理员
				break;
			case '\033':  // Esc
				printf("拜拜了您嘞\n");
				stayHere = 0;
				break;
		}
	}
	dc_saveEntireDatabase(database, DATA_DIR);	// 保存数据
	system("pause");
	return 0;
}