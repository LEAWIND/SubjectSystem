#pragma once

#define NAMELEN 100
#define HASH_LEN 32		   // 密码哈希值长度
#define PERIODS_PER_DAY 7  // 一天几个上课时间段
char* colleges[] = {
	"-1,"				   // 0
	"中国语言文学系",	   // 1
	"体育教研部",		   // 2
	"信息科学技术学院",	   // 3
	"北京大学教务部",	   // 4
	"历史学系",			   // 5
	"城市与环境学院",	   // 6
	"外国语学院",		   // 7
	"工学院",			   // 8
	"心理与认知科学学院",  // 9
	"教育学院",			   // 0
	"新闻与传播学院",	   // 1
	"物理学院",			   // 2
	"环境科学与工程学院",  // 3
	"生命科学学院",		   // 4
	"社会学系",			   // 5
	"经济学院",			   // 6
	"英语语言文学系"	   // 7
};

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
	long long classSheet[7][PERIODS_PER_DAY];
	// 学院
	char college;
	char totPoint;	//可选总学分
	// 当前总学分
	int points;
} Student;

// 课程班级
typedef struct CourseClass {
	long long id;			  // 班级id
	int id_local;			  // 班级编号（某某某1班、某某某2班）
	long long course;		  // 课程id
	long long teacherID;	  // 老师ID
	int periods[49];		  // 上课时间段们
	long long students[100];  // 学生们ID
	char room[10];			  //上课的教室
} CourseClass;

// 课程
typedef struct Course {
	long long id;
	char name[NAMELEN];
	long long CourseClasses[16];  //课程班级们的id
	int availableTime;			  // 开课学期 (1:大一上|2:大一下|3:大二上|4:大二下|5678)
	int college;				  //所属的学院，-1代表公选
	int point;					  // 学分
} Course;

// 老师
typedef struct Teacher {
	long long id;
	char key[32];
	char name[NAMELEN];
	char introduce[1024];
	long long CourseClasses[10];  // 教授哪些课程班级

} Teacher;

// 管理员
typedef struct Admin {
	long long id;
	char key[32];
} Admin;
