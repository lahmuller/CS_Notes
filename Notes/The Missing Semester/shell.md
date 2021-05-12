# Lesson 1

想要创建一个带空格的文件夹
> mkdir a b

会创建两个文件夹a和b，正确用法为
>mkdir a\ b

path
>echo $PATH

展现当前所有的路径，输入一个指令，电脑将会在这些路径里面查找，当我们想要知道某一个指令的位置，只需输入
>which echo

就会得到echo的路径

>cd -

回到你上一次所在路径，可以方便我们在两个路径下切换工作
>mv

可以移动或者重命名文件（夹）
> rm

删除文件
>rmdir

只可以删除空文件夹，出于安全机制的考虑
>man

manual pages,操作手册，可以查看指令的
>ctrl+L

清空界面

一般的，shell的输入流为键盘输入，输出流则直接展现在终端，然而我们可以通过<>来指定I/O
>echo hello > hello.txt  
cat hello.txt  
cat <hello.txt  
cat <hello.txt >hello2.txt

将hello字符串写入hello.txt,查看hello.txt的内容；hello.txt作为输入流，cat显示;不用cp拷贝文件，将cat将本来要输出到终端的内容输出到hello2.txt。cat只做自己工作，不知道被指定的位置。>会覆盖文件内容，而>>可以追加写入

更有趣的是 | 符号，它将左边的程序输出作为右侧程序的输入
>ls -l / | tail -n1

ls -l /列出根目录下详细文件信息,tail -n1输出n个信息中的最后一个，1可以换成任何数字。tail可以换成head，如字面意思。左右两个程序互不了解对方。
此种<>|符号可以无限叠加使用。
>ls -l / | tail -n1 > ls.txt

sudo: do as super

当以非根用户登录时，无法操作一些文件
>sudo mkdir b  
sudo echo a > b.txt 会失败

因为左右两个程序毫无关联，sudo只给了echo a权限，要想执行，应当
> #echo a > b.txt  
or  
echo a > sudo b.txt


或者sudo su 作为root登录 用exit退出

tee命令会将输入写入文件并且同时显示在终端

```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest/missing$ echo "hello world" |tee test.txt
hello world
clay@LAPTOP-TA3R21QJ:~/linuxTest/missing$ cat test.txt
hello world
```
## Exercise
1. Create a new directory called missing under /tmp.
```bash
mkdir /tmp/missing
```
2. Look up the touch program
```bash
man touch
```
3. Use touch to create a new file called semester in missing
```bash
touch semester
```
4. Write the following into that file, one line at a time:
> #!/bin/sh  
curl --head --silent https://missing.csail.mit.edu
```bash
echo "#!/bin/sh" > semester
echo "curl --head --silent https://missing.csail.mit.edu" >> semester
```
5. Try to execute the file, i.e. type the path to the script (./semester) into your shell and press enter. Understand why it doesn’t work by consulting the output of ls
```bash
./semester
```
不能执行，使用ls -l查看权限，发现为-rw-r--r--,则本用户无法执行。

6. Run the command by explicitly starting the sh interpreter, and giving it the file semester as the first argument, i.e. sh semester. Why does this work, while ./semester didn’t?
因为./semester 是将此脚本作为可执行文件执行，而我们没有执行权限，所以会被拒绝，而sh semester，semester文件作为参数（argument)传入，只需要读权限。参考自[What is the difference between running “bash script.sh” and “./script.sh”?
](https://unix.stackexchange.com/questions/136547/what-is-the-difference-between-running-bash-script-sh-and-script-sh?rq=1) 

7. Look up the chmod program
```bash
man chmode
```
chmod: change mode，改变文件的mode rwx，u for user; g for group; o for other; a for all. 如果不加，默认为all. + for add; - for remove; = just make it excatly the same,i.e add mentioned and remove unmentioned.

8. Use chmod to make it possible to run the command ./semester rather than having to type sh semester. How does your shell know that the file is supposed to be interpreted using sh? See this page on the [shebang](https://en.wikipedia.org/wiki/Shebang_(Unix)) line for more information.
```bash
chmod 755 semester
or
chmod u+x semester
```
755 转换为二进制 对应为文件mode的那9位。shell通过文件首行 *#!/bin/sh* 知道通过/bin/sh 的程序去运行该文件内容。

9. Use | and > to write the “last modified” date output by semester into a file called last-modified.txt in your home directory.
```bash
ls -l semester | cut -c27-38 > ~/last-modified.txt
```
date ranges from 27th to 38th character in the output string of ls-l semester on my computer.

10. Write a command that reads out your laptop battery’s power level or your desktop machine’s CPU temperature from /sys
```bash
cat /sys/class/power_supply/BAT1/capacity
```
