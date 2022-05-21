#pragma once

#define NAMELEN 100
#define HASH_LEN 32	 // 密码哈希值长度
#define PERIODS_PER_DAY	 // 一天几个上课时间段

// 学生
typedef struct Student {
	/*
	前4位代表入学年份，其他代表标识
	*/
	long long id;

	char key[32];  // 密码哈希值

	char name[NAMELEN];
	//专业班级
	char class_pro[NAMELEN];
	// 课表（元素为 课程班级id）
	long long classSheet[7][11];
} Student;

// 课程班级
typedef struct CourseClass {
	long long id;			  // 班级id
	int id_local;			  // 班级编号（某某某1班、某某某2班）
	long long course;		  // 课程id
	long long teacherID;	  // 老师ID
	int periods[49];		  // 上课时间段们
	long long students[100];  // 学生们ID
	char room[10];//上课的教室
} CourseClass;

// 课程
typedef struct Course {
	long long id;
	char name[NAMELEN];
	long long CourseClasses[16];  //课程班级们的id
	int availableTime;	// 开课学期 (1:大一上|2:大一下|3:大二上|4:大二下|5678)
} Course;

// 老师
typedef struct Teacher {
	long long id;
	char key[32];
	char name[NAMELEN];
	char introduce[1024];
	long long CourseClasses[10];  // 教授哪些课程

} Teacher;

// 管理员
typedef struct Admin {
	long long id;
	char key[32];
} Admin;
