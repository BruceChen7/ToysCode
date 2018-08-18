;编译的模式
mode: exe
; 加入源文件
src: test.c
; 编译的选项
flag: -Wall, -g, -O2

; 手动指定exe文件
out: main

; 手动指定临时文件目录
int: obj

mode: exe
src: test.c
inc: ./
out: obj/hello
