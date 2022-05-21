
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
void loadEntireDatabaseIfDare(Database* db, char* dir) {
	FILE* fp;
	char buff[50];
	{
		sprintf(buff, "%s/%s", dir, "student.dat");
		db->students = (Student*)malloc(sizeof(Student) * db->studentCount);
		fp = fopen(buff, "rb");
		if (fp) {
			db->studentCount = dc_loadArray(sizeof(Student), db->students, buff);
		} else {
			db->studentCount = 0;
		}
	}
	{
		sprintf(buff, "%s/%s", dir, "teacher.dat");
		db->teachers = (Teacher*)malloc(sizeof(Teacher) * db->teacherCount);
		fp = fopen(buff, "rb");
		if (fp) {
			db->teacherCount = dc_loadArray(sizeof(Teacher), db->teachers, buff);
		} else {
			db->teacherCount = 0;
		}
	}
	{
		sprintf(buff, "%s/%s", dir, "admin.dat");
		db->admins = (Admin*)malloc(sizeof(Admin) * db->adminCount);
		fp = fopen(buff, "rb");
		if (fp) {
			db->adminCount = dc_loadArray(sizeof(Admin), db->admins, buff);
		} else {
			db->adminCount = 0;
		}
	}
	{
		sprintf(buff, "%s/%s", dir, "courseClass.dat");
		db->courseClasses = (CourseClass*)malloc(sizeof(CourseClass) * db->ccCount);
		fp = fopen(buff, "rb");
		if (fp) {
			db->ccCount = dc_loadArray(sizeof(CourseClass), db->courseClasses, buff);
		} else {
			db->ccCount = 0;
		}
	}
	{
		sprintf(buff, "%s/%s", dir, "course.dat");
		db->courses = (Course*)malloc(sizeof(Course) * db->courseCount);
		fp = fopen(buff, "rb");
		if (fp) {
			db->courseCount = dc_loadArray(sizeof(Course), db->courses, buff);
		} else {
			db->courseCount = 0;
		}
	}
}

// 保存数据
void saveEntireDatabase(Database db, char* dir) {
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

// TODO 导入原始数据
// (dirPath 原始数据文件夹)
void dc_importRawData(char* dirPath){

};