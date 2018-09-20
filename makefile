#ISHAN TYAGI 
#ROLLNO- 2018201017


CC = g++
CFLAGS = -Wall -std=c++1z
DEPS =  remove_dir.h nonCanonical.h  PermissionsAndDetail.h CommandMode.h
OBJ =  Test1.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

Test1 : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

