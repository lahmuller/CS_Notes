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
# Lesson 2
```bash
clay@LAPTOP-TA3R21QJ:~$ foo=bar
clay@LAPTOP-TA3R21QJ:~$ echo $foo
bar
clay@LAPTOP-TA3R21QJ:~$ foo = bar

Command 'foo' not found, did you mean:

  command 'fop' from deb fop (1:2.4-2)
  command 'fio' from deb fio (3.16-1)
  command 'goo' from deb goo (0.155+ds-1)

Try: sudo apt install <deb name>
```
You can define a variable in shell like first line, and space is reserved for seperating arguments. So if we type foo = bar , shell will recognize foo as a command, = and bar as its arguments.

```bash
clay@LAPTOP-TA3R21QJ:~$ echo "hello"
hello
clay@LAPTOP-TA3R21QJ:~$ echo 'world'
world
clay@LAPTOP-TA3R21QJ:~$ echo "value is $foo"
value is bar
clay@LAPTOP-TA3R21QJ:~$ echo 'value is $foo'
value is $foo
```
We can use single or double quote in shell to define a string, they are same for literature text, but the variable in double quote will be replaced by its value, and in single quote it won't.

```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ vim mcd.sh
clay@LAPTOP-TA3R21QJ:~/linuxTest$ source mcd.sh
clay@LAPTOP-TA3R21QJ:~/linuxTest$ ls
hello.txt  hello2.txt  mcd.sh  missing
clay@LAPTOP-TA3R21QJ:~/linuxTest$ mcd test
clay@LAPTOP-TA3R21QJ:~/linuxTest/test$
```
>mcd(){  
    mkdir -p "$1"  
    cd "$1"  
}

source mcd.sh define the mcd function into shell. So we can execute the mcd now.
|command| meaning |
| :----: | :----: |
| $0 | the name of the command |
| $1~$9 | the first to the nineth argument of the command |
| $? | the error code of last command |
|  $_ | the last argument from last command |
| !! | the last command　|
| $# | the number of arguments|
| $$ | the pid |
| $@ | the list of all arg |
```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ mkdir /new
mkdir: cannot create directory ‘/new’: Permission denied
clay@LAPTOP-TA3R21QJ:~/linuxTest$ sudo !!
sudo mkdir /new
[sudo] password for clay:
```

```bash
clay@LAPTOP-TA3R21QJ:~$ true
clay@LAPTOP-TA3R21QJ:~$ echo $?
0
clay@LAPTOP-TA3R21QJ:~$ false
clay@LAPTOP-TA3R21QJ:~$ echo $?
1
clay@LAPTOP-TA3R21QJ:~$ true || echo "will not be printed"
clay@LAPTOP-TA3R21QJ:~$ false || echo "Oops, fail"
Oops, fail
clay@LAPTOP-TA3R21QJ:~$ true && echo "will be printed"
will be printed
clay@LAPTOP-TA3R21QJ:~$ false && echo "will not be printed"
clay@LAPTOP-TA3R21QJ:~$ false ; echo "This will always print"
This will always print
clay@LAPTOP-TA3R21QJ:~/linuxTest$ foo=$(pwd)
clay@LAPTOP-TA3R21QJ:~/linuxTest$ echo $foo
/home/clay/linuxTest
clay@LAPTOP-TA3R21QJ:~/linuxTest$ echo "We are in $(pwd)"
We are in /home/clay/linuxTest
clay@LAPTOP-TA3R21QJ:~/linuxTest$ cat <(ls) <(ls ..)
hello.txt
hello2.txt
mcd.sh
missing
test
CS_Notes
last-modified.txt
linuxTest
```
cat can concatenate the output of (ls) and (ls ..)

ls *.sh list all .sh file, ? can only match one character.

```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ mkdir foo{,1,2,29}
clay@LAPTOP-TA3R21QJ:~/linuxTest$ ls
example.sh  foo  foo1  foo2  foo29  hello.txt  hello2.txt  mcd.sh  missing  null  test
```
{} expand the content
```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ touch {foo,bar}/{a..j}
clay@LAPTOP-TA3R21QJ:~/linuxTest$ cd foo
clay@LAPTOP-TA3R21QJ:~/linuxTest/foo$ ls
a  b  c  d  e  f  g  h  i  j
clay@LAPTOP-TA3R21QJ:~/linuxTest/foo$ cd ../bar
clay@LAPTOP-TA3R21QJ:~/linuxTest/bar$ ls
a  b  c  d  e  f  g  h  i  j
clay@LAPTOP-TA3R21QJ:~/linuxTest$ touch foo/x bar/y
clay@LAPTOP-TA3R21QJ:~/linuxTest$ diff <(ls foo) <(ls bar)
11c11
< x
---
> y
```
find命令
```bash
find . -name src -t d
```
`.`表示在当前目录下搜索，src表示名称，`-t`代表type，`d`代表directory

grep命令:搜索文件中的字符（ripgrep,rg)
```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ grep foobar mcd.sh
# foobar
```
递归搜索文件夹-R
```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ grep -R foobar .
./mcd.sh:# foobar
./null: grep foobar "$file" > ./null 2>./null
./null:         echo "File $file does not have any foobar, adding one"
./null:         echo "# foobar" >> "$file"
./example.sh:   grep foobar "$file" > ./null 2>./null
./example.sh:           echo "File $file does not have any foobar, adding one"
./example.sh:           echo "# foobar" >> "$file"
```
history列出shell中执行过的指令，配合grep使用更佳
```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ history | grep tldr
  338  pip install tldr
  339  tldr grep
  342  tldr
  343  sudo apt install tldr
  344  tldr grep
  345  tldr find
  399  history | grep tldr
```

