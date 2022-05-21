#include "main.h"

// 加载数据
int loadEntireDatabaseIfDare() {
	FILE* fp;
	{
		students = (Student*)malloc(sizeof(Student) * studentCount);
		fp = fopen(FPATH_STUDENT, "rb");
		if (fp) {
			studentCount = dc_loadArray(sizeof(Student), students, FPATH_STUDENT);
		} else {
			studentCount = 0;
		}
	}
	{
		teachers = (Teacher*)malloc(sizeof(Teacher) * teacherCount);
		fp = fopen(FPATH_TEACHER, "rb");
		if (fp) {
			teacherCount = dc_loadArray(sizeof(Teacher), teachers, FPATH_TEACHER);
		} else {
			teacherCount = 0;
		}
	}
	{
		admins = (Admin*)malloc(sizeof(Admin) * adminCount);
		fp = fopen(FPATH_ADMIN, "rb");
		if (fp) {
			adminCount = dc_loadArray(sizeof(Admin), admins, FPATH_ADMIN);
		} else {
			adminCount = 0;
		}
	}
	{
		courseClasses = (CourseClass*)malloc(sizeof(CourseClass) * ccCount);
		fp = fopen(FPATH_COURSECLASS, "rb");
		if (fp) {
			ccCount = dc_loadArray(sizeof(Admin), admins, FPATH_ADMIN);
		} else {
			ccCount = 0;
		}
	}
	{
		courses = (Course*)malloc(sizeof(Course) * courseCount);
		fp = fopen(FPATH_COURSE, "rb");
		if (fp) {
			courseCount = dc_loadArray(sizeof(Course), courses, FPATH_COURSE);
		} else {
			courseCount = 0;
		}
	}
}

// 保存数据
int saveEntireDatabase() {
	dc_saveArray(sizeof(Student), students, studentCount, FPATH_STUDENT);
	dc_saveArray(sizeof(Teacher), teachers, teacherCount, FPATH_TEACHER);
	dc_saveArray(sizeof(Admin), admins, adminCount, FPATH_ADMIN);
	dc_saveArray(sizeof(CourseClass), courseClasses, ccCount, FPATH_COURSECLASS);
	dc_saveArray(sizeof(Course), courses, courseCount, FPATH_COURSE);
}

char page_getUserType() {
	system("cls");

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

int main(int argc, char* argv[]) {
	system("chcp 65001");  // 设置字符编码: UTF-8
	// 读取数据
	loadEntireDatabaseIfDare();
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
	saveEntireDatabase();
	system("pause");
	return 0;
}
