CPPFLAGS := -g
VPATH := objs
COMPILE.CPP := clang++
SRCS := ldbitest.cpp loginstance.cpp databaseclient.cpp mysqldatabase.cpp rowdata.cpp
#OBJS := ldbitest.o loginstance.o databaseclient.o mysqldatabase.o  rowdata.o
OBJS := $(patsubst %.cpp,objs/%.o, $(SRCS))

ldbitest : $(OBJS)
	echo $(OBJS)
	$(COMPILE.CPP) $(OBJS) -o ldbitest -lmysqlclient
objs/%.o : %.cpp %.h
	$(COMPILE.CPP) -c $(CPPFLAGS) $< -o $@
clean:
	rm ldbitest
	rm objs/*
