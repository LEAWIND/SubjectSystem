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
	|- # data/
		|- blablabla.bin
		|- blablabla.txt
```

### 界面

使用[控制台虚拟终端序列](https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences)倾力打造。


