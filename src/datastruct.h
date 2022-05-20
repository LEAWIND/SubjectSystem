#pragma once

#define NAMELEN 100
struct node_period {
	struct node_period* next;
	int d;	// 课程班级的一个时间段
};
typedef struct node_period* node_period;

struct node_id {
	struct node_id* next;
	long long d;
};
typedef struct node_id* node_id;

// 学生
struct Student {
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
};

// 课程班级
struct CourseClass {
	long long id;		  //班级id
	int id_local;		  // 班级编号（XXX1班）
	node_period periods;  // 上课时间段们的带头节点的单链表
	long long teacherID;  // 老师ID
	node_id students;	  // 学生们
	int size;			  // 班级容量
};

// 课程
struct Course {
	long long id;
	char name[NAMELEN];
	long long CourseClasses[16];  //课程班级们
	int availableTime;			  // 开课时间 (1:大一上|2:大一下|3:大二上|4:大二下)
};
// 老师
struct Teacher {
	long long id;
	char key[32];
	char name[NAMELEN];
	char introduce[1024];
	long long CourseClasses[10];
};
// 管理员
struct Administrator {
	long long id;
	char key[32];
};
