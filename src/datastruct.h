#pragma once

#define NAMELEN 100		   // ������󳤶�
#define HASH_LEN 32		   // �����ϣֵ����
#define PERIODS_PER_DAY 7  // һ�켸���Ͽ�ʱ���

char* colleges[] = {
	"��ѡ",				   // 0
	"�й�������ѧϵ",	   // 1
	"�������в�",		   // 2
	"��Ϣ��ѧ����ѧԺ",	   // 3
	"������ѧ����",	   // 4
	"��ʷѧϵ",			   // 5
	"�����뻷��ѧԺ",	   // 6
	"�����ѧԺ",		   // 7
	"��ѧԺ",			   // 8
	"��������֪��ѧѧԺ",  // 9
	"����ѧԺ",			   // 10
	"�����봫��ѧԺ",	   // 11
	"����ѧԺ",			   // 12
	"������ѧ�빤��ѧԺ",  // 13
	"������ѧѧԺ",		   // 14
	"���ѧϵ",			   // 15
	"����ѧԺ",			   // 16
	"Ӣ��������ѧϵ"	   // 17
};

// ѧ��
typedef struct Student {
	long long id;							   // ID ǰ4λ������ѧ���
	char key[32];							   // �����ϣֵ
	char name[NAMELEN];						   // ����
	char class_pro[NAMELEN];				   // רҵ�༶
	long long classSheet[7][7];				   // �α�Ԫ��Ϊ �γ̰༶id��
	int college;							   // ѧԺ
	int points;								   // ��ǰ����ѧ��
} Student;

// �γ̰༶
typedef struct CourseClass {
	long long id;			  // �༶id
	int id_local;			  // �༶��ţ�ĳĳĳ1�ࡢĳĳĳ2�ࣩ
	long long course;		  // �γ�id
	long long teacherID;	  // ��ʦID
	int periods[49];		  // �Ͽ�ʱ�����
	long long students[100];  // ѧ����ID
	char room[10];			  // �ϿεĽ���
	int capacity;			  // �������ѧ����
	int isDeleted;			  // �Ƿ��Ѿ���ɾ��
} CourseClass;

// �γ�
typedef struct Course {
	long long id;		 // �γ� ID
	char name[NAMELEN];	 // �γ�����
	int availableTime;	 // ����ѧ�� (1:��һ��|2:��һ��|3:�����|4:�����|5678)
	int college;		 // ������ѧԺ��-1����ѡ
	int point;			 // ѧ��
	int isDeleted;		 // �Ƿ��Ѿ���ɾ��
} Course;

// ��ʦ
typedef struct Teacher {
	long long id;				  // ID
	char key[32];				  // ����
	char name[NAMELEN];			  // ����
	char introduce[1024];		  // ���
	long long CourseClasses[10];  // ������Щ�γ̰༶
	int isDeleted;				  // �Ƿ��Ѿ���ɾ��
} Teacher;

// ����Ա
typedef struct Admin {
	long long id;  // ID
	char key[32];  // ����
} Admin;
