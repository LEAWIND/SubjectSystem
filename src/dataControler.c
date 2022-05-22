
int dc_loadArray(int elementSize, void* p, char* fpath) {
	FILE* fp = fopen(fpath, "rb");
	int len;
	fread(&len, sizeof(int), 1, fp);
	fread(p, elementSize, len, fp);
	fclose(fp);
	return len;
}

void dc_saveArray(int elementSize, void* p, int plen, char* fpath) {
	FILE* fp = fopen(fpath, "wb");
	int s = plen;
	fwrite(&s, sizeof(int), 1, fp);
	fwrite(p, elementSize, plen, fp);
	fclose(fp);
}

// 加载数据
Database dc_loadEntireDatabaseIfDare(char* dir) {
	FILE* fp;
	Database db;
	char buff[50];
	{
		sprintf(buff, "%s/%s", dir, "student.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.studentCount), sizeof(int), 1, fp);
			db.students = (Student*)malloc(sizeof(Student) * db.studentCount);
			fread(db.students, sizeof(Student), db.studentCount, fp);
		} else {
			db.studentCount = 0;
		}
		fclose(fp);
	}
	{
		sprintf(buff, "%s/%s", dir, "teacher.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.teacherCount), sizeof(int), 1, fp);
			db.teachers = (Teacher*)malloc(sizeof(Teacher) * db.teacherCount);
			fread(db.teachers, sizeof(Teacher), db.teacherCount, fp);
		} else {
			db.teacherCount = 0;
		}
		fclose(fp);
	}
	{
		sprintf(buff, "%s/%s", dir, "admin.dat");
		fp = fopen(buff, "rb");
		if (fp) {
			fread(&(db.adminCount), sizeof(int), 1, fp);
			db.admins = (Admin*)malloc(sizeof(Admin) * db.adminCount);
			fread(db.admins, sizeof(Admin), db.adminCount, fp);
		} else {
			db.adminCount = 0;
		}
		fclose(fp);
	}
	{
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
	sprintf(buff, "%s/%s", dir, "student.dat");
	dc_saveArray(sizeof(Student), db.students, db.studentCount, buff);
	sprintf(buff, "%s/%s", dir, "teacher.dat");
	dc_saveArray(sizeof(Teacher), db.teachers, db.teacherCount, buff);
	sprintf(buff, "%s/%s", dir, "admin.dat");
	dc_saveArray(sizeof(Admin), db.admins, db.adminCount, buff);
	sprintf(buff, "%s/%s", dir, "courseClass.dat");
	dc_saveArray(sizeof(CourseClass), db.courseClasses, db.ccCount, buff);
	sprintf(buff, "%s/%s", dir, "course.dat");
	dc_saveArray(sizeof(Course), db.courses, db.courseCount, buff);
}

// 导入原始数据
void dc_importRawData(Database* db, char* dirPath) {
	char buff[64];
	FILE* fp;
	int d;
	// Student
	{
		sprintf(buff, "%s/%s", dirPath, "student.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->studentCount));
			db->students = (Student*)malloc(sizeof(Student) * db->studentCount);
			for (int i = 0; i < db->studentCount; i++) {
				fscanf(fp, "%lld", &(db->students[i].id));
				fscanf(fp, "%s", &(db->students[i].key));
				fscanf(fp, "%s", &(db->students[i].name));
				fscanf(fp, "%s", &(db->students[i].class_pro));
				fscanf(fp, "%d", &(db->students[i].college));
				fscanf(fp, "%d", &(db->students[i].points));
				// printf("%lld\n", db->students[i].id);
			}
			fclose(fp);
		}
	}
	// Teacher
	{
		sprintf(buff, "%s/%s", dirPath, "teacher.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->teacherCount));
			db->teachers = (Teacher*)malloc(sizeof(Teacher) * db->teacherCount);
			for (int i = 0; i < db->teacherCount; i++) {
				fscanf(fp, "%lld", &(db->teachers[i].id));
				fscanf(fp, "%s", &(db->teachers[i].key));
				fscanf(fp, "%s", &(db->teachers[i].name));
				fscanf(fp, "%s", &(db->teachers[i].introduce));
				fscanf(fp, "%lld", db->teachers[i].CourseClasses);
				for (int j = 0; j < db->teachers[i].CourseClasses[0]; j++)
					fscanf(fp, "%lld", db->teachers[i].CourseClasses + j + 1);
				// printf("%s\n", db->teachers[i].introduce);
				// printf("%lld\n", db->teachers[i].CourseClasses[0]);
			}
			fclose(fp);
		}
	}
	// Admin
	{
		sprintf(buff, "%s/%s", dirPath, "admin.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->adminCount));
			db->admins = (Admin*)malloc(sizeof(Admin) * db->adminCount);
			for (int i = 0; i < db->adminCount; i++) {
				fscanf(fp, "%lld", &(db->admins[i].id));
				fscanf(fp, "%s", &(db->admins[i].key));
				// printf("%lld\n", db->admins[i].id);
			}
			fclose(fp);
		}
	}
	// Course
	{
		sprintf(buff, "%s/%s", dirPath, "course.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->courseCount));
			db->courses = (Course*)malloc(sizeof(Course) * db->courseCount);
			for (int i = 0; i < db->courseCount; i++) {
				fscanf(fp, "%lld", &(db->courses[i].id));
				fscanf(fp, "%s", &(db->courses[i].name));
				fscanf(fp, "%lld", &(db->courses[i].CourseClasses));
				for (int j = 0; j < db->courses[i].CourseClasses[0]; j++)
					fscanf(fp, "%lld", db->courses[i].CourseClasses + j + 1);
				fscanf(fp, "%d", &(db->courses[i].availableTime));
				fscanf(fp, "%d", &(db->courses[i].college));
				fscanf(fp, "%d", &(db->courses[i].point));
				// printf("%lld\n", db->courses[i].id);
				// printf("%s\n", db->courses[i].name);
			}
			fclose(fp);
		}
	}
	// Course Class
	{
		sprintf(buff, "%s/%s", dirPath, "courseClass.txt");
		fp = fopen(buff, "r");
		if (fp) {
			fscanf(fp, "%d", &(db->ccCount));
			db->courseClasses = (CourseClass*)malloc(sizeof(CourseClass) * db->ccCount);
			for (int i = 0; i < db->ccCount; i++) {
				fscanf(fp, "%lld", &(db->courseClasses[i].id));
				fscanf(fp, "%d", &(db->courseClasses[i].id_local));
				fscanf(fp, "%lld", &(db->courseClasses[i].course));
				fscanf(fp, "%lld", &(db->courseClasses[i].teacherID));

				fscanf(fp, "%d", db->courseClasses[i].periods);
				for (int j = 0; j < db->courseClasses[i].periods[0]; j++)
					fscanf(fp, "%d", db->courseClasses[i].periods + j + 1);

				fscanf(fp, "%lld", db->courseClasses[i].students);
				for (int j = 0; j < db->courseClasses[i].students[0]; j++)
					fscanf(fp, "%lld", db->courseClasses[i].students + j + 1);
				fscanf(fp, "%s", db->courseClasses[i].room);

				printf("%s\n", db->courseClasses[i].room);
			}
			fclose(fp);
		}
	}
};

int dc_checkAdminLogin(Database db, long long account, char* passwd) {
	for (int i = 0; i < db.adminCount; i++) {
		Admin adm = db.admins[i];
		if (adm.id == account && !strcmp(passwd, adm.key))
			return 1;
	}
	return 0;
}

int dc_checkStudentLogin(Database db, long long account, char* passwd) {
	for (int i = 0; i < db.studentCount; i++) {
		Student stu = db.students[i];
		if (stu.id == account && !strcmp(passwd, stu.key))
			return 1;
	}
	return 0;
}
int dc_checkTeacherLogin(Database db, long long account, char* passwd) {
	for (int i = 0; i < db.teacherCount; i++) {
		Teacher tea = db.teachers[i];
		if (tea.id == account && !strcmp(passwd, tea.key))
			return 1;
	}
	return 0;
}
