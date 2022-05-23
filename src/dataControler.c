#pragma once

// 加载数据
int dc_loadArray(int elementSize, void* p, char* fpath) {
	FILE* fp = fopen(fpath, "rb");
	int len;
	fread(&len, sizeof(int), 1, fp);  // 读取元素数量
	fread(p, elementSize, len, fp);	  // 读取所有元素
	fclose(fp);
	return len;
}

// 保存数据
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
		// 学生
		sprintf(buff, "%s/%s", dir, "student.dat");	 // 计算文件路径
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.studentCount), sizeof(int), 1, fp);						// 读入元素数量
			db.students = (Student*)malloc(sizeof(Student) * db.studentCount);	// 申请内存
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
			db.teachers = (Teacher*)malloc(sizeof(Teacher) * db.teacherCount);	// 申请内存
			fread(db.teachers, sizeof(Teacher), db.teacherCount, fp);			// 读取所有元素
		} else {
			db.teacherCount = 0;
		}
		fclose(fp);
	}
	{
		// 管理员
		sprintf(buff, "%s/%s", dir, "admin.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.adminCount), sizeof(int), 1, fp);				// 读入元素数量
			db.admins = (Admin*)malloc(sizeof(Admin) * db.adminCount);	// 申请内存
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
			db.courses = (Course*)malloc(sizeof(Course) * db.courseCount);
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
			db.courseClasses = (CourseClass*)malloc(sizeof(CourseClass) * db.ccCount);
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
				fscanf(fp, "%lld", &(db->students[i].id));		 // 学生 ID
				fscanf(fp, "%s", &(db->students[i].key));		 // 密码
				fscanf(fp, "%s", &(db->students[i].name));		 // 名字
				fscanf(fp, "%s", &(db->students[i].class_pro));	 // 专业班级
				fscanf(fp, "%d", &(db->students[i].college));	 // 学院
				fscanf(fp, "%d", &(db->students[i].points));	 // 已修学分

				// printf("%lld\n", db->students[i].id);
			}
			fclose(fp);
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
				fscanf(fp, "%lld", &(db->teachers[i].id));			// 教师 ID
				fscanf(fp, "%s", &(db->teachers[i].key));			// 密码
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
				fscanf(fp, "%s", &(db->admins[i].key));	  // 密码

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
				fscanf(fp, "%lld", &(db->courses[i].id));			  // 课程 ID
				fscanf(fp, "%s", &(db->courses[i].name));			  // 课程名称
				// fscanf(fp, "%lld", &(db->courses[i].CourseClasses));  // 该课程对应的课程班级数量
				// for (int j = 0; j < db->courses[i].CourseClasses[0]; j++)
				// 	fscanf(fp, "%lld", db->courses[i].CourseClasses + j + 1);  // 课程班级
				fscanf(fp, "%d", &(db->courses[i].availableTime));			   // 可以选该课的学期
				fscanf(fp, "%d", &(db->courses[i].college));				   // 所属学院
				fscanf(fp, "%d", &(db->courses[i].point));					   // 课程学分

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
				fscanf(fp, "%lld", &(db->courseClasses[i].course));		//课程
				fscanf(fp, "%lld", &(db->courseClasses[i].teacherID));	// 老师 ID

				fscanf(fp, "%d", db->courseClasses[i].periods);	 // 时间段数量
				for (int j = 0; j < db->courseClasses[i].periods[0]; j++)
					fscanf(fp, "%d", db->courseClasses[i].periods + j + 1);	 // 时间段

				fscanf(fp, "%lld", db->courseClasses[i].students);	// 已加入的学生数量
				for (int j = 0; j < db->courseClasses[i].students[0]; j++)
					fscanf(fp, "%lld", db->courseClasses[i].students + j + 1);	// 学生 ID
				fscanf(fp, "%s", db->courseClasses[i].room);					// 教室

				// printf("%s\n", db->courseClasses[i].room);
			}
			fclose(fp);
		}
	}
};

// 检查管理员账号密码是否正确
int dc_checkAdminLogin(Database db, long long account, char* passwd) {
	for (int i = 0; i < db.adminCount; i++) {
		Admin adm = db.admins[i];
		if (adm.id == account && !strcmp(passwd, adm.key))
			return 1;
	}
	return 0;
}

// 检查学生账号密码是否正确
int dc_checkStudentLogin(Database db, long long account, char* passwd) {
	for (int i = 0; i < db.studentCount; i++) {
		Student stu = db.students[i];
		if (stu.id == account && !strcmp(passwd, stu.key))
			return 1;
	}
	return 0;
}
// 检查教师账号密码是否正确
int dc_checkTeacherLogin(Database db, long long account, char* passwd) {
	for (int i = 0; i < db.teacherCount; i++) {
		Teacher tea = db.teachers[i];
		if (tea.id == account && !strcmp(passwd, tea.key))
			return 1;
	}
	return 0;
}
