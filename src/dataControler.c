#pragma once
#define STRANGE_NUMBER 100
#include "dataControler.h"

void dc_test_sprintByte(unsigned char* b, char* dst) {
	for (int i = 0; i < 8; i++)
		dst[i] = *b & (1 << (7 - i)) ? '1' : '0';
}

// 哈希函数
void dc_hash32(const void* src, int len, void* dst) {
	memset(dst, 0, HASH_LEN);
	if (!len)
		len = strlen(src);
	const int StrangeVariable = 8;
	// Generated by python
	//  f = lambda:('0x'+("0%x" % int(random.random() * 256))[-2:])
	// ",".join([f() for i in range(32)])
	unsigned char fillers[][HASH_LEN] = {
		{0x0a, 0xb9, 0x0e, 0xdd, 0x25, 0x5e, 0xf6, 0xda,
		 0x44, 0xf5, 0xd2, 0xdd, 0x19, 0x96, 0x1e, 0xe2,
		 0xaf, 0xa4, 0x7d, 0x25, 0x58, 0x46, 0x59, 0x23,
		 0x34, 0xa7, 0x2a, 0xb8, 0x26, 0xd5, 0x9c, 0x69},  // 0
		{0x19, 0xd0, 0x70, 0x92, 0x23, 0xaa, 0x83, 0x21,
		 0x20, 0x3f, 0xdb, 0xf5, 0x24, 0xdd, 0x81, 0x9e,
		 0xfd, 0x5b, 0x0d, 0x4c, 0xf8, 0x1e, 0x29, 0x64,
		 0x58, 0xd3, 0xb0, 0x08, 0x96, 0xbb, 0x19, 0x3e},  // 1
		{0x5e, 0x7d, 0x7c, 0x18, 0x82, 0xd0, 0x06, 0xb0,
		 0x40, 0xa9, 0xef, 0xb1, 0x3b, 0xa2, 0x53, 0xfe,
		 0x4a, 0xd3, 0xbd, 0xdf, 0xe0, 0x83, 0x57, 0x99,
		 0x39, 0x69, 0x61, 0x0e, 0x8a, 0xc3, 0x45, 0xf1},  // 2
		{0x0e, 0x75, 0xc8, 0x04, 0xc1, 0xc1, 0xa4, 0x22,
		 0x9f, 0xb5, 0x80, 0x41, 0x0d, 0xaa, 0x4b, 0x92,
		 0x40, 0x66, 0x67, 0x41, 0xb5, 0x5d, 0x30, 0x2c,
		 0x50, 0x64, 0x41, 0x69, 0xdd, 0x55, 0xcd, 0x3b},  // 3
		{0xc4, 0x25, 0x1e, 0xe5, 0x5c, 0x32, 0xe5, 0x8b,
		 0x04, 0x77, 0xca, 0x5a, 0x5c, 0x9b, 0x82, 0x22,
		 0x42, 0x7b, 0x58, 0xe5, 0x6f, 0xbd, 0x81, 0xf7,
		 0xc9, 0xa2, 0x53, 0x3d, 0x10, 0x29, 0xb6, 0x8c},  // 4
		{0x74, 0xeb, 0xc4, 0xfb, 0xaa, 0xd0, 0xc9, 0xc5,
		 0xcc, 0xba, 0xde, 0x45, 0xfd, 0x08, 0x83, 0x4a,
		 0xd8, 0x2c, 0x0c, 0xf8, 0xd5, 0xb3, 0xb5, 0x5c,
		 0xd1, 0x93, 0x72, 0x56, 0x1e, 0x7d, 0xd3, 0x41},  // 5
		{0x35, 0x2e, 0xd4, 0x98, 0x8a, 0xf2, 0xd1, 0xcf,
		 0x18, 0x9b, 0x40, 0x23, 0xb9, 0xfd, 0xb4, 0xda,
		 0x63, 0x8a, 0x36, 0xd4, 0xd4, 0xd0, 0x44, 0xba,
		 0x1c, 0x29, 0x3c, 0xef, 0x29, 0x44, 0xec, 0xdc},  // 6
		{0x93, 0xdb, 0x74, 0xbf, 0xd5, 0xb4, 0x61, 0xa9,
		 0x02, 0xb9, 0x88, 0x52, 0x5c, 0xfc, 0x50, 0x33,
		 0xb4, 0x0e, 0x5b, 0x72, 0x67, 0xbb, 0x2c, 0x92,
		 0xba, 0x6c, 0xa2, 0xb0, 0xe3, 0xb0, 0x5e, 0x38},  // 7
	};

	int d = 0x2B;
	for (unsigned char i = 0; i < len; i++)
		d += ((unsigned char*)src)[i];
	d %= StrangeVariable;

	unsigned char buff[HASH_LEN];
	memset(buff, 0, HASH_LEN);
	// 将源数据分成 n 段，每段长度 HASH_LEN Bytes，最后一段可能不完整

	// 遍历每一段
	for (int i = 0; i < len; i += HASH_LEN) {
		int s = (len - i <= HASH_LEN) ? len % HASH_LEN : HASH_LEN;	// 该段的长度

		memcpy(buff, (unsigned char*)src + i, s);  // 将源数据写进缓存
		if (s != HASH_LEN)
			memcpy(buff + s, fillers[d] + s, HASH_LEN - s);	 // 用 filler 填充剩余部分

		for (int j = 0; j < HASH_LEN; j++)
			((unsigned char*)dst)[j] ^= buff[j];  // 异或操作
		d = (d + 1) % StrangeVariable;
	}
}
void dc_test_hash32() {
	char* samples[] = {
		"01",
		"123456789",
		"023456789",
		"abcdefg",
		"abcdefh",
		"abcdefi",
		"wofijwa093j0909f09qjfr09ewr0wrj90q3rf9-i309ri409309rif3290ir93",
	};
	int len = 7;
	char buff[HASH_LEN];
	char buff_B[9] = {[8] = 0};
	for (int i = 0; i < len; i++) {
		printf("[%s]\n", samples[i]);
		dc_hash32(samples[i], 0, buff);
		for (int j = 0; j < HASH_LEN / 16; j++) {
			printf("\t");
			for (int k = 0; k < 16; k++) {
				{
					// 2 进制输出
					dc_test_sprintByte(buff + j * 16 + k, buff_B);
					printf("%s ", buff_B);
				}
				// 16 进制输出
				// printf("%2x ", *((unsigned char*)(buff + j * 16 + k)));
			}
			printf("\n");
		}
	}
}

