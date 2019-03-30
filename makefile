IDIR=./include
CC=gcc
#-Wall 生成所有警告信息
#-g 生成调试信息，GNU调试器可用到该信息
CFLAGES=-I$(IDIR) -Wall -g

#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

ODIR=./obj
LDIR=./lib

LIBS=-lm
#现有如下路径
# a.c
# b.c
# sub
#	 s1.c
#	 s2.c
#patsubst:替换通配符
#wildcard:扩展通配符 
#SRC=$(wildcard *.c ./sub/*.c) 把当前路径和下级sbu路径中所有后缀是c的文件全部展开
#输出: a.c b.c sub/s1.c sub/s2.c
#notdir:去除路径
#DIR=$(notdir $(SRC) )
#输出: a.c b.c s1.c s2.c
#OBJ=$(patsubst %.c, %.o, $(DIR))
#输出: a.o b.o s1.o s2.o

SRC = $(notdir $(wildcard ./src/*.c))
_OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(warning $(SRC))
$(warning $(OBJ))
SRCDIR=./src
$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(CFLAGES)
$(warning 9)
# $@:目标文件，$^:所有依赖文件，$<:第一个依赖文件
hellomake.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGES) $(LIBS)
$(warning 10)
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCLUDE)/*~
	rm -f hellomake
