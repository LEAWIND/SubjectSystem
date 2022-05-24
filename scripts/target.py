import os
import easygui

count_dir=dict()
line_count=dict()
tot = 0
Endwith = [".c",".cpp",".py",".java",".html",".js",".css", ".cs", ".cmd", ".bat"]#选择语种

def target(dir):
    os.chdir(dir)
    dir_list = os.listdir() #当前目录的所有文件和文件夹
    for i in dir_list:
        if os.path.isdir(i):#判断是否为文件夹
            target(os.curdir + os.sep + i)
            os.chdir(os.pardir)#回到当前工作目录
        else:
            try:
                with open(os.curdir + os.sep + i,'rb') as f:
                    m = os.path.splitext(i)[1]# m为后缀名
                    if m in Endwith:
                        count_dir.setdefault(m,0)
                        count_dir[m] += 1# 建立各种类型文件的个数
                        for each_line in f:#可在此循环修改是否包含空行
                            line_count.setdefault(m,0)
                            line_count[m] += 1#建立（后缀名：行号）字典
            except:
                pass


t = easygui.diropenbox('选择你要查看的目录',title='您敲代码的进度')
target(t)
tot = sum(line_count.values())
msg='您现在共累积了{0}行代码，完成进度:{1:.2%}\n离10万行代码还差{2}行，请继续努力！'.format(tot,tot/100000,100000-tot)
txet=''
for i in count_dir:
    txet += '[{0}]源文件{1}个，源代码{2}行\n'.format(i,count_dir[i],line_count[i])
easygui.textbox(msg,text=txet)
