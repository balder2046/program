CPPFLAGS := -g
OBJS := ldbitest.o loginstance.o
ldbitest : $(OBJS)
	g++ $(OBJS) -o ldbitest 
%.o:%.cpp
	g++ -c $(CPPFLAGS) $< -o $@
