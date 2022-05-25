#导入模块
import xlwt
import xlrd
import random

availableId = 1

mapMajor = {
    "建筑学院":["建筑系","城市规划系,建筑技术科学系"]
}
#生成课程信息
def generateCouse():
    #可供使用的课程及学院对应表
    book = xlrd.open_workbook("course.xls")
    print("The number of worksheets is {0}".format(book.nsheets))#表格的数目
    print("Worksheet name(s): {0}".format(book.sheet_names()))#表格的名字
    sh = book.sheet_by_index(0)#第一张表格
    print("{0} {1} {2}".format(sh.name, sh.nrows, sh.ncols))#表格的数和列数
    print("Cell D30 is {0}".format(sh.cell_value(rowx=29, colx=3)))

    courses = []#用于保存可供使用的课程及学院对应表 (课程名称，所属学院，学分)
    collegs = []#学院
    notACollege = ['北京大学中国社会科学调查中心', '国家发展研究院', '地球与空间科学学院', "现代农学院"]

    for rx in range(1,sh.nrows):
        courses.append(( \
            sh.cell_value(rx, 0), \
            "-1" if sh.cell_value(rx, 2) in notACollege else sh.cell_value(rx, 2), \
            sh.cell_value(rx, 4)
            ))
        collegs.append(sh.cell_value(rx, 2) if sh.cell_value(rx, 2) and sh.cell_value(rx, 2) not in notACollege else "-1")
    #课程的id最大为6位，且无前缀0
    collegs = sorted(list(set(collegs)))
    temp = [i for i in range(len(collegs))]
    ne = dict(zip(collegs, temp))
    # print(ne)
    # print(courses)
    # print(collegs)
    returnCourses = []#用于保存各个课程
    for i in range(len(courses)):
        idx = str(i+1)
        course = []
        course.append(idx)#id
        course.append(courses[i][0])#课程名称
        # course.append([])#所属的课程班级id   注：废除课程的课程班级属性
        course.append(random.randint(1, 8))#开课时间
        course.append(courses[i][1])#所属学院
        course.append(courses[i][2])#所需学分
        returnCourses.append(course)
    return returnCourses
#生成学生信息
def generateStudent(names):
    global availableId
    students = []
    years = [str(i) for i in range(2018, 2021)]
    for name in names:
        student = []
        student.append(random.choice(years) + "{0:0>8d}".format(availableId))#学号
        availableId += 1
        student.append('123456')#密码
        student.append(name)#名字
        student.append("数据科学与大数据技术班")#专业班级
        student.append([['-1' for i in range(7)] for j in range(7)])#课程表
        student.append(random.randint(1, 17))#所属学院
        student.append(25)#总的学分
        students.append(student)
    return students
#生成一些可用的名字
def getNames():
    with open('names.txt', 'r', encoding='utf8') as f:
        namestxt = f.readlines()
        for i in range(len(namestxt)):
            namestxt[i] = namestxt[i].rstrip('\n')
        return namestxt
#生成老师的信息
def generateTeacher(names):
    teachers = []
    for name in names:
        teacher = []
        teacher.append("{0:0>8d}".format(availableId))  # 老师id
        availableId += 1
        teacher.append('123456')  # 密码
        teacher.append(name)  # 名字
        teacher.append('我是一个认真负责，教学经验丰富的老师')#介绍
        teacher.append([])#教的课程班级
        teachers.append(teacher)
    return  teachers
#生成管理员
def generateAdmin(n):
    admins = []
    for i in range(n):
        admin = []
        admin.append("{0:0>6d}".format(i))#id
        admin.append("123456")#密码
        admins.append(admin)
    return admins
#生成课程班级
def generateCourseClass(n):
    jiaoshi = []
    for i in range(1, 7):
        for j in range(1, 6):
            for k in range(1, 11):
                jiaoshi.append(str(i) + str(j) + "{0:0>2d}".format(k))
    courseClasses = []
    for i in range(n):
        courseClass = []
        courseClass.append("{0:0>8d}".format(i+1)) #id
        courseClass.append("-1")#班级编号
        courseClass.append("-1")#课程id
        courseClass.append("-1")#老师id
        courseClass.append(list(set([random.randint(0, 48) for i in range(random.randint(2, 3))])))#上课时间段
        courseClass.append([])#上课学生们的id
        courseClass.append(random.choice("wx") + random.choice(jiaoshi))#上课教室
        courseClass.append(random.randint(5, 12)*10)#班级容量
        courseClasses.append(courseClass)
    return courseClasses

def connectAll(courses, students, teachers, admins, courseClasses, nums):
    #建立课程班级与课程之间的关系
    idx = 0
    flag = 0
    for i in range(len(nums)):
        for j in range(nums[i]):
            courseClasses[idx][1] = j+1
            courseClasses[idx][2] = i+1
            idx+=1
    #建立课程班级与老师的联系
    idx = 0
    cnt = 0
    for courseClass in courseClasses:
        courseClass[3] = idx
        teachers[idx][4].append(courseClass[0])
        cnt += 1
        if cnt % 5 == 0:
            idx += 1
            if idx >= len(teachers):
                idx = 0
def outFile(path, ls, flag):
    with open(path, 'w', encoding='utf8') as f:
        f.write(str(len(ls)))
        f.write('\n')
        for student in ls:
            outStr = ""
            for i in range(len(student)):
                if flag and i == 4:
                    for row in student[i]:
                        outStr += " ".join(row) + '\n'
                    continue
                if isinstance(student[i],list):
                    outStr += str(len(student[i])) + '\n'

                    student[i] = map(str, student[i])

                    outStr += " ".join(student[i]) + '\n'
                else:
                    outStr += str(student[i]) + '\n'
            f.write(outStr)

def output(courses, students, teachers, admins, courseClasses):
    # 输出学生数据
    outFile('student.txt', students, 1)
    outFile('courseClass.txt', courseClasses, 0)
    outFile('course.txt', courses, 0)
    outFile('teacher.txt', teachers, 0)
    outFile('admin.txt', admins, 0)
def main():
    names = getNames()

    courses = generateCouse()
    nums = [random.randint(1, 5) for i in range(len(courses))]  # 每个课程对应的班级个数
    students = generateStudent(names[0: 1600])
    teachers = generateTeacher(names[1600:])
    admins = generateAdmin(1)
    courseClasses = generateCourseClass(sum(nums))

    #建立关系
    connectAll(courses, students, teachers, admins, courseClasses, nums)

    #输出内容
    output(courses, students, teachers, admins, courseClasses)
main()