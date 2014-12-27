SRCS := clangtest.cpp
DEPDIR := .deps
OBJDIR := objs
CPPFLAGS := -g -std=c++11 -I/usr/lib/llvm-3.5/include/
LDLIBS := -lmysqlclient -lboost_system -lgtest -lpthread -ljsoncpp -lmysqlcppconn
COMPILE.CPP := clang++
OBJS := $(patsubst %.cpp,objs/%.o, $(SRCS))
OBJDIRS := $(sort $(dir $(OBJS)))
DEPS := $(patsubst %.cpp,deps/%.d, $(SRCS))
$(shell mkdir -p $(OBJDIRS))
$(shell mkdir deps)
clangtest : $(OBJS) 
	$(COMPILE.CPP) $(OBJS) -o $@ $(LDLIBS)
include $(DEPS)
objs/%.o : %.cpp
	$(COMPILE.CPP) -c $(CPPFLAGS) $< -o $@
deps/%.d : %.cpp
	$(COMPILE.CPP) $< -M $(CPPFLAGS) > $@.$$
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

