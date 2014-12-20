DEPDIR := .deps
OBJDIR := objs
CPPFLAGS := -g
LDLIBS := -lmysqlclient -lboost_system -lgtest -lpthread -ljsoncpp
COMPILE.CPP := clang++
SRCS := ldbitest.cpp loginstance.cpp databaseclient.cpp mysqldatabase.cpp rowdata.cpp allocators.cpp
#OBJS := ldbitest.o loginstance.o databaseclient.o mysqldatabase.o  rowdata.o
OBJS := $(patsubst %.cpp,objs/%.o, $(SRCS))
OBJDIRS := $(sort $(dir $(OBJS)))
DEPS := $(patsubst %.cpp,deps/%.d, $(SRCS))
$(info $(OBJDIRS))
$(shell mkdir -p $(OBJDIRS))

ldbitest : $(OBJS) notexist.h
	$(COMPILE.CPP) $(OBJS) -o ldbitest $(LDLIBS)
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
testfunc:
	$(info the directory is : $(dir test/a.cpp))

