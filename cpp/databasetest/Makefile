DEPDIR := .deps
CPPFLAGS := -g
VPATH := objs
COMPILE.CPP := clang++
SRCS := ldbitest.cpp loginstance.cpp databaseclient.cpp mysqldatabase.cpp rowdata.cpp
#OBJS := ldbitest.o loginstance.o databaseclient.o mysqldatabase.o  rowdata.o
OBJS := $(patsubst %.cpp,objs/%.o, $(SRCS))
DEPS := $(patsubst %.cpp,deps/%.d, $(SRCS))

ldbitest : $(OBJS) notexist.h
	$(COMPILE.CPP) $(OBJS) -o ldbitest -lmysqlclient -lboost_system
include $(DEPS)
objs/%.o : %.cpp
	$(COMPILE.CPP) -c $(CPPFLAGS) $< -o $@
deps/%.d : %.cpp
	$(COMPILE.CPP) $< -M > $@.$$
	sed -e 's/\(.*\)\.o[ :]*/objs\/\1.o deps\/\1.d: /' < $@.$$ > $@
	rm -f $@.$$

clean:
	rm -f ldbitest
	rm -f objs/*
	rm -f deps/*
%.h:
	echo "not found " $@