// 加载类型数组
int dc_loadArray(int elementSize, void* p, char* fpath) {
	FILE* fp = fopen(fpath, "rb");
	int len;
	fread(&len, sizeof(int), 1, fp);  // 读取元素数量
	fread(p, elementSize, len, fp);	  // 读取所有元素
	fclose(fp);
	return len;
}

// 保存类型数组
void dc_saveArray(int elementSize, void* p, int plen, char* fpath) {
	FILE* fp = fopen(fpath, "wb");
	int s = plen;
	fwrite(&s, sizeof(int), 1, fp);	   // 写入元素数量
	fwrite(p, elementSize, plen, fp);  // 写入所有元素
	fclose(fp);
}

// 加载数据
Database dc_loadEntireDatabaseIfDare(char* dir) {
	// TODO 确保文件夹存在
	FILE* fp;
	Database db;
	int flag_fileNotFound;
	char buff[50];
	{
		// TODO 学生
		sprintf(buff, "%s/%s", dir, "student.dat");	 // 计算文件路径
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.studentCount), sizeof(int), 1, fp);						// 读入元素数量
			db.students = (Student*)malloc(sizeof(Student) * (db.studentCount + STRANGE_NUMBER));  // 申请内存
			fread(db.students, sizeof(Student), db.studentCount, fp);			// 读取所有元素
		} else {
			db.studentCount = 0;
		}
		fclose(fp);
	}
	{
		// 教师
		sprintf(buff, "%s/%s", dir, "teacher.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.teacherCount), sizeof(int), 1, fp);						// 读入元素数量
			db.teachers = (Teacher*)malloc(sizeof(Teacher) * (db.teacherCount + STRANGE_NUMBER));  // 申请内存
			fread(db.teachers, sizeof(Teacher), db.teacherCount, fp);			// 读取所有元素
		} else {
			db.teacherCount = 0;
		}
		fclose(fp);
	}
	{
		// 管理??
		sprintf(buff, "%s/%s", dir, "admin.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.adminCount), sizeof(int), 1, fp);				// 读入元素数量
			db.admins = (Admin*)malloc(sizeof(Admin) * (db.adminCount + STRANGE_NUMBER));  // 申请内存
			fread(db.admins, sizeof(Admin), db.adminCount, fp);			// 读取所有元素
		} else {
			db.adminCount = 0;
		}
		fclose(fp);
	}
	{
		// 课程
		sprintf(buff, "%s/%s", dir, "course.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.courseCount), sizeof(int), 1, fp);
			db.courses = (Course*)malloc(sizeof(Course) * (db.courseCount + STRANGE_NUMBER));
			fread(db.courses, sizeof(Course), db.courseCount, fp);
		} else {
			db.courseCount = 0;
		}
		fclose(fp);
	}
	{
		// 课程班级
		sprintf(buff, "%s/%s", dir, "courseClass.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.ccCount), sizeof(int), 1, fp);
			db.courseClasses = (CourseClass*)malloc(sizeof(CourseClass) * (db.ccCount + STRANGE_NUMBER));
			fread(db.courseClasses, sizeof(CourseClass), db.ccCount, fp);
		} else {
			db.ccCount = 0;
		}
		fclose(fp);
	}
	return db;
}

