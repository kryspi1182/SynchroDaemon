OBJ = main.o write_log.o time_test.o file_copy.o
all: demonize
demonize: $(OBJ)
	gcc $(OBJ) -o demonize
$(OBJ): write_log.h time_test.h file_copy.h
.PHONY: clean
clean:
	rm -f *.o demonize
