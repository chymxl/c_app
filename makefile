IDIR = ./include
CC=gcc
CFLAGES=-I$(IDIR)

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

_DEPS = app.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

_SRC = main.c
SRCDIR=./src
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))
$(warning $(SRC))
$(ODIR)/%.o: $(SRC) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGES)
$(warning 9)
# $@:目标文件，$^:所有依赖文件，$<:第一个依赖文件
hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGES) $(LIBS)
$(warning 10)
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCLUDE)/*~