ctrl+R可以进入交互界面，动态匹配使用过的命令

`fzf` is fuzzy find,模糊匹配
# Exercise
1. Read `man ls` and write an `ls` command that lists files in the following manner  
* Includes all files, including hidden files  
* Sizes are listed in human readable format (e.g. 454M instead of 454279954)  
* Files are ordered by recency  
* Output is colorized
```bash
clay@LAPTOP-TA3R21QJ:~/linuxTest$ ls -a -h -l -t
total 48K
drwxr-xr-x 9 clay clay 4.0K May 13 21:41 ..
drwxr-xr-x 6 clay clay 4.0K May 13 17:19 .
-rwxr--r-- 1 clay clay   79 May 13 17:19 script.py
drwxr-xr-x 2 clay clay 4.0K May 13 17:10 bar
drwxr-xr-x 2 clay clay 4.0K May 13 17:10 foo
-rw-r--r-- 1 clay clay   42 May 13 16:43 mcd.sh
-rw-r--r-- 1 clay clay  125 May 13 16:43 null
-rw-r--r-- 1 clay clay  287 May 13 16:43 example.sh
drwxr-xr-x 2 clay clay 4.0K May 13 15:09 test
drwxr-xr-x 2 clay clay 4.0K May 12 20:31 missing
-rw-r--r-- 1 clay clay   12 May 12 00:18 hello2.txt
-rw-r--r-- 1 clay clay    6 May 12 00:10 hello.txt
```
2. >Write bash functions marco and polo that do the following. Whenever you execute marco the current working directory should be saved in some manner, then when you execute polo, no matter what directory you are in, polo should cd you back to the directory where you executed marco. For ease of debugging you can write the code in a file marco.sh and (re)load the definitions to your shell by executing source marco.sh.  
marco.sh
    ```bash
    #!/bin/sh
    marco(){
        pwd > /tmp/marco.txt
    }

    polo(){
        cd &(cat /tmp/marco.txt)
    }
    ```
3. >Say you have a command that fails rarely. In order to debug it you need to capture its output but it can be time consuming to get a failure run. Write a bash script that runs the following script until it fails and captures its standard output and error streams to files and prints everything at the end. Bonus points if you can also report how many runs it took for the script to fail. 


    failscript.sh
    ```bash
    #!/usr/bin/env bash

    n=$(( RANDOM % 100 ))

    if [[ n -eq 42 ]]; then
        echo "Something went wrong"
        >&2 echo "The error was using magic numbers"
        exit 1
    fi

    echo "Everything went according to plan"
    ```

    debug.sh
    ```bash
    #!/usr/bin/env bash

    # empty the file
    >std.out
    >err.out
    cnt=0
    while true; do
            #./fail_script.sh >> ./std.out 2>> ./err.out || break
            ./fail_script.sh >> ./std.out 2>> ./err.out
            if [ $? -ne 0 ]; then
                    break
            fi
            cnt=$((cnt+1))
    done
    cat ./std.out ./err.out
    echo "It takes $cnt runs for the script to fail."
    ```
4. >As we covered in the lecture find’s -exec can be very powerful for performing operations over the files we are searching for. However, what if we want to do something with all the files, like creating a zip file? As you have seen so far commands will take input from both arguments and STDIN. When piping commands, we are connecting STDOUT to STDIN, but some commands like tar take inputs from arguments. To bridge this disconnect there’s the xargs command which will execute a command using STDIN as arguments. For example ls | xargs rm will delete the files in the current directory.  
Your task is to write a command that recursively finds all HTML files in the folder and makes a zip with them. Note that your command should work even if the files have spaces (hint: check -d flag for xargs).

    we have already created some html files, we can list them by using `find`
    ```bash
    clay@LAPTOP-TA3R21QJ:~/linuxTest/lesson2$ find . -name "*.html"
    ./file with space1.html
    ./file with space2.html
    ./somefile5.html
    ./file with space4.html
    ./somefile3.html
    ./test/others3.html
    ./test/others1.html
    ./test/others2.html
    ./somefile2.html
    ./somefile1.html
    ./file with space3.html
    ./somefile4.html
    ```

    As it shows, the files separate with '\n', by looking up the flag `-d` in xargs, we can use `-d '\n'` to let `xargs' separate the args. so here is the answer:
    ```bash
    find . -name '*.html' | xargs -d '\n' tar czf target.tar.gz
    ```

5. >(Advanced) Write a command or script to recursively find the most recently modified file in a directory. More generally, can you list all files by recency?
# TroubleShooting
>-bash: /home/username/.local/bin/packagename: No such file or directory

in my situation, I can't execute `tldr`, so here is the solution
```bash
clay@LAPTOP-TA3R21QJ:~$ tldr
-bash: /home/clay/.local/bin/tldr: No such file or directory
clay@LAPTOP-TA3R21QJ:~$ which tldr
/usr/bin/tldr
clay@LAPTOP-TA3R21QJ:~$ type tldr
tldr is hashed (/home/clay/.local/bin/tldr)
clay@LAPTOP-TA3R21QJ:~$ hash -r
```