// 保存数据
void dc_saveEntireDatabase(Database db, char* dir) {
	char buff[50];
	sprintf(buff, "%s/%s", dir, "student.dat");							// 计算文件路径
	dc_saveArray(sizeof(Student), db.students, db.studentCount, buff);	// 保存
	sprintf(buff, "%s/%s", dir, "teacher.dat");							// 计算文件路径
	dc_saveArray(sizeof(Teacher), db.teachers, db.teacherCount, buff);	// 保存
	sprintf(buff, "%s/%s", dir, "admin.dat");
	dc_saveArray(sizeof(Admin), db.admins, db.adminCount, buff);
	sprintf(buff, "%s/%s", dir, "courseClass.dat");
	dc_saveArray(sizeof(CourseClass), db.courseClasses, db.ccCount, buff);
	sprintf(buff, "%s/%s", dir, "course.dat");
	dc_saveArray(sizeof(Course), db.courses, db.courseCount, buff);
}

// 导入原始数据
void dc_importRawData(Database* db, char* dirPath) {
	// TODO 确保文件夹存在
	char buff[64];
	FILE* fp;
	int d;
	// 学生
	{
		sprintf(buff, "%s/%s", dirPath, "student.txt");	 // 计算路径
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->studentCount));								  // 学生数量
			db->students = (Student*)malloc(sizeof(Student) * db->studentCount);  // 申请内存
			for (int i = 0; i < db->studentCount; i++) {
				fscanf(fp, "%lld", &(db->students[i].id));	// 1. 学生 ID
				{											// 2. 密码
					char buff_passwd[32];					// 用于密码 hash
					memset(buff_passwd, 0, 32);
					fscanf(fp, "%s", buff_passwd);
					dc_hash32(buff_passwd, 0, &(db->students[i].key));
				}
				fscanf(fp, "%s", &(db->students[i].name));		 // 3. 名字
				fscanf(fp, "%s", &(db->students[i].class_pro));	 // 4. 专业班级
				// 5.$课表
				for (int i = 0; i < 7; i++) {	   // 一天 7 节课
					for (int j = 0; j < 7; j++) {  // 一周 7 天
						long long tp;
						fscanf(fp, "%lld", &tp);
						db->students[i].classSheet[j][i] = tp;
					}
				}
				fscanf(fp, "%d", &(db->students[i].college));  // 学院
				fscanf(fp, "%d", &(db->students[i].points));   // 已修学分

				// printf("%lld\n", db->students[i].id);
			}
			fclose(fp);
		}
		if (1) {
			printf("students.length = %d\n", db->studentCount);
			for (int i = 0; i < db->studentCount; i++) {
				Student* stu = db->students + i;
				printf("i=%5d, .id=%lld\n", i, stu->id);
			}
			getch();
		}
	}
	// 教师
	{
		sprintf(buff, "%s/%s", dirPath, "teacher.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->teacherCount));								  // 教师数量
			db->teachers = (Teacher*)malloc(sizeof(Teacher) * db->teacherCount);  //申请内存
			for (int i = 0; i < db->teacherCount; i++) {
				fscanf(fp, "%lld", &(db->teachers[i].id));	// 教师 ID
				{											// 密码
					char buff_passwd[32];
					memset(buff_passwd, 0, 32);
					fscanf(fp, "%s", buff_passwd);
					dc_hash32(buff_passwd, 0, &(db->teachers[i].key));
				}

				fscanf(fp, "%s", &(db->teachers[i].name));			// 名字
				fscanf(fp, "%s", &(db->teachers[i].introduce));		// 简介
				fscanf(fp, "%lld", db->teachers[i].CourseClasses);	// 课程班级数量
				for (int j = 0; j < db->teachers[i].CourseClasses[0]; j++)
					fscanf(fp, "%lld", db->teachers[i].CourseClasses + j + 1);	// 课程班级 ID

				// printf("%s\n", db->teachers[i].introduce);
				// printf("%lld\n", db->teachers[i].CourseClasses[0]);
			}
			fclose(fp);
		}
	}
	// 管理员
	{
		sprintf(buff, "%s/%s", dirPath, "admin.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->adminCount));						  // 管理员数量
			db->admins = (Admin*)malloc(sizeof(Admin) * db->adminCount);  // 申请内存
			for (int i = 0; i < db->adminCount; i++) {
				fscanf(fp, "%lld", &(db->admins[i].id));  // 管理员 ID

				{  // 密码
					char buff_passwd[32];
					memset(buff_passwd, 0, 32);
					fscanf(fp, "%s", buff_passwd);
					dc_hash32(buff_passwd, 0, &(db->admins[i].key));  // 保存 hash 值
				}

				// printf("%lld\n", db->admins[i].id);
			}
			fclose(fp);
		}
	}
	// 课程
	{
		sprintf(buff, "%s/%s", dirPath, "course.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->courseCount));							  // 课程数量
			db->courses = (Course*)malloc(sizeof(Course) * db->courseCount);  // 申请内存
			for (int i = 0; i < db->courseCount; i++) {
				fscanf(fp, "%lld", &(db->courses[i].id));  // 课程 ID
				fscanf(fp, "%s", &(db->courses[i].name));  // 课程名称
				fscanf(fp, "%d", &(db->courses[i].availableTime));	// 可以选该课的学期
				fscanf(fp, "%d", &(db->courses[i].college));		// 所属学院
				fscanf(fp, "%d", &(db->courses[i].point));			// 课程学分

				// printf("%lld\n", db->courses[i].id);
				// printf("%s\n", db->courses[i].name);
			}
			fclose(fp);
		}
	}
	// 课程班级
	{
		sprintf(buff, "%s/%s", dirPath, "courseClass.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->ccCount));  //课程班级数量
			db->courseClasses = (CourseClass*)malloc(sizeof(CourseClass) * db->ccCount);
			for (int i = 0; i < db->ccCount; i++) {
				fscanf(fp, "%lld", &(db->courseClasses[i].id));			//课程班级 ID
				fscanf(fp, "%d", &(db->courseClasses[i].id_local));		// 本地 ID
				fscanf(fp, "%lld", &(db->courseClasses[i].course));		//课程 ID
				fscanf(fp, "%lld", &(db->courseClasses[i].teacherID));	// 老师 ID

				fscanf(fp, "%d", db->courseClasses[i].periods);	 // 时间段数量
				for (int j = 0; j < db->courseClasses[i].periods[0]; j++)
					fscanf(fp, "%d", db->courseClasses[i].periods + j + 1);	 // 时间段

				fscanf(fp, "%lld", db->courseClasses[i].students);	// 已加入的学生数量
				for (int j = 0; j < db->courseClasses[i].students[0]; j++)
					fscanf(fp, "%lld", db->courseClasses[i].students + j + 1);	// 学生 ID
				fscanf(fp, "%s", db->courseClasses[i].room);					// 教室
				fscanf(fp, "%d", &(db->courseClasses[i].capacity));				//  容纳最大学生数

				// printf("课程班级: id=%lld, course=%lld\n", db->courseClasses[i].id, db->courseClasses[i].course);
			}
			fclose(fp);
		}
	}
	if (0) {
		int summer = 0;
		// 遍历课程
		for (int i = 0; i < db->courseCount; i++) {
			Course* course = db->courses + i;
			CourseClass* ccs[300];
			int ccslen = dc_searchCourseClasses(db, course, ccs);
			// printf("课程: id=%3lld ccslen=[%2d] anme=%s\n", course->id, ccslen, course->name);
		}
	}
	getch();
};

