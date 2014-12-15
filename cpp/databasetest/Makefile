CPPFLAGS := -g
VPATH := objs
SRCS := ldbitest.cpp loginstance.cpp databaseclient.cpp mysqldatabase.cpp rowdata.cpp
#OBJS := ldbitest.o loginstance.o databaseclient.o mysqldatabase.o  rowdata.o
OBJS := $(patsubst %.cpp,objs/%.o, $(SRCS))

ldbitest : $(OBJS)
	echo $(OBJS)
	g++ $(OBJS) -o ldbitest -lmysqlclient
objs/%.o : %.cpp %.h
	g++ -c $(CPPFLAGS) $< -o $@
clean:
	rm ldbitest
	rm objs/*
