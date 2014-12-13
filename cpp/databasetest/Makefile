CPPFLAGS := -g
OBJS := ldbitest.o loginstance.o databaseclient.o mysqldatabase.o 
ldbitest : $(OBJS)
	g++ $(OBJS) -o ldbitest -lmysqlclient
%.o:%.cpp
	g++ -c $(CPPFLAGS) $< -o $@
clean:
	rm ldbitest
	rm *.o
