# SubjectSystem

选课系统（数据结构综合课程设计作业）

## 编译选项

### 编译器版本

`gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0`

### 编译参数

```bat
cd %root%
gcc -fdiagnostics-color=always -std=c11 -g %root%/src/main.c -o %root%/bin/main.exe
```

## 项目结构 (# 代表添加进 gitignore)

```
|- root/
	|- #.vscode/
	|- src/
		|- main.c
		|- main.h
		|- teacher.h
		|- student.h
		|- administrator.h
		|- blablabla.h
	|- # bin/
		|- main.exe
	|- data/
		|- blablabla.bin
		|- blablabla.txt
```

## 功能划分

### 学生

* 查看自己的已选课程
* 查看自己的可选课程
* 给自己选课
* 查看自己任意课程班级的同学

### 老师

* 编辑自己的个人简介
* 查看自己任意班级的学生

### 管理员

* 增删改查课程
* 增删改查课程班级