// 检查管理员账号密码是否正确
int dc_checkAdminLogin(Database db, long long account, char* passwd, Admin** user) {
	unsigned char psd[HASH_LEN];
	dc_hash32(passwd, 0, psd);
	for (int i = 0; i < db.adminCount; i++) {
		Admin adm = db.admins[i];
		if (adm.id == account && !memcmp(psd, adm.key, HASH_LEN))
		{
			*user = &(db.admins[i]);
			return 1;
		}
			
	}
	return 0;
}

// 检查学生账号密码是否正确，如果正确则返回其地址
Student* dc_checkStudentLogin(Database db, long long account, char* passwd) {
	unsigned char psd[HASH_LEN];
	dc_hash32(passwd, 0, psd);
	for (int i = 0; i < db.studentCount; i++) {
		Student stu = db.students[i];
		if (stu.id == account && !memcmp(psd, stu.key, HASH_LEN))
			return db.students + i;
	}
	return NULL;
}

// 检查教师账号密码是否正确
int dc_checkTeacherLogin(Database db, long long account, char* passwd, Teacher** user) {
	unsigned char psd[HASH_LEN];
	dc_hash32(passwd, 0, psd);
	for (int i = 0; i < db.teacherCount; i++) {
		Teacher tea = db.teachers[i];
		if (tea.id == account && !memcmp(psd, tea.key, HASH_LEN)) {
			*user = &db.teachers[i];
			return 1;
		}
	}
	return 0;
}

