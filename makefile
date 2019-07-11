CC=gcc
CXX=g++
RM=rm -f
CXXFLAGS = -std=c++14

SRCS=main.cpp SCmain.cpp Define.cpp Component.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX)	-o	main	$(OBJS)

main.o:	main.cpp

SCmain.o:	SCmain.h	SCmain.cpp

Define.o:	Define.h	Define.cpp

Component.o:	Component.h	Component.cpp


clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main