// 搜索 课程 对应的所有 课程班级
int dc_searchCourseClasses(Database* db, Course* course, CourseClass** result) {
	int len = 0;
	// 在课程班级中搜索
	for (int i = 0; i < db->ccCount; i++) {
		CourseClass* cc = db->courseClasses + i;
		if (cc->course == course->id) {
			if (result)
				result[len] = cc;
			len++;
		}
	}
	return len;
}
// 根据 id 获取教师
Teacher* ds_getTeacherById(Database* db, long long id) {
	for (int i = 0; i < db->teacherCount; i++)
		if (db->teachers[i].id == id)
			return db->teachers + i;
	return NULL;
}

// 根据 id 获取学生
Student* ds_getStudentById(Database* db, long long id) {
	for (int i = 0; i < db->studentCount; i++)
		if (db->students[i].id == id)
			return db->students + i;
	return NULL;
}

// 根据 id 获取课程
Course* ds_getCourseById(Database* db, long long id) {
	for (int i = 0; i < db->courseCount; i++)
		if (db->courses[i].id == id)
			return db->courses + i;
	return NULL;
}

// 根据 id 获取课程班级
CourseClass* ds_getCourseClassById(Database* db, long long id) {
	for (int i = 0; i < db->ccCount; i++)
		if (db->courseClasses[i].id == id)
			return db->courseClasses + i;
	return NULL;
}